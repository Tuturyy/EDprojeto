#include "clientes.h"
#include"supermercado.h"

CLIENTE* CriarCliente(int _id, char* _nome)
{
    CLIENTE* P = (CLIENTE*)malloc(sizeof(CLIENTE));
    P->ID = _id;
    P->NOME = (char*)malloc((strlen(_nome) + 1) * sizeof(char));
    strcpy(P->NOME, _nome);
    P->produtosCarrinho = CriarListaProdutos();
    P->tempo_entrada = 0;
    P->tempo_recolha = 0;
    P->tempo_saida = 0;
    super->num_clientes_total++;
    return P;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void DestruirCliente(CLIENTE* P)
{
    if (!P) return;
    free(P->NOME);
    free(P->produtosCarrinho);
    free(P);
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void MostrarCliente(CLIENTE* P)
{
    printf("Cliente: [%d] : %s\n", P->ID, P->NOME);
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

CLIENTE** LerClientes(int* num_clientes)
{
    FILE* F = fopen("clientes.txt", "r");
    if (!F) {
        *num_clientes = 0;
        return NULL;
    }

    char BUFFER[1001];
    CLIENTE** clientes = NULL;
    *num_clientes = 0;

    while (fgets(BUFFER, 1000, F))
    {
        int ID;
        char* NOME;
        int i = 0;
        char* CAMPOS[10];
        char* token = strtok(BUFFER, "\t");

        while (token != NULL)
        {
            CAMPOS[i] = token;
            token = strtok(NULL, "\t");
            i++;
        }
        ID = atoi(CAMPOS[0]);
        NOME = CAMPOS[1];

        (*num_clientes)++;
        clientes = (CLIENTE**)realloc(clientes, (*num_clientes) * sizeof(CLIENTE*));
        clientes[*num_clientes - 1] = CriarCliente(ID, NOME);
    }

    fclose(F);
    return clientes;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void CriarProdGratis()
{
    prodgratis = (PRODGRATIS*)malloc(sizeof(PRODGRATIS));
    prodgratis->num_prodgratis = 0;
    prodgratis->preco_gratis_total = 0;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void ProdutoGratis(CLIENTE* cliente)
{
    if (cliente->produtosCarrinho && cliente->produtosCarrinho->inicio)
    {
        cliente->produtosCarrinho->PrecoTotal -= cliente->produtosCarrinho->inicio->Info->PRECO;
        prodgratis->num_prodgratis++;
        prodgratis->preco_gratis_total += cliente->produtosCarrinho->inicio->Info->PRECO;
        cliente->produtosCarrinho->inicio->Info->PRECO = 0;
    }
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void MostrarProdGratis()
{
    if (prodgratis)
    {
        printf("Foram oferecidos %d produtos, sendo o preço combinado dos mesmos %.2lf euros\n", prodgratis->num_prodgratis, prodgratis->preco_gratis_total);
    }
    else
    {
        printf("Nao foram oferecidos produtos\n");
    }
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

CLIENTE* EscolherClienteAleatorio(CLIENTE** clientes, int num_clientes)
{
    static int* indices_escolhidos = NULL;
    static int num_indices_escolhidos = 0;

    srand(time(NULL));

    if (num_indices_escolhidos == num_clientes) {
        // Todos os clientes já foram escolhidos
        return NULL;
    }

    int indice_aleatorio;
    do {
        indice_aleatorio = rand() % num_clientes;
    } while (ClienteJaEscolhido(indice_aleatorio, indices_escolhidos, num_indices_escolhidos));

    // Armazena o índice escolhido
    indices_escolhidos = realloc(indices_escolhidos, (num_indices_escolhidos + 1) * sizeof(int));
    indices_escolhidos[num_indices_escolhidos] = indice_aleatorio;
    num_indices_escolhidos++;

    return clientes[indice_aleatorio];
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

int ClienteJaEscolhido(int indice, int* indices_escolhidos, int num_indices_escolhidos) {
    for (int i = 0; i < num_indices_escolhidos; i++) {
        if (indices_escolhidos[i] == indice) {
            return 1; // Cliente já escolhido anteriormente
        }
    }
    return 0; // Cliente não foi escolhido anteriormente
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}