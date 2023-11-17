#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"

typedef struct NO_P
{
    PRODUTO* Info;
    struct NO_P* Prox;

}NO_P, ELEMENTO;

typedef struct
{
    int n_prod;
    NO_P* inicio;
    double PrecoTotal;
    double TempoCaixa;
    double TempoCompra;
}LISTA;


LISTA* CriarListaProdutos();
void MostrarListaProdutos(LISTA* S);
void AdicionarProduto(LISTA* S, PRODUTO* PC);