#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

int main() {

    int n = 0;

    scanf("%d", &n);

    if(n == 1) 
    {
        printf("%ld\n", syscall(462));
    }
    else if(n == 2)
    {
        scanf("%d", &n);
        printf("%ld\n", syscall(463, n));
    } 
    else
    {
        printf("Not defined\n");
    }

    return 0;
}