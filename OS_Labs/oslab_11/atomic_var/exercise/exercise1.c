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
        atomic_fetch_add(&atomic_counter, 2);
    }
    
    return NULL;
}

void *decrement_counter(void *arg)
{
    int n = *((int *)arg);

    for (int i = 0; i < n; i++)
    {
        atomic_fetch_sub(&atomic_counter, 1);
    }
    
    return NULL;
}

int main()
{
    pthread_t thread_add, thread_sub;
    int arg_add = 1000, arg_sub = 1000;

    pthread_create(&thread_add, NULL, increment_counter, &arg_add);
    pthread_create(&thread_sub, NULL, decrement_counter, &arg_sub);

    pthread_join(thread_add, NULL);
    pthread_join(thread_sub, NULL);
    
    printf("Fianl counter value: %d\n", atomic_load(&atomic_counter));

    return 0;
}