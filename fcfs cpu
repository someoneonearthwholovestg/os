#include <stdio.h>

struct process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

int main() {
    int n;
    scanf("%d", &n);

    struct process p[n];
    for(int i = 0; i < n; i++) {
        p[i].pid = i;
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    int current_time = 0;
    int total_tat = 0, total_wt = 0, total_idle = 0;
    for(int i = 0; i < n; i++) {
        if(current_time < p[i].at) {
            total_idle += p[i].at - current_time;
            current_time = p[i].at;
        }
        p[i].ct = current_time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        current_time = p[i].ct;
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("Average TAT = %.2f\n", (float)total_tat / n);
    printf("Average WT  = %.2f\n", (float)total_wt / n);
    printf("CPU Utilization = %.2f%%\n", ((float)(current_time - total_idle) / current_time) * 100);

    return 0;
}




// no of process : 2
// arival time, burst time p1: 1 2 
// arival time, burst time p1: 2 5
