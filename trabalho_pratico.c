#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#define MAX 40

////////////////////////BARALHO///////////////

typedef struct carta
{
    int valor; // 1 / 2 / 3 / 4 / 5 / 6 / 7 / 11 / 12 / 13
    int naipe; // 1 - ouros / 2 – espadas / 3 – copas / 4 - paus.
    char *naipe_char;
    char *extras; // As e familia real
    int carta_id; // 1 a 40
    // int poder;
} carta;

typedef struct baralho
{
    int topo;
    carta vetor[MAX];
} baralho;

typedef struct jogador
{
    char nome[20];
    int vidas;      // comeca com 5 vidas
    int jogador_id; // 1 a 8
    carta mao[5];   // 1 a 5 cartas
    int vence_turnos;
    int turnos_vencidos;
} jogador;

typedef struct mesa
{
    carta cartas_mesa[5];
} mesa;

baralho *criaBaralho();
void liberaBaralho(baralho *b);
mesa *criaMesa();
int inserirBaralho(baralho *b);
int numeroJogadores();
jogador *criaJogadores(int num_jogadores);
int alocaCartasMao(jogador *j, int num_jogadores, int num_cartas_mao);
void liberaJogador(jogador *j);
void nomeJogadores(jogador *j, int num_jogadores);
carta *criaCarta();
int constroiCarta(baralho *b, carta *c);
void preencheBaralho(carta *c, baralho *b);
int calcularCartas(int num_cartas_mao, int *num_cartas_status);
int distribuirCartas(int num_cartas_mao, jogador *j, baralho *b, int num_jogadores);
void intToString(jogador *j, int num_cartas_mao, int num_jogadores);
int verificaMaiorCartaMesa(jogador *j, mesa *m, int count_of_cards_mesa);
void verificaRodadasVencidas(jogador *j, int num_jogadores);
void printCartasMao(jogador *j, int num_jogadores, int num_cartas_mao);
void printCartasJogador(jogador *j, int posicao, int num_cartas_mao);
void printVidas(jogador *j, int num_jogadores, FILE *f);
void red();
void yellow();
void reset();

int main()
{
    baralho *b;
    jogador *j;
    carta *c;
    mesa *m;
    FILE *f;

    int temp, inserir, num_jogadores, num_cartas_jogador, num_cartas_mao = 5, num_cartas_status = 1, constroi, cartas_distribuidas, count_of_cards_mesa = 0;
    int jogador_da_vez = 0;
    // Cria arquivo
    f = fopen("log_jogo.txt", "w");

    if (f != NULL)
        fprintf(f, "Arquivo criado com sucesso\n");
    else
    {
        fprintf(f, "Erro na criacao de arquivo\n");
        return 0;
    }

    // Pede o numero de jogadores
    num_jogadores = numeroJogadores();
    printf("%d jogadores\n", num_jogadores);

    // Cria a lista de jogadores
    j = criaJogadores(num_jogadores);
    if (j == NULL)
    {
        fprintf(f, "Erro ao criar a lista de jogadores\n");
        return 0;
    }
    else
        fprintf(f, "Lista de jogadores criada com sucesso\n");

    // cria baralho (vetor e topo)
    b = criaBaralho();
    if (b == NULL)
    {
        fprintf(f, "Erro ao criar o baralho\n");
        return 0;
    }
    else
        fprintf(f, "Baralho criado com sucesso\n");

    // criar cartas
    c = criaCarta();
    if (c == NULL)
    {
        fprintf(f, "Erro ao criar as cartas\n");
        return 0;
    }
    else
        fprintf(f, "Sucesso ao criar as cartas\n");

    // Cria a mesa
    m = criaMesa();

    // Pegar o nome dos jogadores
    nomeJogadores(j, num_jogadores);

    // inserir cartas no baralho
    inserir = inserirBaralho(b); // Cria um veor de numeros aleatorios entre 0 e 39

    if (inserir == 0)
    {
        fprintf(f, "Erro ao inserir cartas no baralho, baralho cheio\n");
        return 0;
    }
    else if (inserir == 1)
        fprintf(f, "Cartas adicionadas com sucesso\n");

    // Construir as cartas
    constroi = constroiCarta(b, c); // Preenche o vetor de cartas com os valores e naipes
    if (constroi != 40)
    {
        fprintf(f, "Erro ao construir as cartas\n");
        return 0;
    }
    else if (constroi == 40)
        fprintf(f, "Cartas construidas com sucesso\n");

    // preencher o baralho
    preencheBaralho(c, b); // Preenche o baralho com as cartas

    // calcular o numero de cartas
    // num_cartas_mao = calcularCartas(num_cartas_mao, &num_cartas_status); // IF num_cartas_mao = 5, 4, 3, 2 = num_cartas_status = -1 ELSE IF num_cartas_mao = 1 = num_cartas_status = 1
    // printf("Numero de cartas por jogador: %d\n", num_cartas_mao);

    do
    {
        fprintf(f, "\nNOVA RODADA\n");
        // distribuir as cartas
        cartas_distribuidas = distribuirCartas(num_cartas_mao, j, b, num_jogadores);
        if (cartas_distribuidas == 0)
        {
            fprintf(f, "Erro ao distribuir as cartas\n");
            return 0;
        }
        else if (cartas_distribuidas == 1)
            fprintf(f, "Cartas distribuidas com sucesso\n");

        /////////////////****************Aloca Espaco para o naipe e as cartas especiais****************/////////////////////
        if (alocaCartasMao(j, num_jogadores, num_cartas_mao) == 0)
        {
            fprintf(f, "Erro ao alocar espaco para as cartas\n");
            return 0;
        }
        else
            fprintf(f, "Espaco alocado com sucesso\n");

        // Comeca o jogo

        // Passa os naipes de int para string
        intToString(j, num_cartas_mao, num_jogadores);

        // Print de cartas_distribuidas
        // printCartasMao(j, num_jogadores, num_cartas_mao);

        // Escolha de turnos

        // Dentro do jogo

        fprintf(f, "numero de cartas na mao: %d\n", num_cartas_mao);
        num_cartas_jogador = num_cartas_mao;

        for (int l = 0; l < num_jogadores; l++) // Dentro das rodadas
        {
            j[l].vence_turnos = -1; // Reseta os turnos q o jogador precisa vencer
        }

        int soma_turnos = 0; // soma tem q ser igual ao numero de cartas + 1
        int turno_temp = 0;

        for (int g = 0; g < num_cartas_mao; g++) // Dentro das rodadas
        {
            fprintf(f, "jogador_da_vez: %d\n", jogador_da_vez);
            for (int i = 0; i < num_jogadores; i++) // Dentro de uma rodada
            {
                if (i == num_jogadores)
                    i = 0;
                system("cls");
                if (j[i].vence_turnos == -1) // roda apenas no primeiro turno
                {
                    printCartasJogador(j, i, num_cartas_jogador);
                TURNOS:
                    printf("\nEscolha quantos turnos voce faz: \n"); /// Depende da quantidade de cartas na mao
                    scanf("%d", &turno_temp);

                    if (turno_temp < 0 || turno_temp > (num_cartas_mao + 1))
                    {
                        printf("\nNumero invalido, tente novamente\n");
                        goto TURNOS;
                    }
                    else if (i == num_jogadores - 1 && (soma_turnos + turno_temp) < num_cartas_mao + 1)
                    {
                        printf("\nNumero invalido, tente novamente, numero minimo %d turnos\n", (num_cartas_mao + 1) - soma_turnos);
                        goto TURNOS;
                    }
                    else
                    {
                        printf("Voce escolheu %d turnos\n", turno_temp);
                        soma_turnos += turno_temp;
                        fprintf(f, "soma_turnos: %d\n", soma_turnos);
                        j[i].vence_turnos = turno_temp;
                    }
                }
            }

            // Escolha de cartas e jogadas

            for (int i = 0; i < num_jogadores; i++)
            {
                system("cls");
                printVidas(j, num_jogadores, f);
                printCartasJogador(j, i, num_cartas_jogador);
            CARTAS:
                printf("\nEscolha qual carta deseja jogar\n");
                scanf("%d", &temp);
                temp--;
                if (temp < 0 || temp > 4)
                {
                    printf("Numero invalido, tente novamente\n");
                    goto CARTAS;
                }
                else
                {
                    if (j[i].mao[temp].valor == 1)
                    {
                        printf("%s de %s,", j[i].mao[temp].extras, j[i].mao[temp].naipe_char);
                        fprintf(f, "\nJogador %d: %s de %s,", j[i].jogador_id, j[i].mao[temp].extras, j[i].mao[temp].naipe_char);
                    }
                    else if (j[i].mao[temp].valor == 11 || j[i].mao[temp].valor == 12 || j[i].mao[temp].valor == 13)
                    {
                        printf("%s de %s, ", j[i].mao[temp].extras, j[i].mao[temp].naipe_char);
                        fprintf(f, "\nJogador %d: %s de %s, ", j[i].jogador_id, j[i].mao[temp].extras, j[i].mao[temp].naipe_char);
                    }
                    else
                    {
                        printf("%d de %s, ", j[i].mao[temp].valor, j[i].mao[temp].naipe_char);
                        fprintf(f, "\nJogador %d: %d de %s, ", j[i].jogador_id, j[i].mao[temp].valor, j[i].mao[temp].naipe_char);
                    }
                    m->cartas_mesa[count_of_cards_mesa] = j[i].mao[temp];
                    count_of_cards_mesa++;
                    j[i].mao[temp] = j[i].mao[num_cartas_jogador - 1]; // Troca a carta jogada com a ultima carta da mao

                    system("pause"); // Pausa o programa
                    system("cls");   // Limpa a tela
                    /* Tentativa de mudar a ordem do jogo baseado em quem ganhou a ultima rodada
                    if (i == num_jogadores - 1)
                        i = -1;
                    printf("i: %d\n", i);
                    */
                }
            }
            int vencedor_turno = verificaMaiorCartaMesa(j, m, count_of_cards_mesa);
            printf("Vencedor do turno: %s \n", j[vencedor_turno].nome);
            fprintf(f, "\nVencedor do turno: %s \n", j[vencedor_turno].nome);
            num_cartas_jogador--;    // Diminui o numero de cartas do jogador
            count_of_cards_mesa = 0; // Reseta o numero de cartas na mesa
            // jogador_da_vez = vencedor_turno;

            printVidas(j, num_jogadores, f);

            system("pause");

            /*
            red();
            printf("num_cartas_jogador: %d\n", num_cartas_jogador);
            reset();
            */
        }
        // Verifica se o jogador venceu a rodada
        verificaRodadasVencidas(j, num_jogadores);

    LOOP_ELIMINADO:
        int aux_num_jogadores = num_jogadores;
        for (int i = 0; i < aux_num_jogadores; i++)
        {
            printf("Jogador %s: %d vidas \n", j[i].nome, j[i].vidas);
            if (j[i].vidas <= 0 && num_jogadores > 1)
            {
                printf("%s - Eliminado \n", j[i].nome);
                fprintf(f, "%s - Eliminado \n", j[i].nome);
                j[i] = j[num_jogadores - 1];
                num_jogadores--;
                goto LOOP_ELIMINADO;
            }
        }

        for (int i = 0; i < num_jogadores; i++)
        {
            j[i].turnos_vencidos = 0; // Zera os turnos vencidos
        }
        num_cartas_mao = calcularCartas(num_cartas_mao, &num_cartas_status); // IF num_cartas_mao = 5, 4, 3, 2 = num_cartas_status = -1 ELSE IF num_cartas_mao = 1, 0 = num_cartas_status = 1

    } while (num_jogadores != 1);

    printf("Vencedor: %s com %d vidas\n", j[0].nome, j[0].vidas);
    fprintf(f, "Vencedor: %s com %d vidas\n", j[0].nome, j[0].vidas);
    printf("Fim de jogo\n");

    fclose(f);
    free(b);
    free(j);
    free(c);
    system("pause"); // Pausa o programa
    return 0;
}

int numeroJogadores()
{
    int num_jogadores, loop = 0, temp;
    do
    {
        printf("Digite o numero de jogadores (2 a 8): \n");
        scanf("%d", &temp);
        if (temp < 2 || temp > 8)
        {
            printf("numero de jogadores invalidos\n");
        }
        else
        {
            num_jogadores = temp;
            loop = 1;
        }
    } while (loop == 0);

    return num_jogadores;
}

jogador *criaJogadores(int num_jogadores)
{
    jogador *j;
    j = (jogador *)malloc(num_jogadores * sizeof(jogador)); // aloca memoria para a lista de jogadores
    return j;                                               // retorna a lista de jogadores
}

int alocaCartasMao(jogador *j, int num_jogadores, int num_cartas_mao)
{
    for (int i = 0; i < num_jogadores; i++)
    {
        for (int k = 0; k < num_cartas_mao; k++)
        {
            j[i].mao[k].extras = (char *)malloc(20 * sizeof(char));     // aloca espaco para as cartas especiais
            j[i].mao[k].naipe_char = (char *)malloc(20 * sizeof(char)); // aloca espaco para o naipe
        }
        if (j->mao[0].extras == NULL || j->mao[0].naipe_char == NULL) // verifica se alocou espaco
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    return -1;
}

void liberaJogador(jogador *j)
{
    free(j);
}

void nomeJogadores(jogador *j, int num_jogadores)
{
    int loop = 0;
    do
    {
        printf("Digite o nome do %i jogador\n", loop + 1); // pede o nome do jogador
        scanf("%s", &j[loop].nome[0]);                     // salva o nome do jogador
        j[loop].jogador_id = loop + 1;                     // salva o id do jogador
        j[loop].vidas = 5;                                 // salva a quantidade de vidas do jogador
        j[loop].turnos_vencidos = 0;
        j[loop].vence_turnos = 0;
        ++loop; // incrementa o loop
    } while (loop < num_jogadores);
}

baralho *criaBaralho()
{
    baralho *b;
    b = (baralho *)malloc(sizeof(baralho)); // aloca memoria para o baralho
    b->topo = 0;                            // inicializa o topo
    return b;                               // retorna o baralho
}

void liberaBaralho(baralho *b)
{
    free(b);
}

mesa *criaMesa()
{
    mesa *m;
    m = (mesa *)malloc(sizeof(mesa));
    return m;
}

int inserirBaralho(baralho *b) // insere um numero no baralho

{
    int temp;
    srand(time(NULL)); // inicializa o gerador de numeros aleatorios
    if (b->topo == MAX)
    {
        printf("Baralho cheio\n");
        return 0;
    }

    else
    {

        for (int i = 0; i < MAX; i++)
        {
        one:
            temp = rand() % 40; // gera um numero aleatorio entre 0 e 39

            for (int j = 0; j < b->topo; j++) // loop para verificar se o numero temp ja existe como carta_id
            {
                if (temp == b->vetor[j].carta_id) // se o numero ja existe, gera outro numero
                {
                    goto one;
                    printf("ERROR\n");
                    exit(1);
                }
            }
            b->vetor[b->topo].carta_id = temp; // se o numero nao existe, adiciona o numero ao vetor
            b->topo++;
        }
        return 1;
    }
}

carta *criaCarta() // cria o vetor de cartas
{
    carta *c;
    c = (carta *)malloc(40 * sizeof(carta));
    return c;
}

int constroiCarta(baralho *b, carta *c)
{
    for (int i = 0; i < MAX; i++)
    {
        c[i].carta_id = i;
        // printf ("carta_id: %i\n", c[i].carta_id);
        // printf ("Baralho: %i, %i de %i\n", b->vetor[i].carta_id, b->vetor[i].valor, b->vetor[i].naipe);
    }
    int count = 0;
    // preencheBaralho (c, b); //Nao fica embaralhado
    for (int i = 0; i < MAX; i++)
    {
        switch (b->vetor[i].carta_id)
        {
        case 0:
            c[i].valor = 4;
            c[i].naipe = 1;
            count++;
            break;
        case 1:
            c[i].valor = 4;
            c[i].naipe = 2;
            count++;
            break;
        case 2:
            c[i].valor = 4;
            c[i].naipe = 3;
            count++;
            break;
        case 3:
            c[i].valor = 5;
            c[i].naipe = 1;
            count++;
            break;
        case 4:
            c[i].valor = 5;
            c[i].naipe = 2;
            count++;
            break;
        case 5:
            c[i].valor = 5;
            c[i].naipe = 3;
            count++;
            break;
        case 6:
            c[i].valor = 5;
            c[i].naipe = 4;
            count++;
            break;
        case 7:
            c[i].valor = 6;
            c[i].naipe = 1;
            count++;
            break;
        case 8:
            c[i].valor = 6;
            c[i].naipe = 2;
            count++;
            break;
        case 9:
            c[i].valor = 6;
            c[i].naipe = 3;
            count++;
            break;
        case 10:
            c[i].valor = 6;
            c[i].naipe = 4;
            count++;
            break;
        case 11:
            c[i].valor = 7;
            c[i].naipe = 2;
            count++;
            break;
        case 12:
            c[i].valor = 7;
            c[i].naipe = 4;
            count++;
            break;
        case 13:
            c[i].valor = 11;
            c[i].naipe = 1;
            count++;
            break;
        case 14:
            c[i].valor = 11;
            c[i].naipe = 2;
            count++;
            break;
        case 15:
            c[i].valor = 11;
            c[i].naipe = 3;
            count++;
            break;
        case 16:
            c[i].valor = 11;
            c[i].naipe = 4;
            count++;
            break;
        case 17:
            c[i].valor = 12;
            c[i].naipe = 1;
            count++;
            break;
        case 18:
            c[i].valor = 12;
            c[i].naipe = 2;
            count++;
            break;
        case 19:
            c[i].valor = 12;
            c[i].naipe = 3;
            count++;
            break;
        case 20:
            c[i].valor = 12;
            c[i].naipe = 4;
            count++;
            break;
        case 21:
            c[i].valor = 13;
            c[i].naipe = 1;
            count++;
            break;
        case 22:
            c[i].valor = 13;
            c[i].naipe = 2;
            count++;
            break;
        case 23:
            c[i].valor = 13;
            c[i].naipe = 3;
            count++;
            break;
        case 24:
            c[i].valor = 13;
            c[i].naipe = 4;
            count++;
            break;
        case 25:
            c[i].valor = 1;
            c[i].naipe = 1;
            count++;
            break;
        case 26:
            c[i].valor = 1;
            c[i].naipe = 3;
            count++;
            break;
        case 27:
            c[i].valor = 1;
            c[i].naipe = 4;
            count++;
            break;
        case 28:
            c[i].valor = 2;
            c[i].naipe = 1;
            count++;
            break;
        case 29:
            c[i].valor = 2;
            c[i].naipe = 2;
            count++;
            break;
        case 30:
            c[i].valor = 2;
            c[i].naipe = 3;
            count++;
            break;
        case 31:
            c[i].valor = 2;
            c[i].naipe = 4;
            count++;
            break;
        case 32:
            c[i].valor = 3;
            c[i].naipe = 1;
            count++;
            break;
        case 33:
            c[i].valor = 3;
            c[i].naipe = 2;
            count++;
            break;
        case 34:
            c[i].valor = 3;
            c[i].naipe = 3;
            count++;
            break;
        case 35:
            c[i].valor = 3;
            c[i].naipe = 4;
            count++;
            break;
        case 36:
            c[i].valor = 7;
            c[i].naipe = 1;
            count++;
            break;
        case 37:
            c[i].valor = 1;
            c[i].naipe = 2;
            count++;
            break;
        case 38:
            c[i].valor = 7;
            c[i].naipe = 3;
            count++;
            break;
        case 39:
            c[i].valor = 4;
            c[i].naipe = 4;
            count++;
            break;
        default:
            printf("Erro! \n");
            break;
        }
    }

    // printf("count: %i\n", count);
    return count;
}

void preencheBaralho(carta *c, baralho *b)
{
    for (int i = 0; i < 40; i++)
    {
        b->vetor[i].valor = c[i].valor;
        b->vetor[i].naipe = c[i].naipe;
    }
}

int calcularCartas(int num_cartas_mao, int *num_cartas_status)
{
    yellow();
    printf("num_cartas_mao: %i, num_cartas_status: %i \n", num_cartas_mao, *num_cartas_status);
    reset();

    if (num_cartas_mao == 5)
        *num_cartas_status = -1;
    else if (num_cartas_mao == 1)
        *num_cartas_status = 1;

    if (*num_cartas_status == 1)
        num_cartas_mao++;
    else
        num_cartas_mao--;

    red();
    printf("num_cartas_mao: %i, num_cartas_status: %i \n", num_cartas_mao, *num_cartas_status);
    reset();
    return num_cartas_mao;
}

int distribuirCartas(int num_cartas_mao, jogador *j, baralho *b, int num_jogadores)
{
    int count = 0;
    for (int i = 0; i < num_jogadores; i++)
    {
        for (int k = 0; k < num_cartas_mao; k++)
        {
            j[i].mao[k] = b->vetor[b->topo - 1];
            b->topo--;
            count++;
        }
    }
    if (count == num_cartas_mao * num_jogadores)
        return 1;
    else
        return 0;
}

void intToString(jogador *j, int num_cartas_mao, int num_jogadores)
{
    int count_extra = 0, count_naipe = 0;

    for (int i = 0; i < num_jogadores; i++)
    {
        for (int k = 0; k < num_cartas_mao; k++)
        {
            switch (j[i].mao[k].naipe)
            {
            case 1:
                j[i].mao[k].naipe_char = "Ouros";
                count_naipe++;
                break;
            case 2:
                j[i].mao[k].naipe_char = "Espadas";
                count_naipe++;
                break;
            case 3:
                j[i].mao[k].naipe_char = "Copas";
                count_naipe++;
                break;
            case 4:
                j[i].mao[k].naipe_char = "Paus";
                count_naipe++;
                break;
            }

            switch (j[i].mao[k].valor)
            {
            case 1:
                j[i].mao[k].extras = "As";
                count_extra++;
                break;
            case 11:
                j[i].mao[k].extras = "Dama";
                count_extra++;
                break;
            case 12:
                j[i].mao[k].extras = "Valete";
                count_extra++;
                break;
            case 13:
                j[i].mao[k].extras = "Rei";
                count_extra++;
                break;
            }
        }
    }
}

int verificaMaiorCartaMesa(jogador *j, mesa *m, int count_of_cards_mesa)
{
    int maior_carta_mesa = 0;
    int posicao_maior_carta_mesa = 0;

    for (int i = 0; i < count_of_cards_mesa; i++)
    {
        if (m->cartas_mesa[i].carta_id > maior_carta_mesa)
        {
            maior_carta_mesa = m->cartas_mesa[i].carta_id;
            posicao_maior_carta_mesa = i;
        }
    }

    j[posicao_maior_carta_mesa].turnos_vencidos++;

    return posicao_maior_carta_mesa;
}

void verificaRodadasVencidas(jogador *j, int num_jogadores)
{
    for (int i = 0; i < num_jogadores; i++)
    {
        if (j[i].turnos_vencidos == j[i].vence_turnos)
        {
            printf("O jogador %s fez todos os turnos\n", j[i].nome);
        }
        else if (j[i].turnos_vencidos < j[i].vence_turnos)
        {
            printf("O jogador %s nao fez todos os turnos\n", j[i].nome);
            j[i].vidas = j[i].vidas - (j[i].vence_turnos - j[i].turnos_vencidos); // verifica quantas vidas o jogador perdeu
        }
        else if (j[i].turnos_vencidos > j[i].vence_turnos)
        {
            printf("O jogador %s fez mais turnos do que o necessario\n", j[i].nome);
            j[i].vidas = j[i].vidas - (j[i].turnos_vencidos - j[i].vence_turnos); // verifica quantas vidas o jogador perdeu
        }
        else
        {
            printf("Erro na funcao verificaRodadasVencidas\n");
        }
    }
}

void printCartasMao(jogador *j, int num_jogadores, int num_cartas_mao)
{
    for (int i = 0; i < num_jogadores; i++)
    {
        printf("Jogador %s: ", j[i].nome);

        for (int k = 0; k < num_cartas_mao; k++)
        {
            if (j[i].mao[k].valor == 1)
            {
                printf("%s de %s, ", j[i].mao[k].extras, j[i].mao[k].naipe_char);
            }
            else if (j[i].mao[k].valor == 11 || j[i].mao[k].valor == 12 || j[i].mao[k].valor == 13)
            {
                printf("%s de %s, ", j[i].mao[k].extras, j[i].mao[k].naipe_char);
            }
            else
            {
                printf("%d de %s, ", j[i].mao[k].valor, j[i].mao[k].naipe_char);
            }
        }
        printf("\n");
    }
}

void printCartasJogador(jogador *j, int posicao, int num_cartas_jogador)
{
    printf("Jogador %s: ", j[posicao].nome);

    for (int k = 0; k < num_cartas_jogador; k++)
    {
        if (j[posicao].mao[k].valor == 1)
        {
            printf("%s de %s, ", j[posicao].mao[k].extras, j[posicao].mao[k].naipe_char);
        }
        else if (j[posicao].mao[k].valor == 11 || j[posicao].mao[k].valor == 12 || j[posicao].mao[k].valor == 13)
        {
            printf("%s de %s, ", j[posicao].mao[k].extras, j[posicao].mao[k].naipe_char);
        }
        else
        {
            printf("%d de %s, ", j[posicao].mao[k].valor, j[posicao].mao[k].naipe_char);
        }
    }
    printf("\n");
}

void printVidas(jogador *j, int num_jogadores, FILE *f)
{
    for (int k = 0; k < num_jogadores; k++)
    {
        printf("%s: %d vidas, turnos vencidos: %d, vencer: %d\n", j[k].nome, j[k].vidas, j[k].turnos_vencidos, j[k].vence_turnos);
        fprintf(f, "%s: %d vidas, turnos vencidos: %d, vencer: %d\n", j[k].nome, j[k].vidas, j[k].turnos_vencidos, j[k].vence_turnos);
    }
}

void red()
{
    printf("\033[1;31m");
}

void yellow()
{
    printf("\033[1;33m");
}

void reset()
{
    printf("\033[0m");
}

/*    carta *c;

    c = (carta *) malloc (sizeof(carta));
    c->carta_id = ;
    c->valor = ;
    c->naipe = ;*/