#include <stdio.h>
#include <stdlib.h>

int main() {

    FILE *fp;
    char buffer[100];

    fp = fopen("hello.txt", "rb");

    if(fp == NULL)
    {
        perror("fopen");
        exit(1);
    }

    size_t n = fread(buffer, 1, sizeof(buffer), fp);

    printf("%s", buffer);

    fclose(fp);

    return 0;
}