#include "listaC.h"

FILA* CriarFila()
{
    FILA* F = (FILA*)malloc(sizeof(FILA));
    F->numClientes = 0;
    F->inicio = NULL;
    return F;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void destruir_fila(FILA* F)
{
    if (!F)return;
    NO_C* C = F->inicio;
    NO_C* Aux;
    while (C)
    {
        Aux = C->prox;
        free(C->info);
        free(C);
        C = Aux;
    }
    free(F);
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void MostrarFila(FILA* F)
{
    if (!F) return;
    NO_C* C = F->inicio;
    while (C != NULL)
    {
        MostrarCliente(C->info);
        C = C->prox;
    }
    printf("\n");
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void AddClienteFim(CLIENTE* C, FILA* F)
{
    if (!C || !F) return;
    NO_C* Aux = (NO_C*)malloc(sizeof(NO_C));
    Aux->info = C;
    Aux->prox = NULL;
    if (!F->inicio)
        F->inicio = Aux;
    else
    {
        NO_C* Q = F->inicio;
        while (Q->prox)
            Q = Q->prox;
        Q->prox = Aux;
    }
    F->numClientes++;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void RemoverClienteFila(CLIENTE* C, FILA* F)
{
    if (!C || !F) return;
    NO_C* atual = F->inicio;
    NO_C* anterior = NULL;

    while (atual != NULL)
    {
        if (atual->info == C)
        {
            if (anterior == NULL)
            {
                F->inicio = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }
            F->numClientes--;
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

CLIENTE* pesquisar_cliente_fila(FILA* F, int id_cliente)
{
    if (!F && !id_cliente) return;
    NO_C* atual = F->inicio;
    while (atual && atual->info->ID != id_cliente)
    {
        atual = atual->prox;
    }
    if (atual)
    {
        if (atual->info->ID == id_cliente)
        {
            //printf("O cliente esta na fila desta caixa.");
            return atual->info;
        }
        //else printf("Cliente nao encontrado.");
    }
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}