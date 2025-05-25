#include <stdio.h>

typedef struct {
    int id, arrival, burst, remaining, waiting, turnaround, completion,response;
} Process;

void sjfPreemptive(Process p[], int n) {
    int completed = 0, time = 0, minIndex, minBurst;
    while (completed < n) {
        minIndex = -1, minBurst = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (p[i].remaining < minBurst || (p[i].remaining == minBurst && p[i].arrival < p[minIndex].arrival)) {
                    minBurst = p[i].remaining;
                    minIndex = i;
                }
            }
        }

        if (minIndex == -1) {
            time++;
            continue;
        }

        p[minIndex].remaining--;
        time++;

        if (p[minIndex].remaining == 0) {
            p[minIndex].completion = time;
            p[minIndex].turnaround = p[minIndex].completion - p[minIndex].arrival;
            p[minIndex].waiting = p[minIndex].turnaround - p[minIndex].burst;
            completed++;
        }
    }
}

void displayResults(Process p[], int n, const char *title) {
    printf("\n--- %s ---\n", title);
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    float totalWT = 0, totalTAT = 0, totalRT = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].completion, p[i].turnaround, p[i].waiting);
        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    printf("Average Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
}

int main() {
    int n, choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process p[n];
    printf("Enter Arrival Time and Burst Time:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1; // Auto-generate PID
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
    }
    sjfPreemptive(p, n);
    displayResults(p, n, "Shortest Job First (Preemptive)");
    return 0;
}
