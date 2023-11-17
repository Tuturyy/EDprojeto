#include "funcionarios.h"
#include "supermercado.h"

FUNCIONARIO* CriarFuncionario(int _id, char* _nome)
{
    FUNCIONARIO* P = (FUNCIONARIO*)malloc(sizeof(FUNCIONARIO));
    P->ID = _id;
    P->NOME = (char*)malloc((strlen(_nome) + 1) * sizeof(char));
    strcpy(P->NOME, _nome);
    P->estado = NAO_TRABALHA;
    P->clientes_atendidos = 0;
    super->funcionarios[super->num_funcionarios_total] = P;
    super->num_funcionarios_total++;
    return P;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void DestruirFuncionario(FUNCIONARIO* P)
{
    if (!P) return;
    free(P->NOME);
    free(P);
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

void MostrarFuncionario(FUNCIONARIO* P)
{
    printf("[%d] %s", P->ID, P->NOME);
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}

FUNCIONARIO** LerFuncionarios(int* num_funcionarios)
{
    FILE* F = fopen("funcionarios.txt", "r");
    if (!F) {
        *num_funcionarios = 0;
        return NULL;
    }

    char BUFFER[1001];
    FUNCIONARIO** funcionarios = NULL;
    *num_funcionarios = 0;

    while (fgets(BUFFER, 1000, F)) {
        int ID;
        char* NOME;
        int i = 0;
        char* CAMPOS[10];
        char* token = strtok(BUFFER, "\t");

        while (token != NULL) {
            CAMPOS[i] = token;
            token = strtok(NULL, "\t");
            i++;
        }

        ID = atoi(CAMPOS[0]);
        NOME = CAMPOS[1];

        (*num_funcionarios)++;
        funcionarios = (FUNCIONARIO**)realloc(funcionarios, (*num_funcionarios) * sizeof(FUNCIONARIO*));
        funcionarios[*num_funcionarios - 1] = CriarFuncionario(ID, NOME);
    }

    fclose(F);
    return funcionarios;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}


FUNCIONARIO* gerar_funcionario_aleatorio()
{
    if (super->num_funcionarios_total == 0)
    {
        int num_funcionarios;
        super->funcionarios = LerFuncionarios(&num_funcionarios);
    }
    if (super->num_funcionarios_total == 0)
    {
        return NULL;
    }
    for (int i = 0; i < super->num_funcionarios_total; i++)
    {
        if (super->funcionarios[i]->estado == NAO_TRABALHA)
        {
            super->funcionarios[i]->estado = TRABALHAR;
            return super->funcionarios[i];
        }
    }
    return NULL;
    AtualizarHistorico(__FUNCTION__);
    GuardarHistorico();
}