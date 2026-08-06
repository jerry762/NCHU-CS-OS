#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define ADDITION_THREADS_SIZE 2
#define SUBSTRACTION_THREADS_SIZE 1

static int buffer = 0;
static pthread_mutex_t mtx;

void *addition(void *arg)
{
    int n = *((int *)arg);

    for (int i = 0; i < n; i++)
    {
        pthread_mutex_lock(&mtx);
        buffer += 2;
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

void *substraction(void *arg)
{
    int n = *((int *)arg);

    for (int i = 0; i < n; i++)
    {
        pthread_mutex_lock(&mtx);
        buffer -= 2;
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int iter_per_threads;
    pthread_t threads_add[ADDITION_THREADS_SIZE];
    pthread_t threads_sub[SUBSTRACTION_THREADS_SIZE];

    pthread_mutex_init(&mtx, NULL);

    if (argc < 2)
    {
        iter_per_threads = 1000000;
    }
    else
    {
        iter_per_threads = atoi(argv[1]);
    }
    
    for (int i = 0; i < ADDITION_THREADS_SIZE; i++)
    {
        pthread_create(&threads_add[i], NULL, addition, &iter_per_threads);
    }

    for (int i = 0; i < SUBSTRACTION_THREADS_SIZE; i++)
    {
        pthread_create(&threads_sub[i], NULL, substraction, &iter_per_threads);
    }
    
    for (int i = 0; i < ADDITION_THREADS_SIZE; i++)
    {
        pthread_join(threads_add[i], NULL);
    }

    for (int i = 0; i < SUBSTRACTION_THREADS_SIZE; i++)
    {
        pthread_join(threads_sub[i], NULL);
    }
    
    pthread_mutex_destroy(&mtx);

    printf("Result: %d\n", buffer);
    return 0;
}
