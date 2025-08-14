#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid, at, bt, remaining;
    int ct, tat, wt, rt;
    int started, done;
} Process;

void srtf(Process p[], int n) {
    int time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    printf("\nOrder of Execution (Gantt Chart):\n|");

    while (completed < n) {
        int idx = -1, minBT = INT_MAX;

        // Find the process with shortest remaining time available at this time
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time && p[i].remaining < minBT && p[i].remaining > 0) {
                minBT = p[i].remaining;
                idx = i;
            }
        }

        if (idx == -1) { // No process available
            printf(" idle |");
            time++;
            continue;
        }

        // First time this process starts
        if (!p[idx].started) {
            p[idx].rt = time - p[idx].at;
            p[idx].started = 1;
        }

        printf(" P%d |", p[idx].pid);

        p[idx].remaining--;
        time++;

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
    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
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
        printf("Enter AT, BT for Process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].remaining = p[i].bt;
    }

    srtf(p, n);
    return 0;
}
