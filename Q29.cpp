#include <stdio.h>
#include <stdint.h>

#define STATE_SIZE 25
#define LANE_SIZE_BITS 64
#define CAPACITY_LANES 6

// Define the state matrix as a 5x5 array of 64-bit integers
typedef uint64_t state_t[STATE_SIZE];

// Function to print the state matrix in a readable format
void printState(const state_t state) {
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            printf("%016llx ", state[row * 5 + col]);
        }
        printf("\n");
    }
}

// Function to fill the lanes until all capacity lanes have at least one nonzero bit
void fillLanes(state_t state) {
    int filledLanes = 0;

    while (filledLanes < CAPACITY_LANES) {
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                if (filledLanes >= CAPACITY_LANES) {
                    return;
                }

                // Check if the lane is empty
                if (state[row * 5 + col] == 0) {
                    // Simulate setting a nonzero value (e.g., 0x1) in the lane
                    state[row * 5 + col] = 0x1;
                    filledLanes++;
                }
            }
        }
    }
}

int main() {
    state_t state = {0}; // Initialize all lanes to zero

    printf("Initial State Matrix:\n");
    printState(state);

    // Fill the lanes until all capacity lanes have at least one nonzero bit
    fillLanes(state);

    printf("\nFinal State Matrix after filling lanes:\n");
    printState(state);

    return 0;
}

