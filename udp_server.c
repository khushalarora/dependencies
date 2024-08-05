#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 3500
#define SIZE 1024

int main(){
    int socket_fd;
    struct sockaddr_in server_address, client_address;
    socklen_t addrlen = sizeof(client_address);

    char buffer[SIZE] = {0};

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(socket_fd == 0){
        perror("Socket error");
        exit(1);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_address.sin_zero), '\0', 8);

    if(bind(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0){
        close(socket_fd);
        perror("Bind error");
        exit(1);
    }

    int bytesRead = recvfrom(socket_fd, buffer, SIZE, 0, (struct sockaddr*)&client_address, &addrlen);
    if(bytesRead < 0){
        close(socket_fd);
        perror("Read Error");
        exit(1);
    }
    else{
        printf("%d\n", bytesRead);
        printf("Message is %s\n", buffer);
    }
    return 0;
}
