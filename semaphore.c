#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>

#define THREAD_NUM 4
#define COSTANT 1000000

typedef struct
{
    pthread_t id;
    pthread_attr_t attr;
} Thread;

typedef struct
{
    sem_t id;
} Semaphore;

int count = 0;

void *increment(void *args)
{

    for (int i = 0; i < COSTANT; i++)
    {
        sem
            count++;
        // printf("Sono thread id: %lu, count is: %d \n", pthread_self(), count);
    }

    return NULL;
}

void *decrement(void *args)
{
    for (int i = 0; i < COSTANT; i++)
    {
        count--;

        // printf("Sono thread id: %lu, count is: %d \n", pthread_self(), count);
    }

    return NULL;
}

int main(int argc, char **argv)
{
    Thread thread[THREAD_NUM];
    Semaphore sem;

    sem_init(&sem.id, 0, 1);

    if (pthread_mutex_init(&mutex.id, &mutex.attr) != 0)
        return -1;

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (i % 2 == 0)
        {
            pthread_create(&thread[i].id, &thread[i].attr, &increment, (void *)&mutex);
        }
        else
        {
            pthread_create(&thread[i].id, &thread[i].attr, &decrement, (void *)&mutex);
        }
    }

    // Join fa in modo che il programma aspetti che tutti i thread finiscono di essere eseguiti prima di andare avanti
    for (int i = 0; i < THREAD_NUM; i++)
    {
        pthread_join(thread[i].id, NULL);
    }

    sem_destroy(&sem.id);

    if (count == 0)
    {
        fprintf(stderr, "Successo! Nessuna race condition rilevata!\nCount è %d come ci aspettavamo!\n", count);
        return 0;
    }
    else
    {
        fprintf(stderr, "Errore! Race condition rilevata!\nCount dovrebbe essere zero, è invece %d\n", count);
        return -1;
    }
}