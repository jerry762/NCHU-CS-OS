#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 3000
#define MAX_SIZE 1000

int main(){

    int socket_fd;
    struct sockaddr_in server_addr;
    ssize_t bytes_send;
    char buffer[MAX_SIZE];


    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd == -1)
    {
        perror("Failed to create the socket\n");
        return 1;
    }
    
    memset(&buffer, '\0', sizeof(buffer));
    memset(&server_addr, 0, sizeof(server_addr));


    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr)) <= 0)
    {
        perror("Failed to convert the address\n");
        return 1;
    }

    while (1)
    {
        printf("> ");
        fgets(buffer, MAX_SIZE, stdin);

        bytes_send = sendto(socket_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        if (bytes_send == -1)
        {
            perror("Failed to send the socket\n");
            return 1;
        }

        if (strncmp(buffer, "exit", 4) == 0)
        {
            break;
        }

        printf("Message sent, total %ld bytes.\n\n", bytes_send);
    }
    
    close(socket_fd);
    return 0;
}