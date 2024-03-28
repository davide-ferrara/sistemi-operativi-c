#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

#define THREAD_NUM 2

typedef struct
{
    pthread_t id;
    pthread_attr_t attr;
} Thread;

Thread thread[THREAD_NUM];

void *workers()
{
    printf("Sono il thread ID: %lu!\n", pthread_self());
}

// Esercizio 1 slide pthread
void *print_x_or_o(void *arg)
{
    char c = *((char *)arg);

    while (1)
    {
        fputc(c, stdout);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    char letters[2] = {'x',
                       'o'};

    // Creazione thread
    for (int i = 0; i < THREAD_NUM; i++)
    {
        pthread_create(&thread->id, &thread->attr, print_x_or_o, (void *)letters + i);
    }

    // Join thread
    for (int i = 0; i < THREAD_NUM; i++)
    {
        pthread_join(thread->id, NULL);
    }

    return 0;
}