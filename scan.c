#include <stdio.h>
int main() {
    int n, head, maxCyl;
    printf("Enter number of requests: "); scanf("%d", &n);
    int req[n];
    printf("Enter requests: ");
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter head position: "); scanf("%d", &head);
    printf("Enter max cylinder: "); scanf("%d", &maxCyl);

    // sort
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-1-i; j++)
            if (req[j] > req[j+1]) { int t=req[j]; req[j]=req[j+1]; req[j+1]=t; }

    int seek = 0, cur = head;
    printf("\nSequence: %d", head);

    // go right
    for (int i = 0; i < n; i++)
        if (req[i] >= head) { seek += req[i]-cur; cur = req[i]; printf(" -> %d", cur); }

    // go to end
    seek += maxCyl - cur; cur = maxCyl;
    printf(" -> %d", maxCyl);

    // go left
    for (int i = n-1; i >= 0; i--)
        if (req[i] < head) { seek += cur-req[i]; cur = req[i]; printf(" -> %d", cur); }

    printf("\nTotal Seek: %d\n", seek);
}
