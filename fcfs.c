#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], st[n], et[n], tat[n];

    for (int i = 0; i < n; i++) {
        printf("PID, AT, BT for process %d: ", i + 1);
        scanf("%d %d %d", &pid[i], &at[i], &bt[i]);
    }

    // Sort by AT, tie-break by BT
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (at[j] > at[j+1] || (at[j] == at[j+1] && bt[j] > bt[j+1])) {
                int tmp;
                tmp = pid[j]; pid[j] = pid[j+1]; pid[j+1] = tmp;
                tmp =  at[j];  at[j] =  at[j+1];  at[j+1] = tmp;
                tmp =  bt[j];  bt[j] =  bt[j+1];  bt[j+1] = tmp;
            }

    // Calculate times
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < at[i]) time = at[i];
        st[i]  = time;
        et[i]  = st[i] + bt[i];
        tat[i] = et[i] - at[i];
        time   = et[i];
    }

    // Table
    printf("\nPID\tAT\tBT\tST\tET\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], st[i], et[i], tat[i]);

    // Gantt chart
    printf("\nGantt Chart:\n");
    time = 0;
    for (int i = 0; i < n; i++) {
        if (time < at[i]) {
            printf("| IDLE ");
            time = at[i];
        }
        printf("| P%d ", pid[i]);
        time = et[i];
    }
    printf("|\n");

    // Time markers
    time = 0;
    printf("0");
    for (int i = 0; i < n; i++) {
        if (time < at[i]) {
            printf("     %d", at[i]);
            time = at[i];
        }
        printf("    %d", et[i]);
        time = et[i];
    }
    printf("\n");

    return 0;
}
