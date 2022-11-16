#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#define MAX 40

////////////////////////BARALHO///////////////

typedef struct baralho {
	int topo;
	int vetor[MAX];
} baralho;

baralho* criaBaralho ();
void liberaBaralho (baralho *b);
int inserirBaralho (baralho *b, int v);

int main ()
{
    baralho *b;
	int escolha, inicio, temp, inserir, num, loop = 0;

    do {
        printf ("Digite o numero de jogadores (2 a 8): \n");
        scanf ("%d", &temp);
        if (temp < 2 || temp > 8)
        {
            printf ("Numero de jogadores invalidos\n");
        }
        else 
        {
            num = temp;
            loop = 1;
        }
    } while (loop == 0);
    printf ("%d jogadores\n", num);

    b = criaBaralho(); //cria baralho (vetor e topo)
    for (int i = 0; i < 40; i++) 
	{
	    temp = i;
		inserir = inserirBaralho (b, temp); //adiciona a pilha/baralho
        if (inserir == 1)
	    {
		    printf ("Numero adicionado: %i\n", b->vetor[b->topo-1]);
	    }
        else
        {
            printf ("Erro ao adicionar numero: %i\n", temp);
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
	b->vetor[b->topo] = v;
	b->topo++;
	return 1;
}