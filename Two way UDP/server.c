#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int serverSocket;
    struct sockaddr_in serverAddress, clientAddress;
    int clientAddressLength = sizeof(clientAddress);
    char buffer[BUFFER_SIZE];

    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    recvfrom(serverSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&clientAddress, (socklen_t *)&clientAddressLength);
    printf("Received message from client: %s\n", buffer);

    int j = strlen(buffer) - 1;
    for (int i = 0; i < j; i++, j--)
    {
        char temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }

    sendto(serverSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&clientAddress, clientAddressLength);
    printf("Reversed string sent to client.\n");

    close(serverSocket);

    return 0;
}