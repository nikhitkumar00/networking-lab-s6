#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int clientSocket, bytesRead;
    struct sockaddr_in serverAddress;
    socklen_t serverAddressLength = sizeof(serverAddress);
    char buffer[BUFFER_SIZE] = {0};
    char message[BUFFER_SIZE];

    // Create client socket
    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Failed to create socket");
        return -1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0)
    {
        perror("Invalid address");
        return -1;
    }

    printf("Enter a string to send to the server: ");
    fgets(message, BUFFER_SIZE, stdin);

    // Send message to the server
    sendto(clientSocket, message, strlen(message), 0, (struct sockaddr *)&serverAddress, serverAddressLength);

    // Receive reversed string from server
    bytesRead = recvfrom(clientSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serverAddress, &serverAddressLength);
    printf("Reversed string received from server: %s\n", buffer);

    // Close the socket
    close(clientSocket);

    return 0;
}
