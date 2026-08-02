#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE *fp;
    char buffer[] = "Hello World\n";

    
    fp = fopen("hello.txt", "w+");

    if(fp == NULL)
    {
        perror("fopen");
        exit(1);
    }

    fwrite(buffer, sizeof(buffer), 1, fp);

    fclose(fp);

    return 0;
}