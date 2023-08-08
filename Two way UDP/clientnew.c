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
    int serverAddressLength = sizeof(serverAddress);
    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE];

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    printf("Enter a string to send to the server: ");
    fgets(message, BUFFER_SIZE, stdin);

    sendto(clientSocket, message, strlen(message), 0, (struct sockaddr *)&serverAddress, serverAddressLength);

    recvfrom(clientSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serverAddress, (socklen_t *)&serverAddressLength);
    printf("Reversed string received from server: %s\n", buffer);

    close(clientSocket);
}