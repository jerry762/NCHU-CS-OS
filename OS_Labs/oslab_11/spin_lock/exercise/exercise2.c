#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define PRODUCER_THREADS_SIZE 3
#define CONSUMER_THREADS_SIZE 3

#define THREAD_ITER_TIMES 100
#define BUFFER_SIZE 10

int produced_count = 0;
int consumed_count = 0;
int buffer = 0;
pthread_spinlock_t spinlock;

void *producer_task(void *arg)
{
    int id = *((int *)arg);

    for (int i = 0; i < THREAD_ITER_TIMES; i++)
    {
        pthread_spin_lock(&spinlock);

        if (buffer < BUFFER_SIZE)
        {
            buffer++;
            printf("Producer %d, count = %d\n", id, buffer);
            produced_count++;
        }
        else
        {
            i--;
        }
        pthread_spin_unlock(&spinlock);
    }
    return NULL;
}

void *consumer_task(void *arg)
{
    int id = *((int *)arg);

    for (int i = 0; i < THREAD_ITER_TIMES; i++)
    {
        pthread_spin_lock(&spinlock);

        if (buffer > 0)
        {
            buffer--;
            printf("Consumer %d, count = %d\n", id, buffer);
            consumed_count++;
        }
        else
        {
            i--;
        }
        pthread_spin_unlock(&spinlock);
    }
    return NULL;
}

int main()
{
    pthread_t producer_threads[PRODUCER_THREADS_SIZE];
    pthread_t consumer_threads[CONSUMER_THREADS_SIZE];
    int producer_threads_ids[PRODUCER_THREADS_SIZE];
    int consumer_threads_ids[CONSUMER_THREADS_SIZE];

    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);

    for (int i = 0; i < PRODUCER_THREADS_SIZE; i++)
    {
        producer_threads_ids[i] = i + 1;
        pthread_create(&producer_threads[i], NULL, producer_task, &producer_threads_ids[i]);
    }

    for (int i = 0; i < CONSUMER_THREADS_SIZE; i++)
    {
        consumer_threads_ids[i] = i + 1;
        pthread_create(&consumer_threads[i], NULL, consumer_task, &consumer_threads_ids[i]);
    }
    
    for (int i = 0; i < PRODUCER_THREADS_SIZE; i++)
    {
        pthread_join(producer_threads[i], NULL);
    }

    for (int i = 0; i < CONSUMER_THREADS_SIZE; i++)
    {
        pthread_join(consumer_threads[i], NULL);
    }
    
    pthread_spin_destroy(&spinlock);

    printf("Total items produced: %d\n", produced_count);
    printf("Total items consumed: %d\n", consumed_count);
    return 0;
}
