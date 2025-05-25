#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id, AT, BT, TAT, WT, CT, BTL;
};

void sorted(struct Process p[], int n) {
    int i, j;
    for (i = 1; i < n; i++) {
        for (j = 0; j < n - i; j++) { 
            if (p[j].AT > p[j + 1].AT || (p[j].AT == p[j + 1].AT && p[j].id > p[j + 1].id)) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void print_process_data(struct Process p[], int n) {
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }

    int ttat = 0, twt = 0;
    for (int i = 0; i < n; i++) {
        ttat += p[i].TAT;
        twt += p[i].WT;
    }

    double avg_tat = (double)ttat / n;
    double avg_wt = (double)twt / n;

    printf("Average Turn-around time: %lf\n", avg_tat);
    printf("Average Waiting time: %lf\n", avg_wt);
}

void robin(struct Process p[],int n,int tq){
    int ct=0,completed=0;
    for (int i = 0; i < n; i++)
    {
        p[i].BTL = p[i].BT;
    }

    while(completed<n){
        for (int i = 0; i < n; i++)
        {
            if(p[i].BTL != 0)
            {
                if (p[i].BTL>tq)
                {
                    p[i].BTL -= tq;
                    ct+= tq;
                }
                else
                {
                    ct+= p[i].BTL;
                    p[i].BTL = 0;
                    p[i].CT=ct;
                    completed++;

                }  
            }
        }
        
    }

    for(int i=0;i<n;i++){
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;
    }
    
}

void main(){
    int n,tq;
    printf("Enter Number of Processes");
    scanf("%d",&n);
    printf("Enter Time Quantum");
    scanf("%d",&tq);
    struct Process p[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter Process %d AT AND BT\n",i+1);
        p[i].id=i+1;
        scanf("%d %d",&p[i].AT,&p[i].BT);
    }
    
    sorted(p,n);
    robin(p,n,tq);
    print_process_data(p,n);
}
