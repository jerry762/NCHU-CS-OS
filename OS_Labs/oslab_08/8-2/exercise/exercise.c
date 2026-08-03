#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static __thread int glob = 0;

static void incr(int *loops)
{
    int loc, j;

    for (int j = 0; j < *loops; j++)
    {
        loc = glob;
        loc++;
        glob = loc;
    }

    printf("thread_ID: %lu, glob: %d\n", pthread_self(), glob);

    pthread_exit(NULL);
}

void *function(void *arg){
    glob++;
    printf("thread_ID: %lu, glob: %d\n", pthread_self(), glob);
    pthread_exit(NULL);
}

int main(){

    pthread_t id[2];
    int arg1 = 50;
    int arg2 = 100;

    printf("(main thread) glob value before run 2 threads: %d\n", glob);

    pthread_create(&id[0], NULL, (void *)incr, &arg1);
    pthread_create(&id[1], NULL, (void *)incr, &arg2);

    pthread_join(id[0], NULL);
    pthread_join(id[1], NULL);

    printf("(main thread) glob value after run 2 threads: %d\n", glob);

    return 0;
}