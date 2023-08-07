#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void main()
{
    int clientSocket;
    struct sockaddr_in serverAddress;
    char buffer[BUFFER_SIZE] = {0};
    char newmessage[BUFFER_SIZE];

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    printf("ENTER A STRING :");
    fgets(newmessage, BUFFER_SIZE, stdin);

    send(clientSocket, newmessage, strlen(newmessage), 0);
    printf("Message sent to server.\n");

    recv(clientSocket, buffer, BUFFER_SIZE, 0);
    printf("%s", buffer);

    close(clientSocket);
}