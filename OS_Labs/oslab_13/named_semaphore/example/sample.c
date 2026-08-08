#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

sem_t *mtx;

int main()
{
    mtx = sem_open("/mysem", O_CREAT, S_IRUSR | S_IWUSR, 1);
    sem_wait(mtx);
    printf("Waiting.. \n");

    sleep(1);
    printf("Sleeping.. \n");

    sem_close(mtx);
    printf("Finished task. \n");
    sem_unlink("/mysem");
    return 0;
}
