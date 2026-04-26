#include <stdio.h>
#include <stdlib.h>
int main(){
    int n, head;
    printf("Enter number of requests: "); scanf("%d",&n);
    int req[n];
    printf("Enter requests: ");
    for(int i=0;i<n;i++) scanf("%d",&req[i]);
    printf("Enter head position: "); scanf("%d",&head);

    int total=0;
    printf("\nSequence: %d",head);
    for(int i=0;i<n;i++){
        total += abs(req[i]-head);
        head = req[i];
        printf(" -> %d",head);
    }
    printf("\nTotal Seek Time: %d",total);
    printf("\nAverage Seek Time: %.2f\n",(float)total/n);
}