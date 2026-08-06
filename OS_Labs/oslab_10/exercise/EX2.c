#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

struct sigaction act;

int phase = 1;

void how_are_you(int sig_num)
{   
   printf("Handler 1: HOW ARE YOU?\n");
}

void i_am_fine(int sig_num)
{   
   printf("Handler 2: I AM FINE!\n");
}

void alarm_handler(int sig_num)
{
    if (phase == 1)
    {
        act.sa_handler = i_am_fine;
        sigaction(SIGINT, &act, NULL);

        phase++;
        alarm(3);
    }
    else if (phase == 2)
    {
        act.sa_handler = SIG_DFL;
        sigaction(SIGINT, &act, NULL);

        printf("Terminating the process after switching to handler2 for 3 seconds.\n");

        phase++;
    }

    signal(SIGALRM, alarm_handler);
}

int main() {

    signal(SIGALRM, alarm_handler);
    alarm(3);
    
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = how_are_you;
    
    sigaction(SIGINT, &act, NULL);
    
    while (1)
    {
        pause();
    }

    return 0;
}

