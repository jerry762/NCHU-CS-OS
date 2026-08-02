#include <unistd.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2


int main() {

    char buffer_out[] = "STDOUT Hello World\n";
    char buffer_err[] = "STDERR Hello World\n";

    write(STDOUT, buffer_out, sizeof(buffer_out));

    write(STDERR, buffer_err, sizeof(buffer_err));

    return 0;

}