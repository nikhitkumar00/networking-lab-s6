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
    char buffer[BUFFER_SIZE] = {0};
    char message[BUFFER_SIZE];

    // Create client socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
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

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        perror("Connection failed");
        return -1;
    }

    while (1)
    {
        printf("Enter a frame to send to the server (or 'q' to quit): ");
        fgets(message, BUFFER_SIZE, stdin);

        if (strcmp(message, "q\n") == 0)
            break;

        // Send frame to the server
        send(clientSocket, message, strlen(message), 0);

        // Receive acknowledgement from the server
        bytesRead = read(clientSocket, buffer, BUFFER_SIZE);
        printf("Received acknowledgement: %s\n", buffer);
    }

    // Close the socket
    close(clientSocket);

    return 0;
}
