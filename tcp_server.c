#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

#define PORT 3500
#define SIZE 1024

int main(){
    int server_fd, new_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t addrlen;
    char buffer[SIZE] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == 0){
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    server_address.sin_port = htons(PORT);    
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_address.sin_zero), '\0', 8);

    if(bind(server_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0){
        perror("Bind error");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd, 3) < 0){
        perror("Listen error");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    addrlen = sizeof(client_address);

    new_socket = accept(server_fd, (struct sockaddr*)&client_address, &addrlen);
    if(new_socket < 0){
        perror("Accept error");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    int bytesRead = read(new_socket, buffer, SIZE);
    // buffer[8] = '\0';
    printf("%d\n", bytesRead);
    printf("Your message is : %s\n", buffer);

    char message[] = "Tehelka Ommelette";
    int bytesSent = send(new_socket, message, strlen(message), 0);
    
    close(new_socket);
    close(server_fd);
    return 0;
}