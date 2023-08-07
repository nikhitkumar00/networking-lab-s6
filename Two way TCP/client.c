#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUFFERSIZE 1024
#define PORT 8080

void main()
{
    int clientsocket;
    struct sockaddr_in serveraddress;
    char buffer[BUFFERSIZE];

    clientsocket = socket(AF_INET, SOCK_STREAM, 0);

    serveraddress.sin_addr.s_addr = INADDR_ANY;
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(PORT);

    connect(clientsocket, (struct sockaddr *)&serveraddress, sizeof(serveraddress));

    printf("Enter the string to be reversed : ");
    fgets(buffer, BUFFERSIZE, stdin);

    send(clientsocket, buffer, BUFFERSIZE, 0);

    recv(clientsocket, buffer, BUFFERSIZE, 0);

    printf("\n%s", buffer);

    close(clientsocket);
}