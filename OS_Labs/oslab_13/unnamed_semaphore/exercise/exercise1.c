#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

//#define ITER_PER_THREAD 25000000
#define ITER_PER_THREAD 1000

sem_t mtx;
int count = 0;

void inc(void);
void dec(void);

int main(void)
{
    int i = 0;
    sem_init(&mtx, 0, 1);
    pthread_t id[4];

    pthread_create(&id[0], NULL, (void *)dec, NULL);
    pthread_create(&id[1], NULL, (void *)inc, NULL);
    pthread_create(&id[2], NULL, (void *)dec, NULL);
    pthread_create(&id[3], NULL, (void *)inc, NULL);

    for (i = 0; i < 4; i++)
    {
        pthread_join(id[i], NULL);
    }

    sem_destroy(&mtx);

    printf("\noutput is %d\n", count);
    pthread_exit(NULL);
}

void inc(void)
{
    int i = 0;

    for (i = 0; i < ITER_PER_THREAD; i++)
    {
        sem_wait(&mtx);

        count++;
        printf("count = %d\n", count);

        sem_post(&mtx);
    }

    pthread_exit(NULL);
}

void dec(void)
{
    int i = 0;

    for (i = 0; i < ITER_PER_THREAD; i++)
    {
        sem_wait(&mtx);

        count--;
        printf("count = %d\n", count);

        sem_post(&mtx);
    }

    pthread_exit(NULL);
}
