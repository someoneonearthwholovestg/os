#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct PageTable {
    int frame_no;
    bool valid;
};

// Check if the page is already present
bool isPagePresent(struct PageTable PT[], int page) {
    return PT[page].valid;
}

// Update the page table entry
void updatePageTable(struct PageTable PT[], int page, int fr_no, int status) {
    PT[page].valid = status;
    if (status)
        PT[page].frame_no = fr_no;
}

// Print current contents of frames
void printFrames(int frame[], int no_of_frames) {
    for (int i = 0; i < no_of_frames; i++)
        printf("%d ", frame[i]);
    printf("\n");
}

int main() {
    int n, no_of_frames, page_fault = 0, current = 0;

    // Input number of pages
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int reference_string[n];
    printf("Enter the reference string (one page number at a time):\n");
    for (int i = 0; i < n; i++) {
        printf("Page %d: ", i + 1);
        scanf("%d", &reference_string[i]);
    }

    // Input number of frames
    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);

    // Initialize frame array
    int frame[no_of_frames];
    for (int i = 0; i < no_of_frames; i++)
        frame[i] = -1;

    // Initialize page table
    struct PageTable PT[50]; // Supports pages 0-49
    for (int i = 0; i < 50; i++)
        PT[i].valid = false;

    printf("\nFrame contents at each step:\n");

    for (int i = 0; i < n; i++) {
        int page = reference_string[i];

        if (!isPagePresent(PT, page)) {
            page_fault++;

            // Invalidate page being replaced, if any
            if (frame[current] != -1) {
                updatePageTable(PT, frame[current], -1, 0);
            }

            // Place new page in frame
            frame[current] = page;
            updatePageTable(PT, page, current, 1);

            printFrames(frame, no_of_frames);

            // Move to next frame (FIFO)
            current = (current + 1) % no_of_frames;
        }
    }

    // Print statistics
    printf("\nTotal Page Faults = %d\n", page_fault);
    printf("Page Fault Ratio = %.2f\n", (float)page_fault / n);
    printf("Page Hit Ratio = %.2f\n", (float)(n - page_fault) / n);

    return 0;
}



//Enter number of pages: 10
//Enter the reference string (one page number at a time):
//Page 1: 1
//Page 2: 2
//Page 3: 3
//Page 4: 4
//Page 5: 1
//Page 6: 2
//Page 7: 5
//Page 8: 1
//Page 9: 2
//Page 10: 3
//Enter number of frames: 3

