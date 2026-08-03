#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int global_variable = 10;

int main() {

    int local_variable = 10;
    pid_t new_pid;

    printf("Initial value:\n");
    printf("PID: %d\tPPID: %d\tGlobal variable: %d\tLocal variable: %d\n", getpid(), getppid(), global_variable, local_variable);

    printf("-------------------------------------------------------------------------\n");

    new_pid = fork();

    switch (new_pid)
    {
    case -1:
        printf("fork error\n");
        break;
    case 0:
        printf("Child process:\n");
        printf("PID: %d\tPPID: %d\tGlobal variable: %d\tLocal variable: %d\n", getpid(), getppid(), global_variable, local_variable);
        
        global_variable++;
        local_variable++;

        printf("Child process after increment:\n");
        printf("PID: %d\tPPID: %d\tGlobal variable: %d\tLocal variable: %d\n", getpid(), getppid(), global_variable, local_variable);

        return 0;
    default:
        wait(NULL);

        printf("Parent process:\n");
        printf("PID: %d\tPPID: %d\tGlobal variable: %d\tLocal variable: %d\n", getpid(), getppid(), global_variable, local_variable);

        printf("Parent process after increment:\n");
        printf("PID: %d\tPPID: %d\tGlobal variable: %d\tLocal variable: %d\n", getpid(), getppid(), global_variable, local_variable);

        break;
    }

    printf("-------------------------------------------------------------------------\n");
    return 0;
}