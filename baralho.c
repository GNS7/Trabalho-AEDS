#include <stdio.h>
#include <stdlib.h>
#define MAX 40

////////////////////////BARALHO///////////////

typedef struct baralho {
	int topo;
	int vetor[MAX];
} baralho;


baralho* criaBaralho ();
void liberaBaralho (baralho *b);
int inserirBaralho (baralho *b, int v);
int retirarBaralho (baralho *b, int *v);
int baralhoCheio (baralho *b);
int baralhoVazio (baralho *b);

int main() {
	baralho *b;
	int escolha, inicio, temp;

	while (inicio != 2) // loop inicial
	{
		printf
		(
			"\n1. Criar baralho\n"
			"2. Sair\n"
		);
		scanf ("%d", &inicio);

		switch (inicio)
		{
		case 1:
			b = criaBaralho(); //cria baralho (vetor e topo)
			do //loop de escolha
			{
				printf
				(
					"\n1. Inserir\n" //embaralho um novo numero
					"2. Retirar\n" //desembaralho um numero
					"3. Conferir se o baralho esta vazio\n" //
					"4. Conferir se o baralho esta cheio\n" //
					"5. Liberar o baralho\n" //
					"6. Sair\n" //volta para o switch inicial
          			"7. Topo\n"
				);
				scanf  ("%d", &escolha);

				switch (escolha)
				{
				case 1:
					
					for (int i = 0; i < 40; i++)
					{
						temp = i;
						int inserir = inserirBaralho (b, temp);
					}
					if (inserir == -1)
					{
						printf ("A baralho esta cheia\n");
					}
					else
					{
						printf ("Numero adicionado: %i\n", temp);
					}
					break;
				case 2:
					printf ("Digite o valor que quer retirar\n");
					scanf ("%d", &temp);
					if (retirarBaralho (b &temp) == 0)
					{
						printf ("A baralho esta vazia\n");
					}
					else
					{
						printf ("Numero %i retirado\n", temp);
					}

					break;
				case 3:
					if (baralhoVazio (b) == 1)
					{
						printf ("Baralho vazia\n");
					}
					else
					{
						printf ("Baralho nao vazia\n");
					}
					break;
				case 4:
					if (baralhoCheio (b) == 1)
					{
						printf ("Baralho cheia\n");
					}
					else
					{
						printf ("Baralho nao Cheia\n");
					}
					break;
				case 5:
					liberaBaralho (b);
					break;
				case 6:
					exit (0);
					break;
        		case 7:
					printf ("Topo: %i\n", b->topo);
					break;
				}
			} while (escolha != 6);
		case 2: return 0; break;
		}
	}
	return 0;
}


baralho* criaBaralho ()
{
	baralho *b;
	b = (baralho *) malloc (sizeof (baralho));
	b->topo = 0;
	return b;
}

void liberaBaralho (baralho *b)
{
	free (b);
}

int inserirBaralho (baralho *b, int v)
{
	if (baralhoCheia(b) == 1)
	{
		return -1;
	}
	else
	{
		b->vetor[b->topo] = v;
		b->topo++;
		return 1;
	}
}

int retirarBaralho (baralho *b, int *v)
{
	if (baralhoVazio) == 1)
	{
		return -1;
	}
	b->topo -= 1;
	return 1;
}

int baralhoCheio (baralho *b)
{
	if (b>topo < 10) //fix sizeof (p->vetor)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int baralhoVazio (baralho *b)
{
	if (b->topo <= 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
