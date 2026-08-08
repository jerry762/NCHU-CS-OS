#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

// #define ITER_PER_THREAD 25000000
#define ITER_PER_THREAD 1000

sem_t *mtx;
int count = 0;

void *inc(void *arg);
void *dec(void *arg);

int main()
{
    int i = 0;
    pthread_t id[4];

    mtx = sem_open("/sem_ex2", O_CREAT, S_IRUSR | S_IWUSR, 1);
    if (mtx == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    pthread_create(&id[0], NULL, dec, NULL);
    pthread_create(&id[1], NULL, inc, NULL);
    pthread_create(&id[2], NULL, dec, NULL);
    pthread_create(&id[3], NULL, inc, NULL);

    for (i = 0; i < 4; i++)
    {
        pthread_join(id[i], NULL);
    }

    printf("\noutput is %d\n", count);

    sem_close(mtx);

    sem_unlink("/sem_ex2");

    return 0;
}

void *inc(void *arg)
{
    int i = 0;

    for (i = 0; i < ITER_PER_THREAD; i++)
    {
        sem_wait(mtx);

        count++;
        printf("count = %d\n", count);

        sem_post(mtx);
    }

    return NULL;
}

void *dec(void *arg)
{
    int i = 0;

    for (i = 0; i < ITER_PER_THREAD; i++)
    {
        sem_wait(mtx);

        count--;
        printf("count = %d\n", count);

        sem_post(mtx);
    }

    return NULL;
}
