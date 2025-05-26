#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

typedef struct {
    int id;
    int CT;             // Computation Time (Burst time)
    int RT;             // Remaining Time
    int period;         // Period (release interval)
    int next_release;   // Next release time
    int deadline;       // Relative deadline
    int abs_deadline;   // Absolute deadline
} Task;

// Sort tasks by earliest absolute deadline (and ID as tie breaker)
void sort_by_deadline(Task tasks[], int n) {
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (tasks[j].abs_deadline > tasks[j + 1].abs_deadline || 
                (tasks[j].abs_deadline == tasks[j + 1].abs_deadline && tasks[j].id > tasks[j + 1].id)) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

void EDF(Task tasks[], int n, int totaltime) {
    for (int t = 0; t < totaltime; t++) {
        // Release new instances of tasks if needed
        for (int i = 0; i < n; i++) {
            if (t == tasks[i].next_release) {
                tasks[i].RT = tasks[i].CT;
                tasks[i].abs_deadline = t + tasks[i].deadline;
                tasks[i].next_release += tasks[i].period;
                printf("Time %d: Task %d released (Deadline at %d)\n", t, tasks[i].id, tasks[i].abs_deadline);
            }
        }

        // Sort tasks by deadline
        sort_by_deadline(tasks, n);

        // Execute task with earliest deadline
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (tasks[i].RT > 0 && t < tasks[i].abs_deadline) {
                printf("Time %d: Executing Task %d\n", t, tasks[i].id);
                tasks[i].RT--;
                executed = 1;

                if (tasks[i].RT == 0) {
                    printf("Time %d: Task %d completed", t + 1, tasks[i].id);
                    if (t + 1 > tasks[i].abs_deadline) {
                        printf(" (Deadline Missed!)");
                    }
                    printf("\n");
                }
                break;
            }
        }

        if (!executed) {
            printf("Time %d: CPU Idle\n", t);
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Task tasks[n];

    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tasks[i].CT);
        tasks[i].id = i + 1;
        tasks[i].RT = 0;               // initially no remaining work
        tasks[i].next_release = 0;     // first release at time 0
        tasks[i].abs_deadline = 0;     // will be set on first release
    }

    printf("Enter the deadlines:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tasks[i].deadline);
    }

    printf("Enter the time periods:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tasks[i].period);
    }

    // Compute hyperperiod (LCM of all periods)
    int hyperperiod = tasks[0].period;
    for (int i = 1; i < n; i++) {
        hyperperiod = lcm(hyperperiod, tasks[i].period);
    }

    printf("\nSystem will execute for hyperperiod (LCM of periods): %d ms\n", hyperperiod);
    printf("Starting Earliest Deadline First (EDF) Scheduling...\n\n");

    EDF(tasks, n, hyperperiod);

    return 0;
}
