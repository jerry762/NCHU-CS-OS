#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

#define THREADS_SIZE 3
#define THREADS_TASK 3

#define SLOW_MODE 1 // 0 or 1

static int indicator = 0;
static pthread_mutex_t mtx;
static pthread_cond_t cond;

typedef void *(*threads_task)();

void *T1()
{
    const char msg[] = "1\t";

    while (1)
    {
        pthread_mutex_lock(&mtx);

        if (indicator % 3 == 0)
        {
            write(STDOUT_FILENO, msg, sizeof(msg) - 1);
            indicator++;
            pthread_cond_broadcast(&cond);

#if SLOW_MODE == 1
            sleep(1);
#endif

        }
        else
        {
            pthread_cond_wait(&cond, &mtx);
        }

        pthread_mutex_unlock(&mtx);
    }
}

void *T2()
{
    const char msg[] = "3\t";

    while (1)
    {
        pthread_mutex_lock(&mtx);

        if (indicator % 3 == 1)
        {
            write(STDOUT_FILENO, msg, sizeof(msg) - 1);
            indicator++;
            pthread_cond_broadcast(&cond);

#if SLOW_MODE == 1
            sleep(1);
#endif

        }
        else
        {
            pthread_cond_wait(&cond, &mtx);
        }

        pthread_mutex_unlock(&mtx);
    }
}

void *T3()
{
    const char msg[] = "5\t";

    while (1)
    {
        pthread_mutex_lock(&mtx);

        if (indicator % 3 == 2)
        {
            write(STDOUT_FILENO, msg, sizeof(msg) - 1);
            indicator++;
            pthread_cond_broadcast(&cond);

#if SLOW_MODE == 1
            sleep(1);
#endif

        }
        else
        {
            pthread_cond_wait(&cond, &mtx);
        }

        pthread_mutex_unlock(&mtx);
    }
}

void sigint(int sig_num)
{
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond);
    exit(0);
}

int main()
{
    signal(SIGINT, sigint);

    pthread_t threads[THREADS_SIZE];
    threads_task tasks[THREADS_TASK] = {T1, T2, T3};

    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&cond, NULL);

    for (int i = 0; i < THREADS_SIZE; i++)
    {
        pthread_create(&threads[i], NULL, tasks[i], NULL);
    }
    
    for (int i = 0; i < THREADS_SIZE; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}