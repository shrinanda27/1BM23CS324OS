#include <stdio.h>
#include <limits.h>

// Structure to hold process information
typedef struct {
    int id, arrival, burst, completion, turnaround, waiting;
} Process;

// SJF Scheduling (Non-Preemptive)
void sjf_non_preemptive(Process p[], int n) {
    int completed = 0, time = 0;
    int isCompleted[n];
    for (int i = 0; i < n; i++) isCompleted[i] = 0;
    
    while (completed < n) {
        int minIdx = -1;
        int minBurst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && p[i].arrival <= time && p[i].burst < minBurst) {
                minBurst = p[i].burst;
                minIdx = i;
            }
        }
        if (minIdx == -1) { time++; continue; }
        
        p[minIdx].completion = time + p[minIdx].burst;
        p[minIdx].turnaround = p[minIdx].completion - p[minIdx].arrival;
        p[minIdx].waiting = p[minIdx].turnaround - p[minIdx].burst;
        time = p[minIdx].completion;
        isCompleted[minIdx] = 1;
        completed++;
    }
}

// Function to display results
void display(Process p[], int n) {
    printf("\nPID Arrival Burst Completion Turnaround Waiting\n");
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        printf("%3d %7d %6d %10d %10d %8d\n", p[i].id, p[i].arrival, p[i].burst, p[i].completion, p[i].turnaround, p[i].waiting);
        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }
    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process p[n];
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("P[%d]: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
    }
    
    printf("\nShortest Job First (Non-Preemptive) Scheduling\n");
    sjf_non_preemptive(p, n);
    display(p, n);
    return 0;
}
