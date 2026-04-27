#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], pr[n], st[n], et[n], tat[n], done[n];
    for (int i = 0; i < n; i++) {
        printf("PID AT BT Priority for process %d: ", i + 1);
        scanf("%d %d %d %d", &pid[i], &at[i], &bt[i], &pr[i]);
        done[i] = 0;
    }

    int time = 0, completed = 0;
    int g_pid[50], g_st[50], g_et[50], g = 0;

    while (completed < n) {
        // Find arrived process with highest priority (lowest number)
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time) {
                if (idx == -1 || pr[i] < pr[idx] || (pr[i] == pr[idx] && at[i] < at[idx]))
                    idx = i;
            }
        }

        if (idx == -1) { time++; continue; } // idle

        st[idx]  = time;
        et[idx]  = time + bt[idx];
        tat[idx] = et[idx] - at[idx];
        done[idx] = 1;
        g_pid[g] = pid[idx]; g_st[g] = st[idx]; g_et[g] = et[idx]; g++;
        time = et[idx];
        completed++;
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
