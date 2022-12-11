#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#define MAX 40

////////////////////////BARALHO///////////////

typedef struct carta {
    int valor; // 1 / 2 / 3 / 4 / 5 / 6 / 7 / 11 / 12 / 13
    int naipe; // 1 - ouros / 2 – espadas / 3 – copas / 4 - paus.
    char *naipe_char;
    char *extras; // As e familia real
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
    int vence_turnos; 
    int turnos_vencidos;
} jogador;

typedef struct mesa{
    carta cartas_mesa[5];
}mesa;


baralho* criaBaralho ();
void liberaBaralho (baralho *b);
mesa* criaMesa ();
int inserirBaralho (baralho *b);
int numeroJogadores ();
jogador* criaJogadores (int num_jogadores);
int alocaCartasMao (jogador *j);
void liberaJogador (jogador *j);
void nomeJogadores (jogador *j, int num_jogadores);
carta* criaCarta ();
int constroiCarta (baralho *b, carta *c);
void preencheBaralho (carta *c, baralho *b);
int calcularCartas (int num_jogadores, int num_cartas_mao);
int distribuirCartas (int num_cartas_mao, jogador *j, baralho *b, int num_jogadores);
void intToString (jogador *j, int num_cartas_mao, int num_jogadores);




int main ()
{
    baralho *b;
    jogador *j;
    carta *c;
    mesa *m;

	int temp, inserir, num_jogadores, num_cartas_mao = 5, loop = 0, cartas = 5, constroi, cartas_distribuidas, count_of_cards_mesa = 0;
    char *familia_real, *as;

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

    //calcular o numero de cartas
    num_cartas_mao = calcularCartas (num_jogadores, num_cartas_mao);
    printf ("Numero de cartas por jogador: %d\n", num_cartas_mao);

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
        printf ("Cartas adicionadas com sucesso\n");
    }

    //criar cartas
    c = criaCarta ();
    if (c == NULL)
    {
        printf ("Erro ao criar as cartas\n");
        return 1;
    }

    /////////////////////////////////////
    /*for (int i = 0; i < 40; i++)
    {
        printf ("Carta %d\n", b->vetor[i].carta_id);
    }*/
    ///////////////////////////////////////

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

    //preencher o baralho
    preencheBaralho (c, b);

    //distribuir as cartas
    cartas_distribuidas = distribuirCartas (num_cartas_mao, j, b, num_jogadores);
    if (cartas_distribuidas == 0)
    {
        printf ("Erro ao distribuir as cartas\n");
        return 1;
    }
    else if (cartas_distribuidas == 1)
    {
        printf ("Cartas distribuidas com sucesso\n");
    }




    /////////////////****************Aloca Espaco para o naipe e as cartas especiais****************/////////////////////
    if (alocaCartasMao (j) == 0)
    {
        printf ("Erro ao alocar espaco para as cartas\n");
        return 1;
    }
    else
    {
        printf ("Espaco alocado com sucesso\n");
    }

    //Cria a mesa
    m = criaMesa ();

    //Comeca o jogo

    //Passa os naipes de int para string
    intToString (j, num_cartas_mao, num_jogadores);

    //Print de cartas_distribuidas 
    for (int i = 0; i < num_cartas_mao; i++)
    {
        if (j->mao[i].valor == 1 )
        {
            printf ("%s de %s,", j->mao[i].extras, j->mao[i].naipe_char);
        }
        else if (j->mao[i].valor == 11 || j->mao[i].valor == 12 || j->mao[i].valor == 13)
        {
            printf ("%s de %s, ", j->mao[i].extras, j->mao[i].naipe_char);
        }
        else
        {
            printf ("%d de %s, ", j->mao[i].valor, j->mao[i].naipe_char);
        }
    }

    printf ("\n");

    for (int i = 40; i > 0; i--)
    {
        printf ("Carta %d: %d de %d   topo: %d\n", b->vetor[i].carta_id, b->vetor[i].valor, b->vetor[i].naipe, b->topo);
    }

    //Escolha de turnos
    printf ("\nEscolha quantas turnos voce faz: 1 2 3 4 ou 5\n");
    scanf ("%d", &temp);
    if (temp < 1 || temp > 5)
    {
        printf ("Numero invalido, tente novamente\n");
        return 1; /////////////////////////////////////////////////////FAZER LOOP/////////////////////////////////////////////////////////////////////////////
    }
    else
    {
        printf ("Voce escolheu %d turnos\n", temp);\
        j->vence_turnos = temp;
    }

    //Escolha de cartas e jogadas
    for (int i = 0; i < num_cartas_mao; i++)
    {
        if (j->mao[i].valor == 1 )
        {
            printf ("%s de %s ,", j->mao[i].extras, j->mao[i].naipe_char);
        }
        else if (j->mao[i].valor == 11 || j->mao[i].valor == 12 || j->mao[i].valor == 13)
        {
            printf ("%s de %s, ", j->mao[i].extras, j->mao[i].naipe_char);
        }
        else
        {
            printf ("%d de %s, ", j->mao[i].valor, j->mao[i].naipe_char);
        }
    }
    printf ("\nEscolha qual carta deseja jogar\n");
    scanf ("%d", &temp);
    temp--;
    if (temp < 0 || temp > 5)
    {
        printf ("Numero invalido, tente novamente\n");
        return 1; /////////////////////////////////////////////////////FAZER LOOP/////////////////////////////////////////////////////////////////////////////
    }
    else
    {
        if (j->mao[temp].valor == 1 )
        {
            printf ("%s de %s ,", j->mao[temp].extras, j->mao[temp].naipe_char);
        }
        else if (j->mao[temp].valor == 11 || j->mao[temp].valor == 12 || j->mao[temp].valor == 13)
        {
            printf ("%s de %s, ", j->mao[temp].extras, j->mao[temp].naipe_char);
        }
        else
        {
            printf ("%d de %s, ", j->mao[temp].valor, j->mao[temp].naipe_char);
        }
    }

    //Adiciona carta a mesa
    m->cartas_mesa[count_of_cards_mesa] = j->mao[temp];
    printf ("Carta %d: %d %d %s\n", count_of_cards_mesa, m->cartas_mesa[count_of_cards_mesa].carta_id, m->cartas_mesa[count_of_cards_mesa].valor, m->cartas_mesa[count_of_cards_mesa].naipe_char);
    count_of_cards_mesa++;

    //Verifica qual a maior carta da mesa
    

    /*for (int i = 0; i < num_jogadores; i++)
    {
        for (int k = 0; k < num_cartas_mao; k++)
        {
           printf ("Carta %d: %d %d %d\n", k, j[i].mao[k].carta_id, j[i].mao[k].valor, j[i].mao[k].naipe);
        }
    }*/

    
        



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

int alocaCartasMao (jogador *j)
{
    for (int i = 0; i < 5; i++)
    {
        j->mao[i].extras = (char *) malloc (20 * sizeof(char)); //aloca espaco para as cartas especiais
        j->mao[i].naipe_char = (char *) malloc (20 * sizeof(char)); //aloca espaco para o naipe
    }
    if (j->mao[0].extras == NULL || j->mao[0].naipe_char == NULL) //verifica se alocou espaco
    {
        return 0;
    }
    else
    {
        return 1;
    }
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
        printf ("Digite o nome do %i jogador\n", loop + 1); //pede o nome do jogador
        scanf ("%s", &j[loop].nome[0]); //salva o nome do jogador
        j[loop].jogador_id = loop + 1; //salva o id do jogador
        j[loop].vidas = 5; //salva a quantidade de vidas do jogador
        ++loop; //incrementa o loop
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


mesa *criaMesa ()
{
    mesa *m;
    m = (mesa *) malloc (sizeof (mesa));
    return m;
}

int inserirBaralho (baralho *b) ///////////////////////////////////////////Consertar numeros repetidos///////////////////////////////

{
    int temp, loop_temp = 0;
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
            one:
            temp = rand() % 40; //gera um numero aleatorio entre 0 e 39

            //printf ("i: %i\n", i);
            //printf ("temp:          %i\n", temp);
            //printf ("topo: %i\n", b->topo);
            for (int j = 0; j < b->topo; j++) //loop para verificar se o numero temp ja existe como carta_id
            {
                if (temp == b->vetor[j].carta_id)
                {
                    //i--; //se o numero ja existe, volta o loop para gerar outro numero
                    //b->topo--; //volta o topo para nao adicionar o numero repetido
                    //printf ("numero ja existe\n");
                    goto one;
                    printf ("ERROR\n");
                    exit(1);
                }
            }
            //printf ("Antes %d\n", b->topo);
            b->vetor[b->topo].carta_id = temp; //se o numero nao existe, adiciona o numero ao vetor
            b->topo++;
            //printf ("Depois %d\n", b->topo);
        
        }
    return 1;
    }
}

carta* criaCarta () //cria o vetor de cartas
{
    carta *c;
	c = (carta *) malloc (40 * sizeof(carta));
	return c;
}

int constroiCarta (baralho *b, carta *c) 
{   
    for (int i = 0; i < MAX; i++)
    {
        c[i].carta_id = i;
        //printf ("carta_id: %i\n", c[i].carta_id);
        //printf ("Baralho: %i, %i de %i\n", b->vetor[i].carta_id, b->vetor[i].valor, b->vetor[i].naipe);
    }
    int count = 0; 
    //preencheBaralho (c, b); //Nao fica embaralhado
    for (int i = 0; i < MAX; i++)
    {
        switch (b->vetor[i].carta_id)
        {
            case 0: c[i].valor = 4; c[i].naipe = 1; count++; break;
            case 1: c[i].valor = 4; c[i].naipe = 2; count++; break;
            case 2: c[i].valor = 4; c[i].naipe = 3; count++; break;
            case 3: c[i].valor = 5; c[i].naipe = 1; count++; break;
            case 4: c[i].valor = 5; c[i].naipe = 2; count++; break;
            case 5: c[i].valor = 5; c[i].naipe = 3; count++; break;
            case 6: c[i].valor = 5; c[i].naipe = 4; count++; break;
            case 7: c[i].valor = 6; c[i].naipe = 1; count++; break;
            case 8: c[i].valor = 6; c[i].naipe = 2; count++; break;
            case 9: c[i].valor = 6; c[i].naipe = 3; count++; break;
            case 10: c[i].valor = 6; c[i].naipe = 4; count++; break;
            case 11: c[i].valor = 7; c[i].naipe = 2; count++; break;
            case 12: c[i].valor = 7; c[i].naipe = 4; count++; break;
            case 13: c[i].valor = 11; c[i].naipe = 1; count++; break;
            case 14: c[i].valor = 11; c[i].naipe = 2; count++; break;
            case 15: c[i].valor = 11; c[i].naipe = 3; count++; break;
            case 16: c[i].valor = 11; c[i].naipe = 4; count++; break;
            case 17: c[i].valor = 12; c[i].naipe = 1; count++; break;
            case 18: c[i].valor = 12; c[i].naipe = 2; count++; break;
            case 19: c[i].valor = 12; c[i].naipe = 3; count++; break;
            case 20: c[i].valor = 12; c[i].naipe = 4; count++; break;
            case 21: c[i].valor = 13; c[i].naipe = 1; count++; break;
            case 22: c[i].valor = 13; c[i].naipe = 2; count++; break;
            case 23: c[i].valor = 13; c[i].naipe = 3; count++; break;
            case 24: c[i].valor = 13; c[i].naipe = 4; count++; break;
            case 25: c[i].valor = 1; c[i].naipe = 1; count++; break;
            case 26: c[i].valor = 1; c[i].naipe = 3; count++; break;
            case 27: c[i].valor = 1; c[i].naipe = 4; count++; break;
            case 28: c[i].valor = 2; c[i].naipe = 1; count++; break;
            case 29: c[i].valor = 2; c[i].naipe = 2; count++; break;
            case 30: c[i].valor = 2; c[i].naipe = 3; count++; break;
            case 31: c[i].valor = 2; c[i].naipe = 4; count++; break;
            case 32: c[i].valor = 3; c[i].naipe = 1; count++; break;
            case 33: c[i].valor = 3; c[i].naipe = 2; count++; break;
            case 34: c[i].valor = 3; c[i].naipe = 3; count++; break;
            case 35: c[i].valor = 3; c[i].naipe = 4; count++; break;
            case 36: c[i].valor = 7; c[i].naipe = 1; count++; break;
            case 37: c[i].valor = 1; c[i].naipe = 2; count++; break;
            case 38: c[i].valor = 7; c[i].naipe = 3; count++; break;
            case 39: c[i].valor = 4; c[i].naipe = 4; count++; break;
            default: printf ("Erro! \n"); break;
        }
    }
    
    printf("count: %i\n", count);
    return count;
}

void preencheBaralho (carta *c, baralho *b) 
{
    for (int i = 0; i < 40; )
    {
        for (int j = 0; j < 40; j++)
        {
            if (b->vetor[i].carta_id == c[j].carta_id)
            {
                printf ("Carta %d I: ID:%d VALOR:%d NAIPE:%d\n", i, b->vetor[i].carta_id, b->vetor[i].valor, b->vetor[i].naipe);
                printf ("Carta %d J: ID:%d VALOR:%d NAIPE:%d\n", j, c[j].carta_id, c[j].valor, c[j].naipe);
                b->vetor[i] = c[j];
                i++;
            }
        }
        
    }
}

int calcularCartas (int num_jogadores, int num_cartas_mao)
{
    if (num_cartas_mao == 0)
    {
        num_cartas_mao = 5;
    }
    return num_cartas_mao;
}

int distribuirCartas (int num_cartas_mao, jogador *j, baralho *b, int num_jogadores)
{
    int count = 0;
    for (int i = 0; i < num_jogadores; i++)
    {
        for (int k = 0; k < num_cartas_mao; k++)
        {
            j[i].mao[k] = b->vetor[b->topo-1];
            b->topo--;
            count++;
        }
    }
    if (count == num_cartas_mao * num_jogadores)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void intToString (jogador *j, int num_cartas_mao, int num_jogadores)
{
    int count_extra = 0, count_naipe = 0;
    for (int i = 0; i < num_cartas_mao; i++)
    {
        switch (j->mao[i].naipe)
        {
            case 1:
                j->mao[i].naipe_char = "Ouros";
                count_naipe++;
                break;
            case 2:
                j->mao[i].naipe_char = "Espadas";
                count_naipe++;
                break;
            case 3:
                j->mao[i].naipe_char = "Copas";
                count_naipe++;
                break;
            case 4:
                j->mao[i].naipe_char = "Paus";
                count_naipe++;
                break;
        }
        switch (j->mao[i].valor)
        {
            case 1:
                j->mao[i].extras = "As";
                count_extra++;
                break;
            case 11:
                j->mao[i].extras = "Dama";
                count_extra++;
                break;
            case 12:
                j->mao[i].extras = "Valete";
                count_extra++;
                break;
            case 13:
                j->mao[i].extras = "Rei";
                count_extra++;
                break;
        }
    }
    //printf("\n");
    //printf("count_extra: %i\n", count_extra);
    //printf("count_naipe: %i\n", count_naipe);
    //printf("\n");
    /*if (count_extra > 0)
    {
        for (int i = 0; i < count_extra; i++)
        {
            printf ("Carta %d: %s de %s\n", i+1, j->mao[i].extras, j->mao[i].naipe_char);
        }
    }
    else
    {
        for (int i = 0; i < count_naipe; i++)
        {
            printf ("Carta %d: %d de %s\n", i+1, j->mao[i].valor, j->mao[i].naipe_char);
        }
    }
    //printf ("Carta %d: %d de %s\n", i+1, j->mao[i].valor, j->mao[i].naipe_char); */
}

void verificaMaiorCartaMesa (jogador *j, int count_of_cards_mesa, mesa *m, int num_jogadores)
{
    int maior_carta_mesa = 0;
    int posicao_maior_carta_mesa;
    for (int i = 0; i < count_of_cards_mesa; i++)
    {
        if (m->cartas_mesa[i].carta_id > maior_carta_mesa)
        {
            maior_carta_mesa = m->cartas_mesa[i].carta_id;
            posicao_maior_carta_mesa = i;
        }
    }

    j[posicao_maior_carta_mesa].turnos_vencidos++;

    for (int i = 0; i <num_jogadores; i++)
    {
        if (j[i].turnos_vencidos == j[i].vence_turnos)
        {
            printf ("O jogador %d fez todos os turnos\n", i);
        }
        else 
        {
            printf ("O jogador %d nao fez todos os turnos\n", i);
            j[i].vidas--;
        }
    }
}


/*    carta *c;

    c = (carta *) malloc (sizeof(carta));
    c->carta_id = ;
    c->valor = ;
    c->naipe = ;*/