#include <stdio.h>

void FCFS(int at[], int bt[], int n) {
    int ct[n], tat[n], wt[n], rt[n];
    int total_wt = 0, total_tat = 0, total_rt = 0, total_ct = 0;
    int time = 0;

    for (int i = 0; i < n; i++) {
        // If CPU is idle, jump to next arrival time
        if (time < at[i]) {
            time = at[i];
        }

        // Response time = time when process starts - arrival time
        rt[i] = time - at[i];

        // Completion time
        time += bt[i];
        ct[i] = time;

        // Turnaround time
        tat[i] = ct[i] - at[i];

        // Waiting time
        wt[i] = tat[i] - bt[i];
    }

    // Totals for averages
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += rt[i];
        total_ct += ct[i];
    }

    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;
    float avg_rt = (float)total_rt / n;
    float avg_ct = (float)total_ct / n;

    // Display process details
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage Completion Time: %.2f\n", avg_ct);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Response Time: %.2f\n", avg_rt);

    // Gantt Chart
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < n; i++) {
        printf("-------");
    }
    printf("\n|");
    for (int i = 0; i < n; i++) {
        printf("  P%d  |", i + 1);
    }
    printf("\n ");
    for (int i = 0; i < n; i++) {
        printf("-------");
    }
    printf("\n%d", at[0] < 0 ? 0 : at[0]);

    for (int i = 0; i < n; i++) {
        printf("     %d", ct[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time of Process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time of Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Sort processes by arrival time for correct FCFS execution
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                int temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
            }
        }
    }

    FCFS(at, bt, n);

    return 0;
}
