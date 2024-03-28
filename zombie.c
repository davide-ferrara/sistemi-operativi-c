#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (pid > 0)
    {
        // Processo padre
        printf("Sono il processo padre con PID %d. Il processo figlio ha PID %d.\n", getpid(), pid);
        // Il processo padre termina subito senza attendere il processo figlio
        // La chiamata a wait() non viene effettuata
        return 0;
    }
    else
    {
        // Processo figlio
        printf("Sono il processo figlio con PID %d.\n", getpid());
        // Il processo figlio termina subito dopo la sua creazione
        // Non viene raccolto dal processo padre
        return 0;
    }

    return 0;
}
