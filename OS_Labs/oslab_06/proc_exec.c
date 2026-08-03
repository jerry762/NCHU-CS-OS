#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t new_pid;
    new_pid = fork();

    switch (new_pid)
    {
    case -1:
        printf("fork error\n");
        break;
    case 0:
        execlp("/bin/ls", "ls", "-l", NULL);
        break;
    default:
        wait(NULL);
        printf("This is parent process\n");
        printf("Pid: %d\nChild pid: %d\n", getpid(), new_pid);
        break;
    }

    return 0;
}