#include <stdio.h>

int main() {
    int p, r;
    scanf("%d", &p);
    scanf("%d", &r);

    int max[20][20], alloc[20][20], need[20][20], avail[20];
    int finish[20] = {0}, safeSeq[20], work[20];

    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &max[i][j]);

    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

    for (int i = 0; i < r; i++)
        scanf("%d", &avail[i]);

    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    for (int i = 0; i < r; i++)
        work[i] = avail[i];

    int count = 0;

    while (count < p) {
        int found = 0;
        for (int i = 0; i < p; i++) {
            if (!finish[i]) {
                int ok = 1;
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > work[j]) {
                        ok = 0;
                        break;
                    }
                }

                if (ok) {
                    for (int j = 0; j < r; j++)
                        work[j] += alloc[i][j];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) break;
    }

    int safe = 1;
    for (int i = 0; i < p; i++)
        if (!finish[i])
            safe = 0;

    if (safe) printf("1");
    else printf("0");

    return 0;
}
