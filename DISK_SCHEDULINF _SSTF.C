#include <stdio.h>
#include <stdlib.h>
int main(){
    int n, head;
    printf("Enter number of requests: "); scanf("%d",&n);
    int req[n], visited[n];
    printf("Enter requests: ");
    for(int i=0;i<n;i++){ scanf("%d",&req[i]); visited[i]=0; }
    printf("Enter head position: "); scanf("%d",&head);

    int total=0;
    printf("\nSequence: %d",head);
    for(int i=0;i<n;i++){
        int minDist=99999, idx=-1;
        for(int j=0;j<n;j++){
            if(!visited[j] && abs(req[j]-head)<minDist){
                minDist = abs(req[j]-head);
                idx = j;
            }
        }
        visited[idx]=1;
        total += minDist;
        head = req[idx];
        printf(" -> %d",head);
    }
    printf("\nTotal Seek Time: %d",total);
    printf("\nAverage Seek Time: %.2f\n",(float)total/n);
}