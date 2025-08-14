#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid, at, bt, priority;
    int remaining, ct, tat, wt, rt;
    int started, done;
} Process;

void priority_preemptive(Process p[], int n) {
    int time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;
    int lastPid = -1;

    printf("\nOrder of Execution (Gantt Chart):\n|");

    while (completed < n) {
        int idx = -1, highestPriority = INT_MAX;

        // Find highest priority process available at this time
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (p[i].priority < highestPriority) {
                    highestPriority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) { // CPU idle
            if (lastPid != -2) {
                printf(" idle |");
                lastPid = -2;
            }
            time++;
            continue;
        }

        // First time response
        if (!p[idx].started) {
            p[idx].rt = time - p[idx].at;
            p[idx].started = 1;
        }

        // Print Gantt chart block only if process changes
        if (lastPid != p[idx].pid) {
            printf(" P%d |", p[idx].pid);
            lastPid = p[idx].pid;
        }

        // Execute for 1 time unit
        p[idx].remaining--;
        time++;

        // If finished
        if (p[idx].remaining == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].done = 1;
            completed++;

            totalWT += p[idx].wt;
            totalTAT += p[idx].tat;
        }
    }

    // Output table
    printf("\n\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].priority,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage WT = %.2f", totalWT / n);
    printf("\nAverage TAT = %.2f\n", totalTAT / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].done = 0;
        p[i].started = 0;
        printf("Enter AT, BT, Priority for Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].remaining = p[i].bt;
    }

    priority_preemptive(p, n);
    return 0;
}
