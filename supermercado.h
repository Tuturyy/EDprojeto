#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listaC.h"
#include "listaP.h"
#include "funcionarios.h"
#include "caixa.h"

typedef struct {
    CLIENTE** clientes_totais;
    int num_clientes_alocados;
    int num_clientes_total;
    PRODUTO** produtos;
    int num_produtos_alocados;
    int num_produtos_total;
    FUNCIONARIO** funcionarios;
    int num_funcionarios_alocados;
    int num_funcionarios_total;
    CAIXA** caixas;
    int num_caixas_abertas;
    int num_caixas_alocadas;
    FILA* clientes_supermercado;
    int tempo_atual;
    int dinheiro_recebido_total;
} SUPERMERCADO;

SUPERMERCADO* super;


void inicializar_supermercado();
void EntrarMaisCliente(SUPERMERCADO* S, int max_produtos, int min_clientes, int max_clientes);
void retirar_cliente_supermercado_para_caixa();
void KABOOM();