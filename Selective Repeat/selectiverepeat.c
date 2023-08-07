#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define WINDOWSIZE 4

void main()
{
    int base = 0;
    bool ackrecieved[999];

    for (int i = 0; i < 999; i++)
    {
        ackrecieved[i] = false;
    }

    while (1)
    {
        for (int i = base; i < base + WINDOWSIZE; i++)
        {
            if (ackrecieved[i] == false)
            {
                printf("\n\t\t\t\t\t\t[%d][%d][%d][%d]", base, base + 1, base + 2, base + 3);
                printf("\nFrame[%d] sent", i);
                sleep(3);

                srand(time(NULL));
                if (rand() % 2 == 0)
                {
                    printf("\n\t\t\tAcknowledge[%d] recieved", i);
                    ackrecieved[i] = true;
                }
                else
                {
                    printf("\n\t\t\tNegative Acknowledge[%d] sent", i);
                }
            }
            if (ackrecieved[base] == true)
            {
                base++;
            }
        }
    }
}