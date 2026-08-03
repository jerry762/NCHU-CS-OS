#include <stdio.h>
#include <unistd.h>

int main() {

    pid_t new_pid;
    new_pid = fork();

    if (new_pid < 0)
    {
        printf("fork error\n");
        return 0;
    }
    else if (new_pid == 0)
    {
        printf("This is child process\n");
        printf("Pid: %d\nParent pid: %d\n", getpid(), getppid());
        return 0;
    }
    else 
    {
        printf("This is parent process\n");
        printf("Pid: %d\nChild pid: %d\n", getpid(), new_pid);
        return 0;
    }
}