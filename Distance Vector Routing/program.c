#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 10
#define INFINITY 9999

struct DistanceVector {
    int cost[MAX_NODES];
};

void initialize(struct DistanceVector dv[], int n, int source) {
    int i, j;

    for (i = 0; i < n; i++) {
        dv[i].cost[i] = 0;

        for (j = 0; j < n; j++) {
            if (i != j) {
                printf("Enter the cost of edge from node %d to node %d: ", i, j);
                scanf("%d", &dv[i].cost[j]);
            }
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j && dv[i].cost[j] == 0) {
                dv[i].cost[j] = INFINITY;
            }
        }
    }

    printf("\n");

    dv[source].cost[source] = 0;
}

void update(struct DistanceVector dv[], int n) {
    bool updated = false;

    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                if (dv[i].cost[k] + dv[k].cost[j] < dv[i].cost[j]) {
                    dv[i].cost[j] = dv[i].cost[k] + dv[k].cost[j];
                    updated = true;
                }
            }
        }
    }

    if (updated)
        update(dv, n);
}

void printRoutingTable(struct DistanceVector dv[], int n) {
    printf("Routing Table:\n");
    printf("Node\tCost\n");

    int i, j;
    for (i = 0; i < n; i++) {
        printf("%d\t", i);

        for (j = 0; j < n; j++) {
            printf("%d\t", dv[i].cost[j]);
        }

        printf("\n");
    }
}

int main() {
    int n, source;
    struct DistanceVector dv[MAX_NODES];

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the source node (0-%d): ", n - 1);
    scanf("%d", &source);

    initialize(dv, n, source);
    update(dv, n);
    printRoutingTable(dv, n);

    return 0;
}
