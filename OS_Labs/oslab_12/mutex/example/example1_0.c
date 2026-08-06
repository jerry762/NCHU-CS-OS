// not using mutex to solve race condition.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static int glob = 0;

static void *threadFunc(void *arg);

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    int loops, s;
    
    if (argc == 2)
    {
        loops = atoi(argv[1]);
    }
    else
    {
        printf("ps input loops time in this program argument.\n");
        return 0;
    }    

    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0)
    {
        printf("pthread_create ERROR\n");
    }
    
    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0)
    {
        printf("pthread_create ERROR\n");
    }
    
    s = pthread_join(t1, NULL);
    if (s != 0)
    {
        printf("pthread_join ERROR\n");
    }
    
    s = pthread_join(t2, NULL);
    if (s != 0)
    {
        printf("pthread_join ERROR\n");
    }

    printf("glob = %d\n", glob);

    return 0;
}

static void *threadFunc(void *arg)
{
    int loops = *((int *)arg);
    int loc, j, s;

    for (j = 0; j < loops; j++)
    {
        loc = glob;
        loc++;
        glob = loc;
    }
    return NULL;
}