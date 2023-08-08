#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFERSIZE 1024
#define PORT 8080

void main()
{
    int serversocket;
    struct sockaddr_in serveraddress, clientaddress;
    int clientaddresslength = sizeof(clientaddress);
    char buffer[BUFFERSIZE];

    serversocket = socket(AF_INET, SOCK_DGRAM, 0);

    serveraddress.sin_addr.s_addr = INADDR_ANY;
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(PORT);

    bind(serversocket, (struct sockaddr *)&serveraddress, sizeof(serveraddress));

    recvfrom(serversocket, buffer, BUFFERSIZE, 0, (struct sockaddr *)&clientaddress, (socklen_t *)&clientaddresslength);

    int j = strlen(buffer) - 1;
    for (int i = 0; i < j; i++,j--)
    {
        int temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }

    sendto(serversocket, buffer, BUFFERSIZE, 0, (struct sockaddr *)&clientaddress, sizeof(clientaddress));

    close(serversocket);
}