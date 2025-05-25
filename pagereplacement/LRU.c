#include<stdio.h>

int main() {
    int frames, pages, pageFaults = 0;
    int referenceString[100], frame[100]; // Max size to prevent runtime issues
    int recent[100]; // To track the order of pages for LRU

    printf("Enter number of frames: ");
    scanf("%d", &frames);
    printf("Enter number of pages: ");
    scanf("%d", &pages);
    printf("Enter reference string: ");
    for (int i = 0; i < pages; i++) {
        scanf("%d", &referenceString[i]);
    }

    // Initialize frames to -1 (indicating empty frames)
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        recent[i] = -1; // Initialize recent access time
    }

    // Process each page in the reference string
    for (int i = 0; i < pages; i++) {
        int found = 0;

        // Check if the page is already in one of the frames
        for (int j = 0; j < frames; j++) {
            if (frame[j] == referenceString[i]) {
                found = 1;  // Page hit, no page fault
                // Update recent access to indicate it's the most recently used
                recent[j] = i;
                break;
            }
        }

        // If the page is not found, we need to replace a page
        if (!found) {
            int emptyFrame = -1;

            // Check for empty frames and place the new page there if available
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    emptyFrame = j;  // Find the first empty frame
                    break;
                }
            }

            if (emptyFrame != -1) {
                // Place the page in the empty frame
                frame[emptyFrame] = referenceString[i];
                recent[emptyFrame] = i; // Mark the access time as the current index
                pageFaults++;  // Increment page fault
            } else {
                // If no empty frame, we need to replace the least recently used page
                int lruIndex = 0;
                for (int j = 1; j < frames; j++) {
                    if (recent[j] < recent[lruIndex]) {
                        lruIndex = j;  // Find the least recently used page
                    }
                }

                // Replace the least recently used page
                frame[lruIndex] = referenceString[i];
                recent[lruIndex] = i; // Update the access time for the replaced page
                pageFaults++;  // Increment page fault
            }
        }

        // Display the current state of the frames
        printf("%d: ", referenceString[i]);
        for (int k = 0; k < frames; k++) {
            printf("%d ", frame[k]);
        }
        printf("\n");
    }

    // Output total page faults
    printf("Total Page Faults: %d\n", pageFaults);
    return 0;
}
