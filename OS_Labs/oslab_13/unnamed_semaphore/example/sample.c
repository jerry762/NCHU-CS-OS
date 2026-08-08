#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mtx;

void *thread(void *arg)
{
    // wait
    sem_wait(&mtx);
    printf("pid:%lu, Entered...\n", pthread_self());

    // critical section
    sleep(4);

    //signal
    printf("pid:%lu, Exiting...\n", pthread_self());
    sem_post(&mtx);
}

int main()
{
    sem_init(&mtx, 0, 1);
    pthread_t t1, t2;

    
    pthread_create(&t1, NULL, thread, NULL);
    sleep(2); // t1 first enter the critical section.

    pthread_create(&t2, NULL, thread, NULL);


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&mtx);
    return 0;
}