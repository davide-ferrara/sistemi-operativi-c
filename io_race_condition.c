#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_NUM 10
#define N 1000

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

void *writers_without_lock(void *arg)
{
    FILE *fp = (FILE *)arg;

    for (int i = 0; i < N; i++)
    {
        fprintf(fp, "Thread %lu ha scritto qualcosa!\n", pthread_self());
    }

    return NULL;
}

void *writers_with_lock(void *arg)
{
    FILE *fp = (FILE *)arg;

    // Entrata sezione critica

    pthread_mutex_lock(&mutex.id);

    for (int i = 0; i < N; i++)
    {
        fprintf(fp, "Thread %lu ha scritto qualcosa!\n", pthread_self());
    }

    // Uscita sezione critica

    pthread_mutex_unlock(&mutex.id);

    return NULL;
}

int main(int argc, char **argv)
{
    char *fileName = "io_race_condition.txt";

    FILE *fp;
    Thread thread[THREAD_NUM];

    if (pthread_mutex_init(&mutex.id, &mutex.attr) == -1)
        return -1;

    if (access(fileName, F_OK))
        remove(fileName);

    fp = fopen(fileName, "w");

    for (int i = 0; i < THREAD_NUM; i++)
    {
        int thread_create = pthread_create(&thread[i].id, &thread[i].attr, &writers_without_lock, (void *)fp);
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

    return 0;
}