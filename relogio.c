#include "relogio.h"

void StartRelogio(Relogio* R, int Vel, const char* H_Inicio)
{
    R->START = time(0);
    R->VELOCIDADE = Vel;
    struct tm* tmp = localtime(&R->START);
    sscanf(H_Inicio, "%d:%d:%d", &tmp->tm_hour, &tmp->tm_min, &tmp->tm_sec);
    R->Hora_Inicio = mktime(tmp);
    R->pausado = 0;
    R->tempoPausado = 0;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void MudarVelocidadeRelogio(Relogio* R, int Vel)
{
    if (R->pausado) {
        R->VELOCIDADE = Vel;
        R->pausado = 0;
        time_t tempoAtual = time(0);
        R->START = tempoAtual - R->tempoPausado;
    }
    else {
        R->VELOCIDADE = 0;
        R->pausado = 1;
        R->tempoPausado = difftime(time(0), R->START);
    }
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

time_t VerTimeRelogio(Relogio* R)
{
    if (R->pausado) {
        return R->Hora_Inicio;
    }
    else {
        time_t Dif = difftime(time(0), R->START);
        time_t Simulada = R->Hora_Inicio + Dif * R->VELOCIDADE;
        return Simulada;
    }
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void WaitSegundos(int s)
{
    clock_t T0 = clock();
    clock_t T1 = T0 + s;
    while (clock() < T1);
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void Wait(int s)
{
    WaitSegundos(s * CLOCKS_PER_SEC);
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}