#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaP.h"
#define TEMPO_MAX_ESPERA 1100


typedef struct { 
    int ID;
    char* NOME;
    int numProdutos;
    LISTA *produtosCarrinho;
    int tempo_entrada;
    double tempo_recolha;
    double tempo_saida;
} CLIENTE;

typedef struct
{
    int num_prodgratis;
    double preco_gratis_total;
}PRODGRATIS;

PRODGRATIS* prodgratis;



CLIENTE** LerClientes(int* num_clientes);
CLIENTE* CriarCliente(int _id, char* _nome);
void DestruirCliente(CLIENTE* P);
void MostrarCliente(CLIENTE* P);
void ProdutoGratis(CLIENTE* cliente);
void MostrarProdGratis();
CLIENTE* EscolherClienteAleatorio(CLIENTE** clientes, int num_clientes);