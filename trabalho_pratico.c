#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#define MAX 40

////////////////////////BARALHO///////////////

typedef struct carta {
    int valor; // 1 / 2 / 3 / 4 / 5 / 6 / 7 / 11 / 12 / 13
    int naipe; // 1 - ouros / 2 – espadas / 3 – copas / 4 - paus.
    int carta_id; // 1 a 40
    //int poder;
} carta;	

typedef struct baralho {
	int topo;
	carta vetor[MAX];
} baralho;

typedef struct jogador {
    char nome [20];
    int vidas; //comeca com 5 vidas
    int jogador_id; //1 a 8
    carta mao[5]; //1 a 5 cartas
} jogador;



baralho* criaBaralho ();
void liberaBaralho (baralho *b);
int inserirBaralho (baralho *b);
int numeroJogadores ();
jogador* criaJogadores (int num_jogadores);
void liberaJogador (jogador *j);
void nomeJogadores (jogador *j, int num_jogadores);
carta* criaCarta ();
int constroiCarta (baralho *b, carta *c);




int main ()
{
    baralho *b;
    jogador *j;
    carta *c;

	int temp, inserir, num_jogadores, loop = 0, cartas = 5, constroi;

    //Pede o numero de jogadores
    num_jogadores = numeroJogadores();
    printf ("%d jogadores\n", num_jogadores);

    //Cria a lista de jogadores
    j = criaJogadores (num_jogadores);
    if (j == NULL)
    {
        printf ("Erro ao criar a lista de jogadores\n");
        return 1;
    }
    printf ("Lista de jogadores criada com sucesso\n");

    //Pegar o nome dos jogadores
    nomeJogadores (j, num_jogadores);

    //cria baralho (vetor e topo)
    b = criaBaralho();
    if (b == NULL)
    {
        printf ("Erro ao criar o baralho\n");
        return 1;
    }
    printf ("Baralho criado com sucesso\n");

    //inserir cartas no baralho
    inserir = inserirBaralho (b);
    //printf ("Inserir: %i\n", inserir);
    if (inserir == 0)
    {
        printf ("Erro ao inserir cartas no baralho, baralho cheio\n");
        return 1;
    }
    else if (inserir == 1)
    {
        printf ("Baralho criado com sucesso\n");
    }

    //criar cartas
    c = criaCarta ();
    if (c == NULL)
    {
        printf ("Erro ao criar as cartas\n");
        return 1;
    }

    //Construir as cartas
    constroi = constroiCarta(b, c);
    if (constroi != 40)
    {
        printf ("Erro ao construir as cartas\n");
        return 1;
    }
    else if (constroi == 40)
    {
        printf ("Cartas construidas com sucesso\n");
    }
    
        



    /*for (int i = 0; i < 40; i++) 
	{
	    temp = i;
        //adiciona a pilha/baralho
		inserir = inserirBaralho (b, temp); 
        if (inserir == 1)
	    {
		    printf ("numero adicionado: %i\n", b->vetor[b->topo-1]);
	    }
        else
        {
            printf ("Erro ao adicionar numero: %i\n", temp);
        }
    }*/

    liberaBaralho (b);
    liberaJogador (j);
    free(c);
    return 0;
}





int numeroJogadores ()
{
    int num_jogadores, loop = 0, temp;
    do {
        printf ("Digite o numero de jogadores (2 a 8): \n");
        scanf ("%d", &temp);
        if (temp < 2 || temp > 8)
        {
            printf ("numero de jogadores invalidos\n");
        }
        else 
        {
            num_jogadores = temp;
            loop = 1;
        }
    } while (loop == 0);
    
    return num_jogadores;
}

jogador* criaJogadores (int num_jogadores)
{
	jogador *j;
	j = (jogador *) malloc (num_jogadores * sizeof(jogador)); //aloca memoria para a lista de jogadores
	return j; //retorna a lista de jogadores
}

void liberaJogador (jogador *j)
{
	free (j);
}

void nomeJogadores (jogador *j, int num_jogadores)
{
    int loop = 0;
    do 
    {
        printf ("Digite o nome do %i jogador\n", loop + 1);
        scanf ("%s", &j[loop].nome[0]);
        j[loop].jogador_id = loop + 1;
        j[loop].vidas = 5;
        ++loop;
    } while (loop < num_jogadores);

    /*for (int i = 0; i < num_jogadores; i++)
    {
        printf ("\n");
        printf ("%i %s\n", i, j[i].nome);
    }*/

}

baralho* criaBaralho ()
{
	baralho *b;
	b = (baralho *) malloc (sizeof (baralho)); //aloca memoria para o baralho
	b->topo = 0; //inicializa o topo
	return b; //retorna o baralho
}

void liberaBaralho (baralho *b)
{
	free (b);
}

int inserirBaralho (baralho *b)
{
    int temp;
    srand(time(NULL)); //inicializa o gerador de numeros aleatorios
     if (b->topo == MAX)
    {
        printf ("Baralho cheio\n");
        return 0;
    }

    else 
    {
        for (int i = 0; i < MAX; i++)
        {
            if (b->topo == MAX)
            {
                return 1;
            }
            else
            {
                temp = rand() % 40; //gera um numero aleatorio entre 0 e 39

                //printf ("i: %i\n", i);
                //printf ("temp: %i\n", temp);
                //printf ("topo: %i\n", b->topo);

                for (int j = 0; j < b->topo; j++) //loop para verificar se o numero temp ja existe como carta_id
                {
                    
                    if (temp == b->vetor[j].carta_id)
                    {
                        i--; //se o numero ja existe, volta o loop para gerar outro numero
                        b->topo--; //volta o topo para nao adicionar o numero repetido
                        //printf ("numero ja existe\n");
                    }
                }
                b->vetor[b->topo].carta_id = temp; //se o numero nao existe, adiciona o numero ao vetor
                b->topo++;
            }
            
        } 
    return 1;
    }
}

carta* criaCarta ()
{
    carta *c;
	c = (carta *) malloc (40 * sizeof(carta));
	return c;
}

int constroiCarta (baralho *b, carta *c)
{
    int count = 0;
    for (int i = 0; i < MAX; i++)
    {
        switch (b->vetor[b->topo].carta_id)
        {
            case 0: c[i].valor = 4; c[i].naipe = 1; count++; printf ("%i \n", c[i].valor); break;
            case 1: c[i].valor = 4; c[i].naipe = 2; count++; printf ("%i \n", c[i].valor); break;
            case 2: c[i].valor = 4; c[i].naipe = 3; count++; printf ("%i \n", c[i].valor); break;
            case 3: c[i].valor = 5; c[i].naipe = 1; count++; printf ("%i \n", c[i].valor); break;
            case 4: c[i].valor = 5; c[i].naipe = 2; count++; printf ("%i \n", c[i].valor); break;
            case 5: c[i].valor = 5; c[i].naipe = 3; count++; printf ("%i \n", c[i].valor); break;
            case 6: c[i].valor = 5; c[i].naipe = 4; count++; printf ("%i \n", c[i].valor); break;
            case 7: c[i].valor = 6; c[i].naipe = 1; count++; printf ("%i \n", c[i].valor); break;
            case 8: c[i].valor = 6; c[i].naipe = 2; count++; printf ("%i \n", c[i].valor); break;
            case 9: c[i].valor = 6; c[i].naipe = 3; count++; printf ("%i \n", c[i].valor); break;
            case 10: c[i].valor = 6; c[i].naipe = 4; count++; printf ("%i \n", c[i].valor); break;
            case 11: c[i].valor = 7; c[i].naipe = 2; count++; printf ("%i \n", c[i].valor); break;
            case 12: c[i].valor = 7; c[i].naipe = 4; count++; printf ("%i \n", c[i].valor); break;
            case 13: c[i].valor = 11; c[i].naipe = 1; count++; printf ("%i \n", c[i].valor); break;
            case 14: c[i].valor = 11; c[i].naipe = 2; count++; printf ("%i \n", c[i].valor); break;
            case 15: c[i].valor = 11; c[i].naipe = 3; count++; printf ("%i \n", c[i].valor); break;
            case 16: c[i].valor = 11; c[i].naipe = 4; count++; printf ("%i \n", c[i].valor); break;
            case 17: c[i].valor = 12; c[i].naipe = 1; count++; printf ("%i \n", c[i].valor); break;
            case 18: c[i].valor = 12; c[i].naipe = 2; count++; printf ("%i \n", c[i].valor); break;
            case 19: c[i].valor = 12; c[i].naipe = 3; count++; printf ("%i \n", c[i].valor); break;
            case 20: c[i].valor = 12; c[i].naipe = 4; count++; printf ("%i \n", c[i].valor); break;
            case 21: c[i].valor = 13; c[i].naipe = 1; count++; printf ("%i \n", c[i].valor); break;
            case 22: c[i].valor = 13; c[i].naipe = 2; count++; printf ("%i \n", c[i].valor); break;
            case 23: c[i].valor = 13; c[i].naipe = 3; count++; printf ("%i \n", c[i].valor); break;
            case 24: c[i].valor = 13; c[i].naipe = 4; count++; printf ("%i \n", c[i].valor); break;
            case 25: c[i].valor = 1; c[i].naipe = 1; count++; printf ("%i \n", c[i].valor); break;
            case 26: c[i].valor = 1; c[i].naipe = 3; count++; printf ("%i \n", c[i].valor); break;
            case 27: c[i].valor = 1; c[i].naipe = 4; count++; printf ("%i \n", c[i].valor); break;
            case 28: c[i].valor = 2; c[i].naipe = 1; count++; printf ("%i \n", c[i].valor); break;
            case 29: c[i].valor = 2; c[i].naipe = 2; count++; printf ("%i \n", c[i].valor); break;
            case 30: c[i].valor = 2; c[i].naipe = 3; count++; printf ("%i \n", c[i].valor); break;
            case 31: c[i].valor = 2; c[i].naipe = 4; count++; printf ("%i \n", c[i].valor); break;
            case 32: c[i].valor = 3; c[i].naipe = 1; count++; printf ("%i \n", c[i].valor); break;
            case 33: c[i].valor = 3; c[i].naipe = 2; count++; printf ("%i \n", c[i].valor); break;
            case 34: c[i].valor = 3; c[i].naipe = 3; count++; printf ("%i \n", c[i].valor); break;
            case 35: c[i].valor = 3; c[i].naipe = 4; count++; printf ("%i \n", c[i].valor); break;
            case 36: c[i].valor = 7; c[i].naipe = 1; count++; printf ("%i \n", c[i].valor); break;
            case 37: c[i].valor = 1; c[i].naipe = 2; count++; printf ("%i \n", c[i].valor); break;
            case 38: c[i].valor = 7; c[i].naipe = 3; count++; printf ("%i \n", c[i].valor); break;
            case 39: c[i].valor = 4; c[i].naipe = 4; count++; printf ("%i \n", c[i].valor); break;
        }
        count++;
    }
    printf("count: %i\n", count);
    return count;
}


/*    carta *c;

    c = (carta *) malloc (sizeof(carta));
    c->carta_id = ;
    c->valor = ;
    c->naipe = ;*/