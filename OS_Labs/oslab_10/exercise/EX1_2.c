#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {

    pid_t new_pid;
    new_pid = fork();

    if (new_pid < 0)
    {
        printf("fork error\n");
        return 0;
    }
    else if (new_pid > 0)
    {
        printf("I am parent, pid = %d and ppid = %d\n", getpid(), getppid());

        wait(NULL);

    }
    else 
    {
        printf("I am child, pid = %d and ppid = %d\n", getpid(), getppid());

        kill(getppid(), SIGKILL);
    }

    return 0;
}