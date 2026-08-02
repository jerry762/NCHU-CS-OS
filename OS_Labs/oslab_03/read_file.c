#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main() {
    int fd;
    char buffer[100];

    fd = open("hello.txt", O_RDONLY);

    read(fd, buffer, sizeof(buffer));

    printf("%s", buffer);

    close(fd);

    return 0;

}