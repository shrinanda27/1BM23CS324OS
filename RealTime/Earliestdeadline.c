#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int CT;             // Computation Time
    int RT;             // Remaining Time
    int period;         // Period (release interval)
    int next_release;   // Next release time
    int deadline;       // Relative deadline
    int abs_deadline;   // Absolute deadline (calculated)
} Task;

// Sort tasks by earliest absolute deadline
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
    // Define periodic tasks: {id, CT, RT, period, next_release, deadline, abs_deadline}
    Task tasks[MAX_TASKS] = {
        {1, 2, 0, 5, 0, 5, 0},  // Task 1: CT=2, Period=5, Deadline=5
        {2, 1, 0, 3, 0, 3, 0},  // Task 2: CT=1, Period=3, Deadline=3
        {3, 1, 0, 7, 0, 7, 0}   // Task 3: CT=1, Period=7, Deadline=7
    };

    int numTasks = 3;
    int totalTime = 20;

    EDF(tasks, numTasks, totalTime);

    return 0;
}
