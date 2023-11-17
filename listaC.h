#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"


typedef struct no {
    CLIENTE* info;
    struct no* prox;
}NO_C;

typedef struct {
    int numClientes;
    NO_C* inicio;
}FILA;


FILA* CriarFila();
void destruir_fila(FILA* F);
void MostrarFila(FILA* F);
void AddClienteFim(CLIENTE* C, FILA* F);
void RemoverClienteFila(CLIENTE* C, FILA* F);
CLIENTE* pesquisar_cliente_fila(FILA* F, int id_cliente);