#include <stdio.h>
#include <stdlib.h>

// helper: absolute value
int abss(int a) { return a < 0 ? -a : a; }

// sort array
void sort(int a[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-1-i; j++)
            if (a[j] > a[j+1]) { int t = a[j]; a[j] = a[j+1]; a[j+1] = t; }
}

// ─── SCAN ───
// goes right to end, then reverses left to start
void scan(int req[], int n, int head, int maxCyl) {
    int r[n]; for (int i=0;i<n;i++) r[i]=req[i];
    sort(r, n);

    int seek = 0, cur = head;
    printf("\n─── SCAN ───\nSequence: %d", head);

    // go right
    for (int i = 0; i < n; i++)
        if (r[i] >= head) { seek += abss(cur - r[i]); cur = r[i]; printf(" -> %d", r[i]); }

    // go to end
    seek += abss(cur - maxCyl); cur = maxCyl;
    printf(" -> %d", maxCyl);

    // go left
    for (int i = n-1; i >= 0; i--)
        if (r[i] < head) { seek += abss(cur - r[i]); cur = r[i]; printf(" -> %d", r[i]); }

    printf("\nTotal Seek: %d\n", seek);
}

// ─── C-SCAN ───
// goes right to end, jumps to 0, continues right
void cscan(int req[], int n, int head, int maxCyl) {
    int r[n]; for (int i=0;i<n;i++) r[i]=req[i];
    sort(r, n);

    int seek = 0, cur = head;
    printf("\n─── C-SCAN ───\nSequence: %d", head);

    // go right
    for (int i = 0; i < n; i++)
        if (r[i] >= head) { seek += abss(cur - r[i]); cur = r[i]; printf(" -> %d", r[i]); }

    // go to end then jump to 0
    seek += abss(cur - maxCyl) + maxCyl;
    cur = 0;
    printf(" -> %d -> 0", maxCyl);

    // continue right from 0
    for (int i = 0; i < n; i++)
        if (r[i] < head) { seek += abss(cur - r[i]); cur = r[i]; printf(" -> %d", r[i]); }

    printf("\nTotal Seek: %d\n", seek);
}

// ─── LOOK ───
// goes right to last request, then reverses left to first request (no going to end)
void look(int req[], int n, int head) {
    int r[n]; for (int i=0;i<n;i++) r[i]=req[i];
    sort(r, n);

    int seek = 0, cur = head;
    printf("\n─── LOOK ───\nSequence: %d", head);

    // go right
    for (int i = 0; i < n; i++)
        if (r[i] >= head) { seek += abss(cur - r[i]); cur = r[i]; printf(" -> %d", r[i]); }

    // go left (no going to maxCyl)
    for (int i = n-1; i >= 0; i--)
        if (r[i] < head) { seek += abss(cur - r[i]); cur = r[i]; printf(" -> %d", r[i]); }

    printf("\nTotal Seek: %d\n", seek);
}

// ─── C-LOOK ───
// goes right to last request, jumps to first request, continues right
void clook(int req[], int n, int head) {
    int r[n]; for (int i=0;i<n;i++) r[i]=req[i];
    sort(r, n);

    int seek = 0, cur = head;
    printf("\n─── C-LOOK ───\nSequence: %d", head);

    // go right
    for (int i = 0; i < n; i++)
        if (r[i] >= head) { seek += abss(cur - r[i]); cur = r[i]; printf(" -> %d", r[i]); }

    // jump to smallest request
    if (r[0] < head) {
        seek += abss(cur - r[0]); cur = r[0];
        printf(" -> %d", r[0]);
        // continue right from there
        for (int i = 1; i < n; i++)
            if (r[i] < head) { seek += abss(cur - r[i]); cur = r[i]; printf(" -> %d", r[i]); }
    }

    printf("\nTotal Seek: %d\n", seek);
}

int main() {
    int n, head, maxCyl;
    printf("Enter number of requests: "); scanf("%d", &n);
    int req[n];
    printf("Enter requests: ");
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter initial head position: "); scanf("%d", &head);
    printf("Enter max cylinder (disk size-1): "); scanf("%d", &maxCyl);

    scan (req, n, head, maxCyl);
    cscan(req, n, head, maxCyl);
    look (req, n, head);
    clook(req, n, head);

    return 0;
}
