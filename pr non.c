#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct Process {
    int pid;
    int at; // Arrival Time
    int bt; // Burst Time
    int priority; // Higher number = higher priority
    int ct, wt, tat, rt, start_time;
} ps[100];

int main() {
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%d", &ps[i].at);
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &ps[i].bt);
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &ps[i].priority);
        ps[i].pid = i;
    }

    bool completed[100] = {false};
    int completed_count = 0, current_time = 0, prev = 0;
    bool first_process = true;
    int total_idle = 0;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;

    while(completed_count < n) {
        int max_index = -1;
        int max_priority = -1;
        for(int i = 0; i < n; i++) {
            if(ps[i].at <= current_time && !completed[i]) {
                if(ps[i].priority > max_priority || 
                  (ps[i].priority == max_priority && ps[i].at < ps[max_index].at)) {
                    max_priority = ps[i].priority;
                    max_index = i;
                }
            }
        }

        if(max_index == -1) {
            current_time++; // CPU idle
        } else {
            ps[max_index].start_time = current_time;
            ps[max_index].ct = current_time + ps[max_index].bt;
            ps[max_index].tat = ps[max_index].ct - ps[max_index].at;
            ps[max_index].wt = ps[max_index].tat - ps[max_index].bt;
            ps[max_index].rt = ps[max_index].start_time - ps[max_index].at;

            total_idle += first_process ? 0 : (ps[max_index].start_time - prev);
            first_process = false;
            prev = ps[max_index].ct;

            sum_tat += ps[max_index].tat;
            sum_wt += ps[max_index].wt;
            sum_rt += ps[max_index].rt;

            current_time = ps[max_index].ct;
            completed[max_index] = true;
            completed_count++;
        }
    }

    // Print results
    printf("PID\tAT\tBT\tPR\tST\tCT\tTAT\tWT\tRT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               ps[i].pid, ps[i].at, ps[i].bt, ps[i].priority,
               ps[i].start_time, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
    }

    printf("\nAverage TAT = %.2f", sum_tat/n);
    printf("\nAverage WT  = %.2f", sum_wt/n);
    printf("\nAverage RT  = %.2f\n", sum_rt/n);

    return 0;
}


// 4
// 0 1 2 3    # Arrival times
// 8 4 2 1    # Burst times
// 2 1 3 4    # Priorities (higher number = higher priority)
