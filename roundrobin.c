#include <stdio.h>

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &tq);

    int pid[n], at[n], bt[n], rt[n], st[n], et[n], tat[n], started[n];
    for (int i = 0; i < n; i++) {
        printf("PID AT BT for process %d: ", i + 1);
        scanf("%d %d %d", &pid[i], &at[i], &bt[i]);
        rt[i] = bt[i];
        started[i] = 0;
    }

    int time = 0, completed = 0;
    int g_pid[500], g_st[500], g_et[500], g = 0;

    // Queue
    int queue[500], front = 0, rear = 0;
    int inqueue[n];
    for (int i = 0; i < n; i++) inqueue[i] = 0;

    // Add processes that arrive at time 0
    for (int i = 0; i < n; i++)
        if (at[i] == 0) { queue[rear++] = i; inqueue[i] = 1; }

    while (completed < n) {
        if (front == rear) { // queue empty, CPU idle
            time++;
            for (int i = 0; i < n; i++)
                if (!inqueue[i] && rt[i] > 0 && at[i] <= time)
                    { queue[rear++] = i; inqueue[i] = 1; }
            continue;
        }

        int idx = queue[front++];

        if (!started[idx]) { st[idx] = time; started[idx] = 1; }

        int run = (rt[idx] < tq) ? rt[idx] : tq;

        g_pid[g] = pid[idx]; g_st[g] = time; g_et[g] = time + run; g++;

        time   += run;
        rt[idx] -= run;

        // Add newly arrived processes to queue
        for (int i = 0; i < n; i++)
            if (!inqueue[i] && rt[i] > 0 && at[i] <= time)
                { queue[rear++] = i; inqueue[i] = 1; }

        if (rt[idx] == 0) {
            et[idx]  = time;
            tat[idx] = et[idx] - at[idx];
            completed++;
        } else {
            queue[rear++] = idx; // re-add to queue
        }
    }

    // Table
    printf("\nPID\tAT\tBT\tST\tET\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], st[i], et[i], tat[i]);

    // Gantt chart
    printf("\nGantt Chart:\n");
    int t = 0;
    for (int i = 0; i < g; i++) {
        if (t < g_st[i]) { printf("| IDLE "); t = g_st[i]; }
        printf("| P%d ", g_pid[i]);
        t = g_et[i];
    }
    printf("|\n");

    t = 0;
    printf("0");
    for (int i = 0; i < g; i++) {
        if (t < g_st[i]) { printf("     %d", g_st[i]); t = g_st[i]; }
        printf("    %d", g_et[i]);
        t = g_et[i];
    }
    printf("\n");

    return 0;
}
