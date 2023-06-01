#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int clientSocket, bytesRead;
    struct sockaddr_in serverAddress;
    char buffer[BUFFER_SIZE];
    FILE *file;

    // Create client socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Socket creation failed");
        return -1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
        perror("Invalid address");
        return -1;
    }

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Connection failed");
        return -1;
    }

    // Open a file for writing
    file = fopen("received_file.txt", "wb");
    if (file == NULL) {
        perror("Failed to create file");
        return -1;
    }

    // Receive file data from the server and write them to the file
    while ((bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytesRead, file);
    }

    // Close the file
    fclose(file);

    // Close the socket
    close(clientSocket);

    return 0;
}
