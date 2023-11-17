#include "caixa.h"
#include"supermercado.h"
#define MEDIA_CLIENTES_FILA_CHEIA 7
#define MEDIA_CLIENTES_FILA_VAZIA 2
ESTATISTICAS_CAIXA stats[NUM_MAX_CAIXAS] = { 0 };


CAIXA* criar_caixa()
{
	if (super->num_caixas_alocadas >= NUM_MAX_CAIXAS)
	{
		return NULL;
	}
	for (int i = 0; i < super->num_caixas_alocadas; i++)
	{
		if (super->caixas[i]->estado_caixa == CAIXA_CLOSED)
		{
			super->caixas[i]->estado_caixa = CAIXA_OPEN;
			printf("\nCaixa [%d] reaberta.\n", i + 1);
			super->num_caixas_abertas++;
			return super->caixas[i];
		}
	}
	CAIXA* C = (CAIXA*)malloc(sizeof(CAIXA));
	int verifica_id = 0;
	C->id = super->num_caixas_alocadas + 1;
	criar_stats(C->id);
	C->fila_clientes = CriarFila();
	C->estado_caixa = CAIXA_OPEN;
	super->caixas[super->num_caixas_alocadas] = C;
	super->num_caixas_alocadas++;
	super->num_caixas_abertas++;
	C->funcionario = gerar_funcionario_aleatorio();
	if (C->funcionario == NULL)
	{
		fechar_caixa(C);
		return NULL;
	}
	printf("Caixa [%d] aberta.\n", C->id);
	return C;
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

void fechar_caixa(CAIXA* C)
{
	if (!C) return;
	C->estado_caixa = CAIXA_CLOSED;
	if (C->funcionario != NULL)
	{
		C->funcionario->estado = NAO_TRABALHA;
	}
	super->num_caixas_abertas--;
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

void fechar_caixa_e_distribuir(CAIXA* C)
{
	float media = calcular_media_clientes(super->caixas);
	if (media >= MEDIA_CLIENTES_FILA_CHEIA)
	{
		printf("Impossivel fechar caixa porque a media de clientes por caixa esta muito alta.");
		return;
	}
	if (!C)return;
	int caixa;
	for (int i = 0; i < super->num_caixas_alocadas; i++)//Encontrar a caixa que vai ser destruida dentro do supermercado
	{
		if (super->caixas[i] == C)
		{
			caixa = i;
		}
	}
	printf("\nCaixa [%d] fechada.", C->id);
	FILA* armazenar = C->fila_clientes; //Copiamos a fila ja que vamos destruir a caixa de seguida
	NO_C* atual = armazenar->inicio;
	fechar_caixa(C);
	if (armazenar->numClientes != 0)
	{
		printf("Clientes vao ser distribuidos...\n");
		while (armazenar->numClientes != 0)
		{
			atual = armazenar->inicio;
			while (atual->prox != NULL)
			{
				atual = atual->prox;
			}
			adicionar_cliente_caixarapida(super->caixas, atual->info);//Adicionamos o ultimo cliente a caixa rapida. Destruimos a caixa anteriormente caso contrario esta funcao iria ter em conta a caixa que vai ser destruida
			RemoverClienteFila(atual->info, armazenar);
		}
	}
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

void destruir_caixa(CAIXA* C)
{
	if (!C) return;
	free(C->fila_clientes);
	free(C);
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

void mostrar_caixa(CAIXA* C)
{
	int caixa = -1;
	for (int i = 0; i < super->num_caixas_alocadas; i++)
	{
		if (super->caixas[i] == C)
			caixa = 0;
	}
	if (caixa == -1)
	{
		printf("\nCaixa nao existe!\n");
		return;
	}
	printf("\nCaixa ID-[%d]\n", C->id);
	if (C->funcionario != NULL) //num_caixas_abertas<=num_funcionarios &&		
		MostrarFuncionario(C->funcionario);
	else printf("Nao existe funcionario nesta caixa.\n");
	printf("Tamanho da fila de clientes[%d]\n", C->fila_clientes->numClientes);
	if (C->fila_clientes->numClientes != 0)
	{
		MostrarFila(C->fila_clientes);
	}
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

void mostrar_todas_caixas()
{
	for (int i = 0; i < super->num_caixas_alocadas; i++)
	{
		if (super->caixas[i]->estado_caixa == CAIXA_CLOSED)
			printf("\nCaixa [%d] - FECHADA\n", super->caixas[i]->id);
		else
			mostrar_caixa(super->caixas[i]);
	}
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

void adicionar_cliente(CAIXA* C, CLIENTE* cliente)
{
	if (C == NULL)
	{
		printf("Impossivel adicionar cliente. Nao existe caixa.\n");
		return;
	}
	if (C->fila_clientes->numClientes >= TAM_MAX_FILA)
	{
		printf("Caixa cheia.");
		return;
	}
	if (C->estado_caixa == CAIXA_CLOSED)
	{
		printf("Caixa fechada. Impossivel adicionar cliente");
		return;
	}
	else
	{
		//printf("Cliente [%s] adicionado a caixa [%d]\n", cliente->NOME, C->id);
		AddClienteFim(cliente, C->fila_clientes);
		double tempo_caixa = caclcular_tempo_caixa(C, cliente);
		cliente->tempo_saida = cliente->tempo_recolha + tempo_caixa;
	}
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

void remover_cliente(CAIXA* C, CLIENTE* cli)
{
	RemoverClienteFila(cli, C->fila_clientes);
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

CLIENTE* pesquisar_cliente_caixa(CAIXA* C, int id_cliente)
{
	CLIENTE* encontrado;
	encontrado = pesquisar_cliente_fila(C->fila_clientes, id_cliente);
	return encontrado;
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

CAIXA* em_que_caixa_esta_cliente(int id_cliente)
{
	if (!id_cliente)
		return NULL;
	CLIENTE* encontrado = NULL;
	for (int i = 0; i < super->num_caixas_alocadas; i++)
	{
		encontrado = pesquisar_cliente_caixa(super->caixas[i], id_cliente);
		if (encontrado != NULL)
		{
			return super->caixas[i];
		}
	}
	return NULL;
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

CLIENTE* pesquisar_cliente(int id_cliente)
{
	CAIXA* caixa = em_que_caixa_esta_cliente(id_cliente);
	CLIENTE* encontrado = pesquisar_cliente_caixa(caixa, id_cliente);
	return encontrado;
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

CAIXA* converter_id_em_caixa(int id)
{
	if (!id) return;
	for (int i = 0; i < super->num_caixas_alocadas; i++)
	{
		if (super->caixas[i]->id == id)
		{
			return super->caixas[i];
		}
	}
	printf("Caixa [%d] nao existe.\n", id);
	return NULL;
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

void mudar_cliente_caixa(CLIENTE* cliente, CAIXA* recetora)
{
	if (cliente == NULL || recetora == NULL)
	{
		printf("Erro: Cliente ou caixa nao existem.");
		return;
	}
	if (recetora->estado_caixa == CAIXA_CLOSED)
	{
		printf("Caixa [%d] fechada.Impossivel adicionar o cliente.\n", recetora->id);
		return;
	}
	CAIXA* caixa_do_cliente = em_que_caixa_esta_cliente(cliente->ID);
	if (caixa_do_cliente == NULL)
	{
		printf("Cliente nao esta em nenhuma caixa");
		return;
	}
	RemoverClienteFila(cliente, caixa_do_cliente);
	adicionar_cliente(recetora, cliente);
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

void adicionar_cliente_caixarapida(CAIXA** caixas, CLIENTE* cliente)
{
	if (super->num_caixas_alocadas == 0)
	{
		criar_caixa();
	}
	int transfere_clientes;
	int soma_produtos = 0;
	int soma_menor = 10000000;
	int caixa_rapida = -1;
	for (int i = 0; i < super->num_caixas_alocadas; i++)
	{
		soma_produtos = 0;
		if (caixas[i]->estado_caixa == CAIXA_OPEN && caixas[i]->fila_clientes->numClientes < TAM_MAX_FILA)
		{
			NO_C* atual = caixas[i]->fila_clientes->inicio;
			while (atual != NULL)
			{
				soma_produtos += atual->info->produtosCarrinho->n_prod;
				atual = atual->prox;
			}
			if (soma_produtos < soma_menor)
			{
				soma_menor = soma_produtos;
				caixa_rapida = i;
			}
		}
	}
	adicionar_cliente(caixas[caixa_rapida], cliente);
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

void media_destruir_criar_caixa(CAIXA** caixas)
{
	float x = calcular_media_clientes(caixas);
	if (x >= MEDIA_CLIENTES_FILA_CHEIA)
	{
		//printf("A media de clientes por caixa (%.1f) esta alta. A abrir uma nova caixa...\n",x);
		if (super->num_caixas_alocadas < NUM_MAX_CAIXAS)
		{
			int distribuir = (x * super->num_caixas_abertas) / (super->num_caixas_abertas + 1);
			CAIXA* nova = criar_caixa();
			//printf("Caixa aberta com sucesso: ID[%d]\n\n", nova->id);
			while (caixas[nova->id - 1]->fila_clientes->numClientes != distribuir)
			{

				int fila_maior = 0;
				int caixa_cheia = -1;
				for (int i = 0; i < super->num_caixas_alocadas; i++)
				{
					if (caixas[i]->estado_caixa == CAIXA_OPEN)
					{
						if (caixas[i]->fila_clientes->numClientes >= fila_maior)
						{
							fila_maior = caixas[i]->fila_clientes->numClientes;
							caixa_cheia = i;
						}
					}
				}
				FILA* fila_caixa_cheia = caixas[caixa_cheia]->fila_clientes;
				NO_C* ultimo = fila_caixa_cheia->inicio;
				while (ultimo->prox != NULL)
				{
					ultimo = ultimo->prox;
				}
				adicionar_cliente(caixas[nova->id - 1], ultimo->info);
				RemoverClienteFila(ultimo->info, caixas[caixa_cheia]->fila_clientes);
			}
			printf("\nNova caixa:");
			mostrar_caixa(caixas[nova->id - 1]);
		}
		else printf("Limite maximo de caixas abertas atingido. Impossivel abrir outra caixa.\n");
	}

	if ((x <= MEDIA_CLIENTES_FILA_VAZIA) && (super->num_caixas_abertas > 1))
	{
		int fila_menor = 11;
		int caixa_destruir = -1;
		for (int k = 0; k < super->num_caixas_alocadas; k++)//Encontrar a caixa com menor fila para ser destruida
		{
			if (super->caixas[k]->estado_caixa == CAIXA_OPEN)
			{
				if (caixas[k]->fila_clientes->numClientes < fila_menor)
				{
					fila_menor = caixas[k]->fila_clientes->numClientes;
					caixa_destruir = k;
				}
			}
		}
		printf("A media de clientes por caixa (%.1f) esta baixa. Fechada a caixa de ID[%d]!\n", x, caixas[caixa_destruir]->id);
		fechar_caixa(caixas[caixa_destruir]);
		/*
		FILA* destruir = caixas[caixa_destruir]->fila_clientes;
		NO_C* cliente_atual = destruir->inicio;
		while (cliente_atual != NULL)
		{
			adicionar_cliente_caixarapida(super->caixas, cliente_atual->info);
			RemoverClienteFila(caixas[caixa_destruir]->fila_clientes->inicio->info, caixas[caixa_destruir]->fila_clientes);
			cliente_atual = cliente_atual->prox;
		}
		*/
	}
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

void adicionar_cliente_automatico(CLIENTE* cliente)
{
	adicionar_cliente_caixarapida(super->caixas, cliente);//Adiciona o cliente a caixa mais rapida(A que tem menos produtos)
	media_destruir_criar_caixa(super->caixas);//Depois com a entrada deste novo cliente irá calcular a media de clientes por caixa e dependendo do valor cria/destroi uma caixa ou nao
	if (cliente->tempo_saida > super->tempo_atual + TEMPO_MAX_ESPERA)
		ProdutoGratis(cliente);
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

float calcular_media_clientes(CAIXA** caixas)
{
	float media_clientes = 0;
	float num_clientes = 0;
	for (int i = 0; i < super->num_caixas_alocadas; i++)
	{
		if (caixas[i]->estado_caixa == CAIXA_OPEN)
			num_clientes += caixas[i]->fila_clientes->numClientes;
	}
	return media_clientes = num_clientes / super->num_caixas_abertas;
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

void criar_stats(int id_caixa)
{
	stats[id_caixa - 1].num_clientes_atendidos = 0;
	stats[id_caixa - 1].id = id_caixa;
	stats[id_caixa - 1].produtos_vendidos = 0;
	stats[id_caixa - 1].clientes_atendidos = (CLIENTE**)malloc(2000 * sizeof(CLIENTE*));
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

void update_stats_caixa(CAIXA* C, CLIENTE* cliente)
{
	stats[C->id - 1].clientes_atendidos[stats[C->id - 1].num_clientes_atendidos] = cliente;
	stats[C->id - 1].num_clientes_atendidos++;
	stats[C->id - 1].produtos_vendidos += cliente->produtosCarrinho->n_prod;
	C->funcionario->clientes_atendidos++;
	super->dinheiro_recebido_total += cliente->produtosCarrinho->PrecoTotal;
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

void mostrar_stats_caixa(CAIXA* C)
{
	if (!C) return;
	printf("\nTotal de clientes atendidos[%d]:\n", stats[C->id - 1].num_clientes_atendidos);
	if (stats[C->id - 1].num_clientes_atendidos > 0)
	{
		for (int i = 0; i < stats[C->id - 1].num_clientes_atendidos; i++)
		{
			MostrarCliente(stats[C->id - 1].clientes_atendidos[i]);
		}
	}
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

void mostrar_stats_importantes()
{
	int menos_clientes_atendidos = 1000000;
	int pior_funcionario = -1;
	int mais_clientes_atendidos = 0;
	int caixa_atendeu_mais = -1;
	int mais_produtos_vendidos = 0;
	int caixa_vendeu_mais = -1;
	for (int i = 0; i < super->num_caixas_alocadas; i++)
	{
		if (stats[i].num_clientes_atendidos > mais_clientes_atendidos)
		{
			mais_clientes_atendidos = stats[i].num_clientes_atendidos;
			caixa_atendeu_mais = i;
		}
		if (stats[i].produtos_vendidos > mais_produtos_vendidos)
		{
			mais_produtos_vendidos = stats[i].produtos_vendidos;
			caixa_vendeu_mais = i;
		}
		if (super->caixas[i]->funcionario->clientes_atendidos < menos_clientes_atendidos)
		{
			menos_clientes_atendidos = super->caixas[i]->funcionario->clientes_atendidos;
			pior_funcionario = i;
		}
	}
	printf("\n-------------------- ESTATISTICA --------------------\n");
	printf("A caixa[%d] foi a caixa que atendeu mais clientes(%d)\n", super->caixas[caixa_atendeu_mais]->id, mais_clientes_atendidos);
	printf("A caixa[%d] foi a caixa que vendeu mais produtos(%d)\n", super->caixas[caixa_vendeu_mais]->id, mais_produtos_vendidos);
	printf("O funcionário que atendeu menos clientes (%d) foi ", super->caixas[pior_funcionario]->funcionario->clientes_atendidos);
	MostrarFuncionario(super->caixas[pior_funcionario]->funcionario);
	MostrarProdGratis();
	printf("O supermercado hoje recebeu uma quantia de [%d euros]\n", super->dinheiro_recebido_total);
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}

double caclcular_tempo_caixa(CAIXA* C, CLIENTE* cli)
{
	if (C->fila_clientes->numClientes == 0)
		return cli->produtosCarrinho->TempoCaixa;
	else
	{
		double tempo_novo = cli->produtosCarrinho->TempoCaixa;
		FILA* fila = C->fila_clientes;
		NO_C* primeiro = fila->inicio;
		while (primeiro->info != cli)
		{
			tempo_novo += primeiro->info->produtosCarrinho->TempoCaixa;
			primeiro = primeiro->prox;
		}
		return tempo_novo;
	}
	AtualizarHistorico(__FUNCTION__);
	GuardarHistorico();
}
