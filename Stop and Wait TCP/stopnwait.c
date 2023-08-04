#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

void main()
{
    int frame_number = 0;

    while (1)
    {
        printf("\nSending Frame : %d", frame_number);

        srand(time(NULL));
        sleep(3);

        if (rand() % 2 == 0)
        {
            printf("\nAcknowledgement Recieved Successfully\n\n");
        }
        else
        {
            printf("\nAcknowledgement not Recieved\nResending Frame : %d\n\n", frame_number);
            continue;
        }

        frame_number++;
    }
}