#include <stdio.h>

int main() {
    int n, tq;
    int at[100], bt[100], rt[100];
    int wt[100], tat[100];
    int queue[100], front = 0, rear = 0;
    int time = 0, completed = 0;
    int inQueue[100] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time of P%d: ", i);
        scanf("%d", &at[i]);
    }

    for (int i = 0; i < n; i++) {
        printf("Enter burst time of P%d: ", i);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    queue[rear++] = 0;
    inQueue[0] = 1;

    while (completed < n) {
        if (front == rear) {
            int nextArrival = 999999;
            for (int i = 0; i < n; i++)
                if (rt[i] > 0 && at[i] < nextArrival)
                    nextArrival = at[i];
            time = nextArrival;
        }

        int p = queue[front++];
        
        if (at[p] > time) {
            time = at[p];
        }

        // Run process
        if (rt[p] > tq) {
            time += tq;
            rt[p] -= tq;
        } else {
            time += rt[p];
            tat[p] = time - at[p];
            wt[p] = tat[p] - bt[p];
            rt[p] = 0;
            completed++;
        }

        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && rt[i] > 0 && at[i] <= time) {
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }

        if (rt[p] > 0) {
            queue[rear++] = p;
        }
    }

    printf("\nP\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i, at[i], bt[i], wt[i], tat[i]);
    }

    return 0;
}
