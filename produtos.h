#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int ID;
    char* NOME;
    double PRECO;
    double T_COMPRA;
    double T_CAIXA;
} PRODUTO;

PRODUTO** LerProdutos(int* num_produtos);
PRODUTO* CriarProduto(int _id, char* _nome, double _preco, double _tcompra, double _tcaixa);
void DestruirProduto(PRODUTO* P);
void MostrarProduto(PRODUTO* P);
int EscolherProdutosAleatorios(PRODUTO** produtos, int num_produtos, int num_escolhas);
