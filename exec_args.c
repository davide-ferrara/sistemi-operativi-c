#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    // argc = args count
    // argv = args values
    // argv[0] = nome del programma

    printf("Numeri di parametri in riga di comandi: %d \n", argc);

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "--h"))
        {
            printf("Esempio menu tramite flags: \n --h, mostra il menù aiuto \n");
            break;
        }
        else
        {
            printf("Flag non valida, esegui exec_args --h per ulteriori informazioni \n");
            break;
        }
    }

    return 0;
}