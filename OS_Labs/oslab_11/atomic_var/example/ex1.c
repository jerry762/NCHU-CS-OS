#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

atomic_int atomic_counter = ATOMIC_VAR_INIT(0);

void *increment_counter(void *arg)
{
    int n = *((int *)arg);

    for (int i = 0; i < n; i++)
    {
        atomic_fetch_add(&atomic_counter, 1);
    }
    
    return NULL;
}

int main()
{
    pthread_t threads[5];
    int increments[5];

    for (int i = 0; i < 5; i++)
    {
        increments[i] = 10000;
        pthread_create(&threads[i], NULL, increment_counter, &increments[i]);
    }
    
    for (int i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
    printf("Fianl counter value: %d\n", atomic_load(&atomic_counter));

    return 0;
}