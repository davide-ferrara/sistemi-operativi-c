#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void routine(char *string)
{
    for (int i = 0; i < 100; i++)
        printf("%s\n", string);
}

int main(int argc, char *argv[])
{
    // Numeri dei processi = 2 ^ Numeri di Fork
    int status;
    pid_t PID;
    PID = fork();

    if (PID == -1)
        exit(-1);

    if (PID == 0)
    {
        printf("Processo Figlio PID: %i, mio padre è %i!\n", getpid(), getppid());
        routine("Il Figlio sta facendo qualcosa...");
        exit(0);
    }
    else
    {
        // Aspetta che il processo figlio finisca... (Prova a rimuoverlo per vedere la differenza!)
        pid_t child_PID = wait(&status);
        if (WIFEXITED(status))
        {
            printf("Processo Padre PID: %i!\n", getpid());
            printf("Il processo figlio %i è terminato correttamente! (Status code: %i)\n", child_PID, WEXITSTATUS(status));
            routine("Il padre sta facendo qualcosa...");
            exit(0);
        }
        else
        {
            printf("Il figlio è diventato uno zombiee! %i \n", WEXITSTATUS(status));
            exit(-1);
        }
    }

    exit(0);
}