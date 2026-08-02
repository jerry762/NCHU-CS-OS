#include <unistd.h>
#include <fcntl.h>

int main() {

    int fd;
    char buffer[] = "hello world\n";

    fd = open("hello.txt", O_CREAT | O_WRONLY, 0644);

    write(fd, buffer, sizeof(buffer));

    close(fd);

    return 0;
}