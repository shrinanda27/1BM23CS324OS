#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 5

int forks[N] = {1, 1, 1, 1, 1}; // 1: available, 0: in use
int mutex = 1;                  // critical section control
int eating[N] = {0};            // 1 if philosopher is currently eating

void wait(int *s) {
    while (*s <= 0);
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void pickup(int i) {
    wait(&mutex);

    if (forks[i] == 1 && forks[(i + 1) % N] == 1 && !eating[i]) {
        forks[i] = 0;
        forks[(i + 1) % N] = 0;
        eating[i] = 1;
        printf("Philosopher %d picks up forks %d and %d and starts EATING.\n", i, i, (i + 1) % N);
    } else {
        printf("Philosopher %d can't eat now. Forks not available or already eating.\n", i);
    }

    signal(&mutex);
}

void putdown(int i) {
    wait(&mutex);

    if (eating[i]) {
        forks[i] = 1;
        forks[(i + 1) % N] = 1;
        eating[i] = 0;
        printf("Philosopher %d puts down forks %d and %d and starts THINKING.\n", i, i, (i + 1) % N);
    } else {
        printf("Philosopher %d is not eating. Nothing to put down.\n", i);
    }

    signal(&mutex);
}

void showForks() {
    printf("Forks: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", forks[i]);
    }
    printf(" | Eating: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", eating[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    while (1) {
        int choice = rand() % 2;
        int id = rand() % N;

        showForks();
        if (choice == 0) {
            pickup(id);
        } else {
            putdown(id);
        }
        sleep(1);
    }

    return 0;
}
