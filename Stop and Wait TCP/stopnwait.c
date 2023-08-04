#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

void sendFrame(int frameNumber) {
    printf("Sending frame: %d\n", frameNumber);
}

bool receiveAck() {
    srand(rand());
    return rand() % 2 == 0;
}

int main() {
    int frameNumber = 0;
    
    while (true) {
        sendFrame(frameNumber);
        sleep(2);
        bool ackReceived = receiveAck();
        
        if (ackReceived) {
            printf("Acknowledgment received for frame: %d\n", frameNumber);
            frameNumber++;
        } else {
            printf("No acknowledgment received for frame: %d\n", frameNumber);
        }
    }
    
    return 0;
}