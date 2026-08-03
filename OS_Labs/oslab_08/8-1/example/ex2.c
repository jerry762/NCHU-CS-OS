#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int count = 87;

void HelloWorld(){
    printf("Thread ID is: %lu complete, count is %d\n", pthread_self(), count);
    pthread_exit(NULL);
}

int main(){

    pthread_t thread1;

    pthread_create(&thread1, NULL, HelloWorld, NULL);
    pthread_join(thread1, NULL);

    printf("Done!\n");

    return 0;
}