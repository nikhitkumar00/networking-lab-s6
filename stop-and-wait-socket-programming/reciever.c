#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PACKET_SIZE 1024

typedef struct {
    int seq_num;
    char data[PACKET_SIZE];
} packet;

int main() {
    int sockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t addr_len = sizeof(cli_addr);
    packet pkt;
    int expected_seq_num = 0;

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
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to address
    if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Receive packets
    while (1) {
        if (recvfrom(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr*) &cli_addr, &addr_len) < 0) {
            perror("recvfrom failed");
            exit(EXIT_FAILURE);
        }

        if (pkt.seq_num == expected_seq_num) {
            printf("Received packet %d\n", pkt.seq_num);
            expected_seq_num++;

            // Create ACK packet
            packet ack;
            ack.seq_num = pkt.seq_num;

            // Send ACK packet
            if (sendto(sockfd, &ack, sizeof(ack), 0, (struct sockaddr*) &cli_addr, addr_len) < 0) {
                perror("sendto failed");
                exit(EXIT_FAILURE);
            }

            printf("Sent ACK for packet %d\n", pkt.seq_num);
        }
        else {
            printf("Discarding packet %d\n", pkt.seq_num);
        }
    }

    // Close socket
    close(sockfd);

    return 0;
}

