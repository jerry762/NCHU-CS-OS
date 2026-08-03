#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    if (fork() == 0)
    {
        printf("Child process E: PID: %d\tPPID: %d\n", getpid(), getppid());
        return 0;
    }
    wait(NULL); // A wait for E


    if (fork() == 0)
    {
        if (fork() == 0)
        {
            printf("Child process C: PID: %d\tPPID: %d\n", getpid(), getppid());
            return 0;
        }
        wait(NULL); // B wait for C


        printf("Child process B: PID: %d\tPPID: %d\n", getpid(), getppid());
        return 0;
    }
    wait(NULL); // A wait for B


    if (fork() == 0)
    {
        printf("Child process D: PID: %d\tPPID: %d\n", getpid(), getppid());

        return 0;
    }
    wait(NULL); // A wait for D


    printf("Parent process A: PID: %d\tPPID: %d\n", getpid(), getppid());

    return 0;
}