#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFERSIZE 1024
#define PORT 8080

void main()
{
    int clientsocket;
    struct sockaddr_in serveraddress;
    int serveraddresslength = sizeof(serveraddress);
    char buffer[BUFFERSIZE];

    clientsocket = socket(AF_INET, SOCK_DGRAM, 0);

    serveraddress.sin_addr.s_addr = INADDR_ANY;
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(PORT);

    printf("\nEnter the string to be reversed : ");
    fgets(buffer, BUFFERSIZE, stdin);

    sendto(clientsocket, buffer, BUFFERSIZE, 0, (struct sockaddr *)&serveraddress, sizeof(serveraddress));

    recvfrom(clientsocket, buffer, BUFFERSIZE, 0, (struct sockaddr *)&serveraddress, (socklen_t *)&serveraddresslength);

    printf("\n%s", buffer);

    close(clientsocket);
}