#pragma once
#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include"listaC.h"
#include"Funcionarios.h"

#define NUM_MAX_CAIXAS 30
#define TAM_MAX_FILA 10 

#define CAIXA_OPEN 1
#define CAIXA_CLOSED 0


typedef struct {
	int id;
	int estado_caixa;
	FILA* fila_clientes;
	FUNCIONARIO* funcionario;
}CAIXA;

typedef struct {
	int id;
	int num_clientes_atendidos;
	int produtos_vendidos;
	CLIENTE** clientes_atendidos;
}ESTATISTICAS_CAIXA;


//CAIXAS

//Criar Fechar
CAIXA* criar_caixa();
void fechar_caixa(CAIXA* caixa);
void fechar_caixa_e_distribuir(CAIXA* C);
void destruir_caixa(CAIXA* C);
//Mostrar
void mostrar_caixa(CAIXA* C);
void mostrar_todas_caixas();
//Pesquisar
CLIENTE* pesquisar_cliente_caixa(CAIXA* C, int id_cliente);
CAIXA* em_que_caixa_esta_cliente(int id_cliente);
CLIENTE* pesquisar_cliente(int id_cliente);
CAIXA* converter_id_em_caixa(int id);
//Cliente
void adicionar_cliente(CAIXA* C, CLIENTE* cliente);
void remover_cliente(CAIXA* C, int id_cliente);
void mudar_cliente_caixa(CLIENTE* cliente, CAIXA* recetora);
void adicionar_cliente_caixarapida(CAIXA** caixas, CLIENTE* cliente);
void adicionar_cliente_automatico(CLIENTE* cliente);
float calcular_media_clientes(CAIXA* caixas);
double caclcular_tempo_caixa(CAIXA* C, CLIENTE* cli);



//ESTATISTICAS

void criar_stats(int id_caixa);
void update_stats_caixa(CAIXA* C, CLIENTE* cliente);
void mostrar_stats_caixa(CAIXA* C);
void mostrar_stats_importantes();
