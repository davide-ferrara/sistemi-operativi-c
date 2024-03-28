#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define _BUFFER_SIZE 128
#define _READ_END 0
#define _WRITE_END 1

int main(int argc, char **argv)
{

    // File descriptor
    int fd[2], status_code;
    pid_t PID;

    if (pipe(fd) == -1)
        return -1;

    PID = fork();

    if (PID == -1)
        return -1;

    if (PID > 0)
    {
        // Parent Process
        char read_buffer[_BUFFER_SIZE];

        wait(&status_code);

        if (WIFEXITED(status_code) != 0)
            return -1;

        printf("Sono il padre: PID = %d\n", getpid());

        close(fd[_WRITE_END]);
        read(fd[_READ_END], read_buffer, _BUFFER_SIZE);
        close(fd[_READ_END]);

        printf("%s", read_buffer);
        return 0;
    }
    else
    {
        // Child Process
        char msg[_BUFFER_SIZE] = "Ciao sono il processo figlio!\nStiamo comunicando tramite un pipe!\n";

        printf("Sono il figlio: PID = %d, mio padre è PID: %d\n", getpid(), getppid());

        close(fd[_READ_END]);
        write(fd[_WRITE_END], msg, strlen(msg));
        close(fd[_WRITE_END]);
        return 0;
    }

    return 0;
}