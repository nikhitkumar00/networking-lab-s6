#include <stdio.h>

int main() {
    int routerCount, sourceRouter, i, j, k, w, v, min;

    printf("Enter the number of routers: ");
    scanf("%d", &routerCount);

    int costMatrix[100][100], distance[100], previousRouter[100], visited[100];

    printf("Enter the cost matrix values:\n");
    for (i = 0; i < routerCount; i++) {
        for (j = 0; j < routerCount; j++) {
            printf("%d -> %d: ", i, j);
            scanf("%d", &costMatrix[i][j]);

            // Treat negative values as infinity
            if (costMatrix[i][j] < 0) {
                costMatrix[i][j] = 1000;
            }
        }
    }

    printf("Enter the source router: ");
    scanf("%d", &sourceRouter);

    // Initialize arrays
    for (v = 0; v < routerCount; v++) {
        visited[v] = 0;
        previousRouter[v] = sourceRouter;
        distance[v] = costMatrix[sourceRouter][v];
    }
    visited[sourceRouter] = 1;

    // Dijkstra's algorithm
    for (i = 0; i < routerCount; i++) {
        min = 1000;
        for (w = 0; w < routerCount; w++) {
            if (!visited[w] && distance[w] < min) {
                v = w;
                min = distance[w];
            }
        }
        visited[v] = 1;
        for (w = 0; w < routerCount; w++) {
            if (!visited[w] && min + costMatrix[v][w] < distance[w]) {
                distance[w] = min + costMatrix[v][w];
                previousRouter[w] = v;
            }
        }
    }

    // Print results
    for (i = 0; i < routerCount; i++) {
        printf("\n%d => %d: Path taken: %d", sourceRouter, i, i);
        w = i;
        while (w != sourceRouter) {
            printf(" <- %d", previousRouter[w]);
            w = previousRouter[w];
        }
        printf("\nShortest path cost: %d\n", distance[i]);
    }

    return 0;
}