#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int serverSocket, clientSocket, bytesRead;
    struct sockaddr_in serverAddress, clientAddress;
    int clientAddressLength = sizeof(clientAddress);
    char buffer[BUFFER_SIZE] = {0};

    // Create server socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
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

    // Listen for incoming connections
    if (listen(serverSocket, 3) < 0)
    {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    // Accept a new connection
    if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, (socklen_t *)&clientAddressLength)) < 0)
    {
        perror("Failed to accept connection");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        // Receive frame from client
        bytesRead = read(clientSocket, buffer, BUFFER_SIZE);
        if (bytesRead == 0)
            break;

        printf("Received frame: %s\n", buffer);

        // Simulate processing time
        sleep(1);

        // Send acknowledgement back to the client
        send(clientSocket, "ACK", 3, 0);
    }

    // Close the sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}
