#include <stdio.h>

void main()
{
    int n, temp;

    struct router
    {
        int distance[20];
        int adjacent[20];
    } node[20];

    printf("\nEnter the Number of nodes :\n");
    scanf("%d", &n);

    printf("\nEnter 999 if nodes doesn't have path between them\nSelf distance will be overwritten as 0");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("\nEnter the distance between node[%d] and node[%d]\n", i + 1, j + 1);
            scanf("%d", &node[i].distance[j]);
            node[i].adjacent[j] = j;

            if (i == j)
            {
                node[i].distance[j] = 0;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (node[i].distance[j] > node[i].distance[k] + node[k].distance[j])
                {
                    node[i].distance[j] = node[i].distance[k] + node[k].distance[j];
                    node[i].adjacent[j] = k;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("\n\nRouter[%d] Table", i + 1);
        for (int j = 0; j < n; j++)
        {
            printf("\n\tDistance to router[%d] through router[%d] is [ %d ]", j + 1, node[i].adjacent[j] + 1, node[i].distance[j]);
        }
    }
}