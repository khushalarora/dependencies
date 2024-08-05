#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 3500

int main(){
    int socket_fd;
    struct sockaddr_in server_address;
    char message[] = "Chin Tapak Dum Dum !";

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(socket_fd == 0){
        perror("Socket error");
        exit(1);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_address.sin_zero), '\0', 8);

    int bytesSent = sendto(socket_fd, message, strlen(message), 0, (struct sockaddr*)&server_address, sizeof(server_address));

    if(bytesSent < 0){
        perror("Send error");
        exit(EXIT_FAILURE);
    }

    return 0;
}