#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define THREAD_NUM 10
#define N 10000
#define SEM_START 5

typedef struct
{
    pthread_t id;
    pthread_attr_t attr;
} Thread;

typedef struct
{
    pthread_mutex_t id;
    pthread_mutexattr_t attr;
} Mutex;

Mutex mutex;
sem_t sem;

void *writers_with_sem_and_lock(void *arg)
{
    FILE *fp = (FILE *)arg;

    sem_wait(&sem);
    pthread_mutex_lock(&mutex.id);
    // Entrata sezione critica

    for (int i = 0; i < N; i++)
    {
        fprintf(fp, "Thread %lu ha scritto qualcosa!\n", pthread_self());
    }

    // Uscita sezione critica
    pthread_mutex_unlock(&mutex.id);
    sem_post(&sem);

    return NULL;
}

// Questa ha sempre il rischio di race condtion se il semafore è inizializzato a un numero > 1
void *writers_with_sem(void *arg)
{
    FILE *fp = (FILE *)arg;

    // Entrata sezione critica

    sem_wait(&sem);

    for (int i = 0; i < N; i++)
    {
        fprintf(fp, "Thread %lu ha scritto qualcosa!\n", pthread_self());
    }

    // Uscita sezione critica

    sem_post(&sem);

    return NULL;
}

int main(int argc, char **argv)
{
    char *fileName = "io_race_condition_sem.txt";

    FILE *fp;
    Thread thread[THREAD_NUM];

    if (pthread_mutex_init(&mutex.id, &mutex.attr) == -1)
        return -1;

    if (access(fileName, F_OK))
        remove(fileName);

    fp = fopen(fileName, "w");

    if (sem_init(&sem, 0, SEM_START) == -1)
        return -1;

    for (int i = 0; i < THREAD_NUM; i++)
    {
        int thread_create = pthread_create(&thread[i].id, &thread[i].attr, &writers_with_sem, (void *)fp);
        if (thread_create == -1)
            return -1;
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        int thread_join = pthread_join(thread[i].id, NULL);
        if (thread_join == -1)
            return -1;
    }

    fclose(fp);

    if (pthread_mutex_destroy(&mutex.id) == -1)
        return -1;

    if (sem_destroy(&sem) == -1)
        return -1;

    return 0;
}