#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void main()
{
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    int clientAddressLength = sizeof(clientAddress);
    char buffer[BUFFER_SIZE] = {0};

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    listen(serverSocket, 3);

    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, (socklen_t *)&clientAddressLength);

    recv(clientSocket, buffer, BUFFER_SIZE, 0);
    printf("Message received: %s\n", buffer);

    strcpy(buffer, "NIKHIT KUMAR");
    send(clientSocket, buffer, BUFFER_SIZE, 0);

    close(clientSocket);
    close(serverSocket);
}