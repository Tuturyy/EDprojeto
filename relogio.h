#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    time_t START;
    int VELOCIDADE;
    time_t Hora_Inicio;
    int pausado;
    time_t tempoPausado;
} Relogio;

void StartRelogio(Relogio* R, int Vel, const char* H_Inicio);
void MudarVelocidadeRelogio(Relogio* R, int Vel);
time_t VerTimeRelogio(Relogio* R);
void WaitSegundos(int s);
void Wait(int s);