#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include<time.h>

#define WINDOW_SIZE 4
#define TIMEOUT 3

void sendFrame(int frameNumber) {
    printf("Sending frame: %d\n", frameNumber);
}

bool receiveAck(int ackNumber) {
    srand(time(NULL));
    return rand() % 2 == 0;
}

int main() {
    int frameNumber = 0, base = 0, nextSeqNum = 0, expectedAck = 0;

    while (1) {
        while (nextSeqNum < base + WINDOW_SIZE) {
            sendFrame(nextSeqNum);
            nextSeqNum++;
        }

        sleep(TIMEOUT);

        for (int i = base; i < nextSeqNum; i++) {
            if (receiveAck(i)) {
                printf("\t\t\t\t\tFrame %d acknowledged\n", i);
                if (i == expectedAck) {
                    expectedAck++;
                    base++;
                }
            } else {
                printf("Frame %d not acknowledged\n", i);
                printf("Retransmitting frame: %d\n\n", i);
                sendFrame(i);
            }
            sleep(3);
        }
    }

    return 0;
}
