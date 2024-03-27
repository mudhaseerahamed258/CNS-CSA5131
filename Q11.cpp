#include <stdio.h>

// Function to calculate factorial
unsigned long long factorial(int n) {
    unsigned long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    int key_size = 25; // Size of the Playfair key matrix (5x5 with 'I/J' combined)
    unsigned long long total_keys = factorial(key_size);

    // Number of effectively unique keys (considering duplicates)
    // For Playfair cipher, row and column permutations are equivalent
    unsigned long long unique_keys = total_keys / (4 * 3 * 2); // Divide by factorial(4) for row permutations

    printf("Total number of keys: %llu\n", total_keys);
    printf("Number of effectively unique keys: %llu\n", unique_keys);

    return 0;
}

