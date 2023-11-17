#include "supermercado.h"
#include "relogio.h"
#include "historico.h"
#include <locale.h>
#include <conio.h>


int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "PT");
    inicializar_supermercado();
    LimparHistorico();
    Relogio Rolex;
    printf("BEM VINDO A SIMULACAO DE SUPERMERCADO\nPARA ACEDER AO MENU PRESSIONE 'M'\nO SUPERMERCADO ESTARA ABERTO DAS 8:30 ATE AS 21:00\n\n");
    Wait(5);
    StartRelogio(&Rolex, 360, "8:30:00");

    time_t Simulada = VerTimeRelogio(&Rolex);
    int simuladaInt = (int)Simulada;
    int t_inicial = simuladaInt;
    int t_atualizado = simuladaInt;
    super->tempo_atual = t_atualizado;
    EntrarMaisCliente(super, 100, 20, 40);
    FILA* fila_supermercado = super->clientes_supermercado;
    NO_C* cliente = fila_supermercado->inicio;
    int clienteatendido = 0;
    int k = 0;
    while (t_atualizado < (t_inicial + 43200))
    {
        time_t Simulada = VerTimeRelogio(&Rolex);
        int simuladaInt = (int)Simulada;
        t_atualizado = simuladaInt;
        super->tempo_atual = t_atualizado;

        char tecla;
        int opcao1, opcao2;
        int id_cliente_procurado;
        int id_caixa_procurada;

        if (kbhit())
        {  // Verifica se alguma tecla foi pressionada
            tecla = getch();  // Obtém a tecla pressionada

            if (tecla == 'M' || tecla == 'm')
            {  // Verifica se a tecla é o 'M'
                MudarVelocidadeRelogio(&Rolex, 0);
                do 
                {
                    printf("\n------------------------ MENU ------------------------\n");
                    printf("1. Abrir uma nova caixa\n");
                    printf("2. Fechar uma caixa\n");
                    printf("3. Passar um dado cliente para outra caixa\n");
                    printf("4. Pesquisar caixa de um certo cliente\n");
                    printf("5. Mostrar clientes no Supermercado\n");
                    printf("6. Mostrar caixas do Supermercado\n");
                    printf("7. Mostrar funcionarios no Supermercado\n");
                    printf("8. Mostrar produtos de um cliente\n");
                    printf("9. Mostrar estatisticas do momento\n");
                    printf("10. Voltar a simulacao\n");
                    printf("11. Sair\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcao1);
                    printf("\n");

                    switch (opcao1)
                    {
                    case 1:
                        criar_caixa();
                        break;
                    case 2:
                        printf("Qual o id da caixa que deseja fechar?\n");
                        scanf("%d", &id_caixa_procurada);
                        CAIXA* caixa1 = converter_id_em_caixa(id_caixa_procurada);
                        fechar_caixa_e_distribuir(caixa1);
                        break;
                    case 3:
                        printf("Qual o id do cliente que deseja mover?\n");
                        scanf("%d", &id_cliente_procurado);
                        CLIENTE* cl_encontrado2 = pesquisar_cliente(id_cliente_procurado);
                        printf("\nQual o id da caixa onde deseja colocar o cliente?\n");
                        scanf("%d", &id_caixa_procurada);
                        CAIXA* caixa2 = converter_id_em_caixa(id_caixa_procurada);
                        mudar_cliente_caixa(cl_encontrado2, caixa2);
                        break;
                    case 4:
                        printf("Qual o id do cliente que quer encontrar?\n");
                        scanf("%d", &id_cliente_procurado);
                        CAIXA* caixinha = em_que_caixa_esta_cliente(id_cliente_procurado);
                        mostrar_caixa(caixinha);
                        break;
                    case 5:
                        printf("CLIENTES AS COMPRAS:\n");
                        MostrarFila(super->clientes_supermercado);
                        printf("CLIENTES NAS CAIXAS:\n");
                        for(int i = 0;i < super->num_caixas_alocadas; i++)
                        {
                            MostrarFila(super->caixas[i]->fila_clientes);
                        }
                        break;
                    case 6:
                        mostrar_todas_caixas();
                        break;
                    case 7:
                        for(int i = 0; i < super->num_funcionarios_alocados; i++)
                        {
                            if(super->funcionarios[i]->estado == TRABALHAR)
                            {
                                printf("[%d] %s", super->funcionarios[i]->ID, super->funcionarios[i]->NOME);
                            }
                        }
                        break;
                    case 8:
                        printf("Qual o id do cliente que deseja ver?\n");
                        scanf("%d", &id_cliente_procurado);
                        CLIENTE* cl_encontrado3 = pesquisar_cliente(id_cliente_procurado);
                        MostrarListaProdutos(cl_encontrado3->produtosCarrinho);
                        break;
                    case 9:
                        mostrar_stats_importantes();
                        break;
                    case 10:
                        MudarVelocidadeRelogio(&Rolex, 360);
                        break;
                    case 11:
                        printf("Saindo...Volte sempre\n");
                        return 0;
                    default:
                        printf("Opcao invalida. Tente novamente.\n");
                       }
                } while (opcao1 != 10);
            }
        }

        if (super->clientes_supermercado->numClientes > 0)
        {
            retirar_cliente_supermercado_para_caixa();
        }

        for (int i = 0; i < super->num_caixas_alocadas; i++)
        {
            FILA* caixa = super->caixas[i]->fila_clientes;
            NO_C* cliente = caixa->inicio;
            NO_C* proximo = NULL;
            if (super->caixas[i]->fila_clientes->numClientes > 0)
            {
                while (cliente != NULL)
                {
                    int j = 0;
                    if (super->tempo_atual > cliente->info->tempo_saida)
                    {
                        j = 1;
                        k++;
                        clienteatendido++;
                        update_stats_caixa(super->caixas[i], cliente->info);  
                        proximo = cliente->prox;
                        RemoverClienteFila(cliente->info, super->caixas[i]->fila_clientes);
                        if (k == 10 && (t_atualizado < (t_inicial + 39600)))
                        {
                            k = 0;
                            EntrarMaisCliente(super, 100, 7, 20);
                        }
                    }
                    if (j == 0)
                    {
                        cliente = cliente->prox;
                    }
                    else
                    {
                        cliente = proximo;
                    }
                }
            }
        }
    }
    int clientesnascaixas = 0;
    for (int i = 0; i < super->num_caixas_alocadas; i++)
    {
        clientesnascaixas += super->caixas[i]->fila_clientes->numClientes;
    }

    mostrar_todas_caixas();
    mostrar_stats_importantes();
    printf("Numero total de clientes atendidos:%d", clienteatendido);
    printf("\nClientes que estao nas caixas:%d", clientesnascaixas);
    printf("\nclientes no supermercado: %d\n", super->clientes_supermercado->numClientes);
    KABOOM();
}