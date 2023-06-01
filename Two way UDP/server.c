#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int serverSocket, bytesRead;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    char buffer[BUFFER_SIZE] = {0};

    // Create server socket
    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) == 0)
    {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // Bind server socket to the specified port
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Receive message from client
    bytesRead = recvfrom(serverSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&clientAddress, &clientAddressLength);
    printf("Received message from client: %s\n", buffer);

    // Reverse the string
    int length = strlen(buffer);
    for (int i = 0; i < length / 2; i++)
    {
        char temp = buffer[i];
        buffer[i] = buffer[length - i - 1];
        buffer[length - i - 1] = temp;
    }

    // Send reversed string back to client
    sendto(serverSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&clientAddress, clientAddressLength);
    printf("Reversed string sent to client.\n");

    // Close the socket
    close(serverSocket);

    return 0;
}
