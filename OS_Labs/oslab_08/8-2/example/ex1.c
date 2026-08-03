#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static __thread int glob = 0;

void *function(void *arg){
    glob++;
    printf("thread_ID: %lu, glob: %d\n", pthread_self(), glob);
    pthread_exit(NULL);
}

int main(){

    pthread_t id[2];

    pthread_create(&id[0], NULL, function, NULL);
    pthread_create(&id[1], NULL, function, NULL);

    pthread_join(id[0], NULL);
    pthread_join(id[1], NULL);

    return 0;
}