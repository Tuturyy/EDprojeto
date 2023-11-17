#include "listaP.h"

LISTA* CriarListaProdutos()
{
    LISTA* S = (LISTA*)malloc(sizeof(LISTA));
    S->n_prod = 0;
    S->inicio = NULL;
    S->PrecoTotal = 0.0;
    S->TempoCaixa = 0.0;
    S->TempoCompra = 0.0;
    return S;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void MostrarListaProdutos(LISTA* S)
{
    if (!S) return;
    NO_P* PC = S->inicio;
    printf("Numero de Produtos = [%d]\n", S->n_prod);
    while (PC)
    {
        MostrarProduto(PC->Info);
        PC = PC->Prox;
    }
    printf("Preco Total = %.2f\n", S->PrecoTotal);
    printf("Tempo Compra Total = %.2f\n", S->TempoCompra);
    printf("Tempo Caixa Total = %.2f\n", S->TempoCaixa);
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void AdicionarProduto(LISTA* S, PRODUTO* PC)
{
    if (!S || !PC) return;
    NO_P* Aux = (NO_P*)malloc(sizeof(NO_P));
    Aux->Info = PC;
    Aux->Prox = S->inicio;
    S->inicio = Aux;
    S->n_prod++;
    S->PrecoTotal += PC->PRECO;
    S->TempoCaixa += PC->T_CAIXA;
    S->TempoCompra += PC->T_COMPRA;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}