#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid, at, bt, priority;
    int ct, tat, wt, rt;
    int done, started;
} Process;

void priority_non_preemptive(Process p[], int n) {
    int time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    printf("\nOrder of Execution (Gantt Chart):\n|");

    while (completed < n) {
        int idx = -1, highestPriority = INT_MAX;

        // Select process with highest priority (smallest number = higher priority)
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (p[i].priority < highestPriority) {
                    highestPriority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) { // CPU idle
            printf(" idle |");
            time++;
            continue;
        }

        // Response Time
        if (!p[idx].started) {
            p[idx].rt = time - p[idx].at;
            p[idx].started = 1;
        }

        // Execute process fully (non-preemptive)
        printf(" P%d |", p[idx].pid);
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = 1;
        completed++;

        totalWT += p[idx].wt;
        totalTAT += p[idx].tat;
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
    }

    priority_non_preemptive(p, n);
    return 0;
}
