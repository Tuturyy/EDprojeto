#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char tempo[20];
    char acao[100];
} HISTORICO;

HISTORICO historico;
FILE* arquivo;

void LimparHistorico();