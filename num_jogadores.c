#include "stdio.h"
#include "stdlib.h"


int main ()
{
    int temp, num_jogadores, loop = 0;

    do {
        printf ("Digite o numero de jogadores (2 a 8): \n");
        scanf ("%d", &temp);
        if (temp < 2 || temp > 8)
        {
            printf ("Numero de jogadores invalidos\n");
        }
        else 
        {
            num_jogadores = temp;
            loop = 1;
        }
    } while (loop == 0);
    printf ("%d jogadores\n", num_jogadores);
    return 0;
}