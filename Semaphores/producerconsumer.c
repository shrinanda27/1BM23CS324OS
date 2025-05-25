// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sleep()
#include <time.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;
int empty = SIZE;  // semaphore: counts empty slots
int full = 0;      // semaphore: counts full slots
int mutex = 1;     // binary semaphore for mutual exclusion
void wait(int *s) {
    while (*s <= 0); // busy wait
    (*s)--;  // decrement semaphore value
}

void signal(int *s) {
    (*s)++;  // increment semaphore value
}

void produce(int item) {
    wait(&empty);  // wait for an empty slot
    wait(&mutex);  // enter critical section

    buffer[in] = item;
    printf("Produced: %d at %d\n", item, in);
    in = (in + 1) % SIZE;

    signal(&mutex);  // leave critical section
    signal(&full);   // signal that there is a full slot
}

void consume() {
    wait(&full);  // wait for a full slot
    wait(&mutex); // enter critical section

    int item = buffer[out];
    printf("Consumed: %d from %d\n", item, out);
    out = (out + 1) % SIZE;

    signal(&mutex);  // leave critical section
    signal(&empty);   // signal that there is an empty slot
}

int main() {
    int item = 1;
    srand(time(NULL));
    // Simulate producer and consumer running automatically
    while (1) {
        int ch = rand()%2;
        switch(ch){
            case 0: if(full==4){break;}
                    produce(item);  // produce an item
                    item++;         // increment item for next production
                    sleep(1);
                    break;
            case 1: consume();      // consume an item
                    sleep(1);
                    break;
        }

    }

    return 0;
}
