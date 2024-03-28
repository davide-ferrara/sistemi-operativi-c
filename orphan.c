#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{

    int status;
    pid_t PID;

    PID = fork();

    if (PID == -1)
        return -1;

    if (PID > 0)
    {
        // Parent Process
        printf("Sono il padre %d\n", getpid());
        printf("Sono il padre e terminerò immediatamente senza aspettare mio figlio...\n");
        return 0;
    }
    else
    {
        // Child Process
        printf("Sono il figlio %d, figlio di %d\n", getpid(), getppid());

        sleep(1);

        printf("Sono il figlio e non trovo mio padre...\nAdesso sono orfano :( \n");

        printf("Adesso sono figlio di %d\n", getppid());
        return 0;
    }

    // Controlla tramite comando ps -el il parent pid del figlio dopo l'abbandono del padre, dovrebbe essere systemd (init)...

    return 0;
}