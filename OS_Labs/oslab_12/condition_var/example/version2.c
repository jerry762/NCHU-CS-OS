// using the condition variable to enhance the cpu efficient rate

// argc = threads, argv = produce per thread


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

static int avail = 0;

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void *producer(void *arg);

int main(int argc, char *argv[])
{
    pthread_t tid;
    int s, j;
    int totRequired; // total number of unit that all threads will produce.
    int numComsumed; // total units so far consumed.

    bool done;
    time_t t;
    t = time(NULL);


    // create all threads
    totRequired = 0;
    for (j = 1; j < argc; j++)
    {
        totRequired += atoi(argv[j]);
        s = pthread_create(&tid, NULL, producer, argv[j]);
        if (s != 0)
        {
            printf("pthread_create ERROR\n");
        }
    }

    // use a polling loop to check for availiable units
    numComsumed = 0;
    done = false;

    while (!done)
    {
        pthread_mutex_lock(&mtx);

        if (avail == 0)
        {
            pthread_cond_wait(&cond, &mtx); // unlock and relock
            printf("wait avail = 0\n");
        }

        // consume all available units
        while (avail > 0)
        {
            numComsumed++;
            avail--;
            printf("T = %ld: numConsumed = %d\n", (long)(time(NULL) - t), numComsumed);
            done = numComsumed >= totRequired;
        }
        pthread_mutex_unlock(&mtx);
    }
    
    pthread_mutex_destroy(&mtx);
    return 0;
}

static void *producer(void *arg)
{
    int cnt = atoi((char *)arg);
    int s, j;

    for (j = 0; j < cnt; j++)
    {
        sleep(1);

        // produce one product
        pthread_mutex_lock(&mtx);
        // Critical Section

        avail++;

        // Critical Section
        pthread_mutex_unlock(&mtx);

        pthread_cond_signal(&cond);
    }

    return NULL;
}
