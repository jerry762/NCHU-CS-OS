#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    if (fork() == 0)
    {
        printf("I am child process 1.\n");
        printf("Pid: %d\tParent Pid: %d\n", getpid(), getppid());
        return 0;
    }

    if (fork() == 0)
    {
        printf("I am child process 2.\n");
        printf("Pid: %d\tParent Pid: %d\n", getpid(), getppid());
        return 0;
    }
    
    wait(NULL);
    wait(NULL);

    printf("I'm parent process.\n");
    printf("PID: %d\tParent PID: %d\n", getpid(), getppid());

    return 0;
}