#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define NUM_INCREMENTS 10000

int counter = 0;
pthread_spinlock_t spinlock;

void *increment_counter(void *arg)
{
    int n = *((int *)arg);

    for (int i = 0; i < n; i++)
    {
        pthread_spin_lock(&spinlock);
        counter++;
        pthread_spin_unlock(&spinlock);
    }
    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int increments[NUM_THREADS];

    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        increments[i] = NUM_INCREMENTS;
        pthread_create(&threads[i], NULL, increment_counter, &increments[i]);
    }
    
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
    pthread_spin_destroy(&spinlock);

    printf("Final counter value: %d\n", counter);
    return 0;
}