#include "historico.h"

void obterHoraAtual() {
    time_t horas;
    struct tm* DadosHoras;
    time(&horas);
    DadosHoras = localtime(&horas);

    sprintf(historico.tempo, "%02d/%02d/%d %02d:%02d:%02d", DadosHoras->tm_mday, DadosHoras->tm_mon + 1, DadosHoras->tm_year + 1900, DadosHoras->tm_hour, DadosHoras->tm_min, DadosHoras->tm_sec);
}

void AtualizarHistorico(const char* acao) {
    obterHoraAtual();
    strcpy(historico.acao, acao);
}

void GuardarHistorico() {
    arquivo = fopen("historico.csv", "a");

    if (arquivo != NULL) 
    {
        fprintf(arquivo, "%s, %s\n", historico.tempo, historico.acao);
        fclose(arquivo);
    }
    else {
        printf("Erro ao abrir o arquivo");
    }
}

void LimparHistorico()
{
    if (arquivo != NULL)
    {
        remove("historico.csv");
    }
}