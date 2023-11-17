#include "produtos.h"
#include"supermercado.h"

PRODUTO* CriarProduto(int _id, char* _nome, double _preco, double _tcompra, double _tcaixa)
{
    PRODUTO* P = (PRODUTO*)malloc(sizeof(PRODUTO));
    P->ID = _id;
    P->NOME = (char*)malloc((strlen(_nome) + 1) * sizeof(char));
    strcpy(P->NOME, _nome);
    P->PRECO = _preco;
    P->T_COMPRA = _tcompra;
    P->T_CAIXA = _tcaixa;
    //super->produtos[super->num_produtos_total] = P;
    super->num_produtos_total++;
    return P;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void DestruirProduto(PRODUTO* P)
{
    if (!P) return;
    free(P->NOME);
    free(P);
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void MostrarProduto(PRODUTO* P)
{
    printf("Produto: [%d] : [%s]\n", P->ID, P->NOME);
    printf("Preco: [%.2lf]\n", P->PRECO);
    printf("Tempo de compra: [%.2lf]\n", P->T_COMPRA);
    printf("Tempo de caixa: [%.2lf]\n", P->T_CAIXA);
    printf("\n");
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void PontoVirgula(char* str) {
    char* ponto = strchr(str, '.');
    if (ponto != NULL) {
        *ponto = ',';
    }
}

PRODUTO** LerProdutos(int* num_produtos)
{
    FILE* F = fopen("produtos.txt", "r");
    if (!F) {
        return NULL;
        *num_produtos = 0;
    }
    PRODUTO** produtos = NULL;
    char BUFFER[1001];
    //int i = 0;
    *num_produtos = 0;
    while (!feof(F))
    {
        fgets(BUFFER, 1000, F);
        int ID;
        char* NOME;
        double PRECO;
        double T_COMPRA;
        double T_CAIXA;
        int j = 0;
        char* CAMPOS[10];
        char* token = strtok(BUFFER, "\t");
        while (token != NULL)
        {
            CAMPOS[j] = token;
            token = strtok(NULL, "\t");
            j++;
        }
        ID = atoi(CAMPOS[0]);
        NOME = CAMPOS[1];
        PontoVirgula(CAMPOS[2]);
        PontoVirgula(CAMPOS[3]);
        PontoVirgula(CAMPOS[4]);
        PRECO = atof(CAMPOS[2]);
        T_COMPRA = atof(CAMPOS[3]);
        T_CAIXA = atof(CAMPOS[4]);
        /*printf("%s\t%lf", CAMPOS[2], PRECO);*/

        (*num_produtos)++;
        produtos = (PRODUTO**)realloc(produtos, (*num_produtos) * sizeof(PRODUTO*));
        produtos[*num_produtos - 1] = CriarProduto(ID, NOME, PRECO, T_COMPRA, T_CAIXA);

        /*PRODUTO* P = CriarProduto(ID, NOME, PRECO, T_COMPRA, T_CAIXA);
        produtos = (PRODUTO**)realloc(produtos, (i + 1) * sizeof(PRODUTO*));
        produtos[i] = P;
        i++;*/
    }
    fclose(F);
    return produtos;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

int EscolherProdutosAleatorios(PRODUTO** produtos, int num_produtos, int num_escolhas)
{


    if (num_produtos < num_escolhas || produtos == NULL)
    {
        return NULL;
    }
    int indice = rand() % num_produtos;

    return indice;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

double PrecoTotal(PRODUTO** produtos, int num_produtos)
{
    double Preco = 0.0;
    for (int i = 0; i < num_produtos; i++) {
        PRODUTO* produto = produtos[i];
        Preco += produto->PRECO;
    }

    return Preco;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

double TempoCaixa(PRODUTO** produtos, int num_produtos)
{
    double tCaixa = 0.0;
    for (int i = 0; i < num_produtos; i++) {
        PRODUTO* produto = produtos[i];
        tCaixa += produto->T_CAIXA;
    }

    return tCaixa;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

double TempoCompra(PRODUTO** produtos, int num_produtos)
{
    double tCompra = 0.0;
    for (int i = 0; i < num_produtos; i++) {
        PRODUTO* produto = produtos[i];
        tCompra += produto->T_COMPRA;
    }

    return tCompra;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}