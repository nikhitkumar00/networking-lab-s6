#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PACKET_SIZE 1024
#define WINDOW_SIZE 1

typedef struct {
    int seq_num;
    char data[PACKET_SIZE];
} packet;

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    socklen_t addr_len = sizeof(serv_addr);
    packet pkt;
    int seq_num = 0;
    int total_packets = 10;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Send packets
    while (seq_num < total_packets) {
        // Create packet
        pkt.seq_num = seq_num;
        sprintf(pkt.data, "Packet %d", seq_num);

        // Send packet
        if (sendto(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr*) &serv_addr, addr_len) < 0) {
            perror("sendto failed");
            exit(EXIT_FAILURE);
        }

        printf("Sent packet %d\n", seq_num);

        // Wait for ACK
        packet ack;
        if (recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr*) &serv_addr, &addr_len) < 0) {
            perror("recvfrom failed");
            exit(EXIT_FAILURE);
        }

        if (ack.seq_num == seq_num) {
            printf("Received ACK for packet %d\n", seq_num);
            seq_num++;
        }
    }

    // Close socket
    close(sockfd);

    return 0;
}

