#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define WINDOW_SIZE 4

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

    int sequenceNumber = 0;
    int expectedAcknowledgement = 0;

    while (1)
    {
        printf("Enter a frame to send to the server (or 'q' to quit): ");
        fgets(message, BUFFER_SIZE, stdin);

        if (strcmp(message, "q\n") == 0)
            break;

        // Construct the frame with sequence number
        snprintf(buffer, BUFFER_SIZE, "%d%s", sequenceNumber, message);

        // Send frame to the server
        send(clientSocket, buffer, strlen(buffer), 0);

        // Receive acknowledgement from the server
        int receivedAcknowledgement;
        bytesRead = read(clientSocket, &receivedAcknowledgement, sizeof(int));

        if (bytesRead == sizeof(int) && receivedAcknowledgement == expectedAcknowledgement)
        {
            printf("Received acknowledgement for frame %d\n", receivedAcknowledgement);
            expectedAcknowledgement = (expectedAcknowledgement + 1) % WINDOW_SIZE;
            sequenceNumber = (sequenceNumber + 1) % WINDOW_SIZE;
        }
        else
        {
            printf("Timeout or negative acknowledgement (NAK) received. Resending frame %d\n", sequenceNumber);
        }
    }

    // Close the socket
    close(clientSocket);

    return 0;
}
