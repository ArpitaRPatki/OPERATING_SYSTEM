#include <stdio.h>

int main() {
    int n, frames;
    printf("Enter number of pages: "); scanf("%d", &n);
    int pages[n];
    printf("Enter page string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter number of frames: "); scanf("%d", &frames);

    int frame[frames], order[frames];
    for (int i = 0; i < frames; i++) { frame[i] = -1; order[i] = -1; }

    int hits = 0, faults = 0;
    printf("\nPage\tFrames\t\t\tHit/Fault\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i], found = 0;
        for (int j = 0; j < frames; j++)
            if (frame[j] == page) { found = 1; break; }

        if (!found) {
            int idx = -1;
            // Fill empty frame first
            for (int j = 0; j < frames; j++)
                if (frame[j] == -1) { idx = j; break; }
            // No empty frame, evict LRU
            if (idx == -1) {
                idx = 0;
                for (int j = 1; j < frames; j++)
                    if (order[j] < order[idx]) idx = j;
            }
            frame[idx] = page; order[idx] = i; faults++;
        } else {
            for (int j = 0; j < frames; j++)
                if (frame[j] == page) { order[j] = i; break; }
            hits++;
        }

        printf("%d\t", page);
        for (int j = 0; j < frames; j++)
            printf("%d ", frame[j]);
        printf("\t\t%s\n", found ? "HIT" : "FAULT");
    }
    printf("Hits: %d  Faults: %d\n", hits, faults);
}