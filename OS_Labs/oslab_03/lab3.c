#include <unistd.h>

#define STDOUT 1

void my_print(int num);

int main() {


    my_print(0);
    my_print(100);
    my_print(2147483647);
    my_print(-2147483648);

    return 0;
}

void my_print(int n){

    char buf[12];
    int i = 0;
    int neg = 0;

    if (n == 0)
    {
        write(STDOUT, "0\n", 2);
        return;
    }

    if (n == -2147483648)
    {
        write(STDOUT, "-2147483648\n", 12);
        return;
    }

    if (n < 0)
    {
        neg = 1;
        n = -n;
    }

    while (n > 0)
    {
        buf[i++] = (n % 10) + '0';
        n /= 10;
    }

    if (neg)
        buf[i++] = '-';

    while (i--)
        write(STDOUT, &buf[i], 1);

    write(STDOUT, "\n", 1);

}