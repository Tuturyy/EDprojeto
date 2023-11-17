#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRABALHAR 1
#define NAO_TRABALHA 0

typedef struct {
    int ID;
    char* NOME;
    int estado;
    int clientes_atendidos;
} FUNCIONARIO;

FUNCIONARIO** LerFuncionarios(int* num_funcionarios);
FUNCIONARIO* CriarFuncionario(int _id, char* _nome);
void DestruirFuncionario(FUNCIONARIO* P);
void MostrarFuncionario(FUNCIONARIO* P);
FUNCIONARIO* gerar_funcionario_aleatorio();