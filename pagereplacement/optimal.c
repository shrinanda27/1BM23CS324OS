#include<stdio.h>

int main() {
    int frames, pages, pageFaults = 0;
    int referenceString[100], frame[100]; // Max size to prevent runtime issues

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
    }

    // Process each page in the reference string
    for (int i = 0; i < pages; i++) {
        int found = 0;

        // Check if the page is already in one of the frames
        for (int j = 0; j < frames; j++) {
            if (frame[j] == referenceString[i]) {
                found = 1;  // Page hit, no page fault
                break;
            }
        }

        // If the page is not in any of the frames, replace a page using the OPT algorithm
        if (!found) {
            int index = -1;

            // First check for empty frames and put the new page there if available
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {  // Find an empty frame to fill
                    index = j;
                    frame[index] = referenceString[i]; // Place the page in the empty frame
                    pageFaults++;  // Increment page fault when a new page is loaded
                    break;  // Exit as soon as we place the page in an empty frame
                }
            }

            // If no empty frame was found, use the OPT algorithm to find the page to replace
            if (index == -1) {
                int maxDistance = -1;
                for (int j = 0; j < frames; j++) {
                    int nextUse = -1;  // Initialize to -1 to indicate the page won't be used in the future
                    for (int k = i + 1; k < pages; k++) {
                        if (frame[j] == referenceString[k]) {
                            nextUse = k;  // Find the next occurrence of the page
                            break;
                        }
                    }

                    // If a page won't be used again (nextUse == -1), replace it immediately
                    if (nextUse == -1) {
                        index = j;
                        break;
                    }

                    // Track the farthest used page
                    if (nextUse > maxDistance) {
                        maxDistance = nextUse;
                        index = j;
                    }
                }

                // Replace the page in the chosen frame
                frame[index] = referenceString[i];
                pageFaults++;  // Increment page fault when a new page is loaded
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
