#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], pr[n], rt[n], st[n], et[n], tat[n], started[n];
    for (int i = 0; i < n; i++) {
        printf("PID AT BT Priority for process %d: ", i + 1);
        scanf("%d %d %d %d", &pid[i], &at[i], &bt[i], &pr[i]);
        rt[i] = bt[i];
        started[i] = 0;
    }

    int time = 0, completed = 0;
    int g_pid[500], g_st[500], g_et[500], g = 0;
    int prev = -1;

    while (completed < n) {
        // Find arrived process with highest priority (lowest number)
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0 && at[i] <= time) {
                if (idx == -1 || pr[i] < pr[idx] || (pr[i] == pr[idx] && at[i] < at[idx]))
                    idx = i;
            }
        }

        if (idx == -1) { time++; prev = -1; continue; } // idle

        if (!started[idx]) { st[idx] = time; started[idx] = 1; }

        if (prev != idx) {
            g_pid[g] = pid[idx];
            g_st[g]  = time;
            g_et[g]  = time;
            g++;
        }
        g_et[g-1]++;

        rt[idx]--;
        time++;
        prev = idx;

        if (rt[idx] == 0) {
            et[idx]  = time;
            tat[idx] = et[idx] - at[idx];
            completed++;
        }
    }

    // Table
    printf("\nPID\tAT\tBT\tPR\tST\tET\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], pr[i], st[i], et[i], tat[i]);

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
