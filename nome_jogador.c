
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#define MAX 40

////////////////////////BARALHO///////////////

typedef struct carta {
    int valor; // 1 a 10
    int naipe; // 1 - copas / 2 – ouros / 3 – espadas / 4 - paus.
    int carta_id; // 1 a 40
} carta;	

typedef struct jogador {
    char nome [20];
    int vidas;
    int jogador_id;
    carta mao[];
} jogador;

typedef struct baralho {
	int topo;
	carta vetor[MAX];
} baralho;


jogador* criaJogadores (int num_jogadores);

int main ()
{
    baralho *b;
    jogador *j;

    int loop = 0, num_jogadores = 3;
    j = criaJogadores (num_jogadores);
    if (j == NULL)
    {
        printf ("Erro ao criar a lista de jogadores\n");
        return 1;
    }

    //Pegar o nome dos jogadores
    do 
    {
        //printf ("\n loop: %d\n", loop);

        printf ("Digite o nome do %i jogador\n", loop + 1);
        scanf ("%s", &j[loop].nome[0]);

        //printf ("\n loop: %d\n", loop);

        loop += 1;
    } while (loop < num_jogadores);

    for (int i = 0; i < num_jogadores; i++)
    {
        printf ("\n");
        printf ("%i %s\n", i, j[i].nome);
    }

    free (b);
return 0;
}

jogador* criaJogadores (int num_jogadores)
{
	jogador *j;
	j = (jogador *) malloc (num_jogadores * sizeof(jogador));
	return j;
}