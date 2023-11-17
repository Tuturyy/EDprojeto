#include "supermercado.h"

SUPERMERCADO* super = NULL;

int numero_cenas(const char* file) {
    FILE* fich = fopen(file, "r");
    if (fich == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }
    int count = 0;
    int car;
    while ((car = fgetc(fich)) != EOF) {
        if (car == '\n') {
            count++;
        }
    }
    fclose(fich);
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
    return count;
}


void inicializar_supermercado() {

    if (super == NULL) {
        super = (SUPERMERCADO*)malloc(sizeof(SUPERMERCADO));

        super->num_clientes_total = 0;
        super->num_clientes_alocados = numero_cenas("clientes.txt");
        super->clientes_totais = (CLIENTE**)malloc(super->num_clientes_alocados * sizeof(CLIENTE*));

        super->caixas = (CAIXA**)malloc(NUM_MAX_CAIXAS * sizeof(CAIXA*));
        super->num_caixas_abertas = 0;
        super->num_caixas_alocadas = 0;

        super->num_funcionarios_total = 0;
        super->num_funcionarios_alocados = numero_cenas("funcionarios.txt");
        super->funcionarios = (FUNCIONARIO**)malloc(super->num_funcionarios_alocados * sizeof(FUNCIONARIO*));

        super->num_produtos_total = 0;
        super->num_produtos_alocados = numero_cenas("produtos.txt");
        super->produtos = (PRODUTO**)malloc(super->num_produtos_alocados * sizeof(PRODUTO*));

        super->clientes_supermercado = CriarFila();
        super->tempo_atual = 0;
        super->dinheiro_recebido_total = 0;

        CriarProdGratis();
        AtualizarHistorico(__FUNCTION__);
        GuardarHistorico();
    }
}


int Aleatorio(int x, int y) {

    int numeroAleatorio = rand() % (y - x + 1) + x;
    return numeroAleatorio;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void EntrarMaisCliente(SUPERMERCADO* S, int max_produtos, int min_clientes, int max_clientes)
{

    if (S->clientes_supermercado->numClientes > 100)
    {
        return;
    }

    int x = Aleatorio(min_clientes, max_clientes);

    if (x < (100 - S->clientes_supermercado->numClientes))
    {
        CLIENTE** clientes_totais = NULL;
        if (super->num_clientes_total == 0)
        {
            int n_clientes;
            CLIENTE** todos = LerClientes(&n_clientes);
            super->clientes_totais = todos;
        }
        clientes_totais = super->clientes_totais;
        int num_clientes = super->num_clientes_alocados;
        for (int i = 0; i < x; i++)
        {
            CLIENTE* Acomprar = EscolherClienteAleatorio(clientes_totais, num_clientes);

            int num_escolhas = rand() % max_produtos + 1;
            PRODUTO** produtos = NULL;
            if (super->num_produtos_total == 0)
            {
                int n_produtos;
                PRODUTO** todos_produtos = LerProdutos(&n_produtos);
                super->produtos = todos_produtos;
            }
            int num_produtos = super->num_produtos_alocados;
            produtos = super->produtos;

            LISTA* lista_produtos = CriarListaProdutos();
            for (int i = 0; i < num_escolhas; i++)
            {
                int indice = EscolherProdutosAleatorios(produtos, num_produtos, num_escolhas);
                AdicionarProduto(lista_produtos, super->produtos[indice]);
            }

            Acomprar->produtosCarrinho = lista_produtos;

            // Mostrar a lista de produtos do cliente
            //printf("Produtos do Cliente [%d] %s: \n", Acomprar->ID, Acomprar->NOME);
            //MostrarListaProdutos(Acomprar->produtosCarrinho);
            //printf("\n");

            AddClienteFim(Acomprar, S->clientes_supermercado);
            Acomprar->tempo_entrada = super->tempo_atual;
            Acomprar->tempo_recolha = Acomprar->tempo_entrada + Acomprar->produtosCarrinho->TempoCompra;


        }
        printf("Entraram %d clientes\n", S->clientes_supermercado->numClientes);

    }
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}


void retirar_cliente_supermercado_para_caixa()
{
    NO_C* cliente = super->clientes_supermercado->inicio;
    NO_C* proximo = NULL;
    while (cliente != NULL)
    {
        int i = 0;
        if (super->tempo_atual > cliente->info->tempo_recolha)
        {
            adicionar_cliente_automatico(cliente->info);
            i = 1;
            proximo = cliente->prox;
            RemoverClienteFila(cliente->info, super->clientes_supermercado);
        }
        if (i == 0)
        {
            cliente = cliente->prox;
        }
        else
        {
            cliente = proximo;
        }
    }
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void KABOOM()
{
    if (super != NULL)
    {
        for (int i = 0; i < super->num_produtos_alocados; i++)
        {
            DestruirProduto(super->produtos[i]);
        }
        for (int i = 0; i < super->num_funcionarios_alocados; i++)
        {
            DestruirFuncionario(super->funcionarios[i]);
        }
        for (int i = 0; i < super->num_clientes_alocados; i++)
        {
            DestruirCliente(super->clientes_totais[i]);
        }
        for (int i = 0; i < super->num_caixas_alocadas; i++)
        {
            destruir_caixa(super->caixas[i]);
        }
        free(super);
    }
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}