// PILHA DINAMICA//

#include <stdio.h>
#include <stdlib.h>

typedef struct elemento {
  int valor;

  struct elemento *anterior;
} elemento;

typedef struct pilha {
  elemento *topo;
} pilha;

pilha *criaPilha();

void liberaPilha(pilha *p);

int emPilha(pilha *p, int temp);

int retiraPilha(pilha *p, int *temp);

int pilhaCheia(pilha *p);

int pilhaVazia(pilha *p);

int main()
{
  pilha *p;

  int temp, inicio, escolha, descarte;

  while (inicio != 2)// loop inicial
    {
      printf(
        "\n1. Criar pilha\n"
        "2. Sair\n");

      scanf("%d", &inicio);

      switch (inicio)

        {
        case 1:

          p = criaPilha();// cria pilha (vetor e topo)
          do// loop de escolha
            {
              printf(
                "\n1. Colocar na pilha\n"// empilha um novo numero
                "2. Retirar da pilha\n"// desempilha um numero
                "3. Conferir se a pilha esta vazia\n"//
                "4. Conferir se a pilha esta cheia\n"// N funciona
                "5. Liberar a pilha e sair\n"// volta para o switch inicial
                );

              scanf("%d", &escolha);

              switch (escolha)

                {
                case 1:

                  printf("Digite o valor que quer colocar na fila: \n");

                  scanf("%d", &temp);

                  if (emPilha(p, temp) == -1)

                    {
                      printf("A pilha esta cheia\n");
                    }

                  else if (emPilha(p, temp) == 1)

                    {
                      printf("Numero adicionado: %i\n", temp);
                    }

                  else

                    {
                      printf("Error");
                    }

                  break;

                case 2:

                  if (retiraPilha(p, &descarte) == -1)

                    {
                      printf("A pilha esta vazia\n");
                    }

                  else if (retiraPilha(p, &descarte) == 1)

                    {
                      printf("Numero %i retirado\n", descarte);
                    }

                  break;

                case 3:

                  if (pilhaVazia(p) == 1)
                    {
                      printf("pilha vazia\n");
                    }

                  else
                    {
                      printf("pilha nao vazia\n");
                    }
                  break;

                /*case 4:
                   if (pilhaCheia(p) == 1)
                   {
                   printf ("pilha cheia\n");
                   }
                   else
                   {
                   printf ("pilha nao Cheia\n");
                   }
                   break; */
                case 5:
                  liberaPilha(p);
                  exit(0);
                  break;
                }
            } while (escolha != 6);

        case 2:
          return 0;
          break;
        }
    }

  return 0;
}

pilha *criaPilha()
{
  pilha *p;

  p = (pilha *)malloc(sizeof(pilha));

  p->topo = NULL;

  return p;
}

void liberaPilha(pilha *p)
{
  while (p->topo != NULL)

    {
      elemento *aux;

      aux = p->topo;

      p->topo = p->topo->anterior;

      free(aux);
    }

  free(p);
}

int emPilha(pilha *p, int temp)
{
  elemento *novo = (elemento *)malloc(sizeof(elemento));

  if (novo == NULL)

    {
      printf("Erro na alocacao de memoria");

      system("pause");
      return 0;
    }

  else

    {
      novo->valor = temp;

      novo->anterior = p->topo;

      p->topo = novo;

      return 1;
    }
}

int retiraPilha(pilha *p, int *descarte)
{
  if (pilhaVazia(p) == 1)

    {
      return -1;
    }

  else

    {
      *descarte = p->topo->valor;

      elemento *aux;

      aux = p->topo;

      p->topo = aux->anterior;

      free(aux);

      return 1;
    }
}

// int pilhaCheia (elemento n)
//{
//  if (n == NULL)
//{
// return 1;
// }
// else
//{
//  return 0;
//  }
//}

int pilhaVazia(pilha *p)
{
  if (p->topo == NULL)

    {
      return 1;
    }

  else

    {
      return 0;
    }
}
