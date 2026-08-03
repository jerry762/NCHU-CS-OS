#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREAD_COUNT 4

int count = 0;

void IterIncreCount(void *arg){
    int iterCount = *(int *)arg;

    printf("Thread ID: %lu, IterCount: %d\n", pthread_self(), iterCount);

    for (size_t i = 0; i < iterCount; i++)
    {
        count++;
    }

    pthread_exit(NULL);
}

int main(){

    pthread_t threads[THREAD_COUNT];
    int rc;
    int iterCount = 25000000;
    
    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        rc = pthread_create(&threads[i], NULL, (void *)IterIncreCount, &iterCount);

        if (rc)
        {
            printf("CREATE ERROR\n");
            exit(-1);
        }
    }
    
    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        rc = pthread_join(threads[i], NULL);
        if (rc)
        {
            printf("JOIN ERROR\n");
            exit(-1);
        }
    }

    printf("Final Count: %d\n", count);

    return 0;
}