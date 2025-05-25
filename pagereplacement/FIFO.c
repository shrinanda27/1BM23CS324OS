#include <stdio.h>

int main() {
	int frames, pages, pageFaults = 0, current = 0;
	int referenceString[100], frame[100]; // Max size to prevent runtime issues

	printf("Enter number of frames: "); 
    scanf("%d", &frames); 
    printf("Enter number of pages: "); 
    scanf("%d", &pages); 
    printf("Enter reference string: "); 
    for (int i = 0; i < pages; i++) { 
        scanf("%d", &referenceString[i]); 
    }

	// Initialize frames
	for (int i = 0; i < frames; i++) {
		frame[i] = -1;
	}

	for (int i = 0; i < pages; i++) {
		int found = 0;
		for (int j = 0; j < frames; j++) {
			if (frame[j] == referenceString[i]) {
				found = 1;
				break;
			}
		}
		if (!found) {
			frame[current] = referenceString[i];
			current = (current + 1) % frames;
			pageFaults++;
		}
		printf("%d: ", referenceString[i]); 
        for (int k = 0; k < frames; k++) { 
        printf("%d ", frame[k]); 
        } 
        printf("\n");
	}

	printf("Total Page Faults: %d\n", pageFaults);
	return 0;
}
