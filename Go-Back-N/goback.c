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
            printf("\n\t\t\t\t\t\t[%d][%d][%d][%d]", base, base + 1, base + 2, base + 3);
            printf("\nFrame[%d] sent", i);
            sleep(1);

            srand(time(NULL));
            if (rand() % 2 == 0 && base == i)
            {
                printf("\n\t\t\tAcknowledge[%d] recieved", i);
                ackrecieved[i] = true;
                base++;
            }
        }
    }
}