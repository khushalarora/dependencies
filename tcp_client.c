#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

#define PORT 3500
#define SIZE 1024


int main(){
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[SIZE] = {0};
    char message[] = "Chin Tapak DumDum !";

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket == 0){
        perror("Socket error");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_address.sin_zero), '\0', 8);

    if(connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0){
        perror("connect error");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Enter you message : ");
    fgets(buffer, SIZE, stdin);

    int bytesSent = send(client_socket, buffer, strlen(buffer), 0);
    if (bytesSent < 0) {
        perror("Send error");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    char recMessage[SIZE] = {0};

    int bytesRead = read(client_socket, recMessage, SIZE);
    if(bytesRead < 0){
        perror("Rec error");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    printf("Secret Code is %s\n", recMessage);

    close(client_socket);

    return 0;
}