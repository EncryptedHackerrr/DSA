#include <stdio.h>

typedef struct {
    int pid, at, bt, remaining;
    int ct, tat, wt, rt;
    int started, done;
} Process;

void round_robin(Process p[], int n, int tq) {
    int time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;
    int queue[100], front = 0, rear = 0;
    int inQueue[n];
    for (int i = 0; i < n; i++) inQueue[i] = 0;

    printf("\nOrder of Execution (Gantt Chart):\n|");

    // Add first available process to queue
    for (int i = 0; i < n; i++) {
        if (p[i].at == 0) {
            queue[rear++] = i;
            inQueue[i] = 1;
        }
    }

    while (completed < n) {
        if (front == rear) { // CPU idle
            printf(" idle |");
            time++;
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && !p[i].done && p[i].at <= time) {
                    queue[rear++] = i;
                    inQueue[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];

        if (!p[idx].started) {
            p[idx].rt = time - p[idx].at;
            p[idx].started = 1;
        }

        printf(" P%d |", p[idx].pid);

        int execTime = (p[idx].remaining > tq) ? tq : p[idx].remaining;
        time += execTime;
        p[idx].remaining -= execTime;

        // Add new arrivals during execution
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && !p[i].done && p[i].at <= time) {
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }

        if (p[idx].remaining > 0) {
            queue[rear++] = idx; // Re-queue process
        } else {
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
    int n, tq;
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

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    round_robin(p, n, tq);
    return 0;
}
