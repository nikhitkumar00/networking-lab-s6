#include <stdio.h>

void main()
{
    int numberofrouters, sourcerouter, minvalue, minindex;
    int cost[10][10], previous[10], distance[10], visited[10];

    printf("\nEnter the number of Routers : ");
    scanf("%d", &numberofrouters);

    printf("\nEnter the Source Router : ");
    scanf("%d", &sourcerouter);

    for (int i = 0; i < numberofrouters; i++)
    {
        for (int j = 0; j < numberofrouters; j++)
        {
            printf("Enter the cost between [%d] and [%d] : ", i, j);
            scanf("%d", &cost[i][j]);
        }
        distance[i] = 9999;
        visited[i] = 0;
    }

    distance[sourcerouter] = 0;

    for (int i = 0; i < numberofrouters; i++)
    {
        minvalue = 9999;
        for (int j = 0; j < numberofrouters; j++)
        {
            if (visited[j] == 0 && distance[j] < minvalue)
            {
                minvalue = distance[j];
                minindex = j;
            }
        }

        visited[minindex] = 1;

        for (int j = 0; j < numberofrouters; j++)
        {
            if (visited[j] == 0 && minvalue + cost[minindex][j] < distance[j])
            {
                distance[j] = minvalue + cost[minindex][j];
                previous[j] = minindex;
            }
        }
    }

    for (int i = 0; i < numberofrouters; i++)
    {
        printf("\n\nMinimum Cost : %d", distance[i]);
        printf("\t\tPath to router [%d] : [%d]", i, i);
        int temp = i;
        while (temp != sourcerouter)
        {
            printf(" <== [%d]", previous[temp]);
            temp = previous[temp];
        }
    }
}