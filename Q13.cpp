#include <stdio.h>

#define SIZE 2

// Function to calculate the modular inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse does not exist
}

// Function to decrypt a message using the Hill cipher
void decryptHill(int ciphertext[][SIZE], int key[][SIZE]) {
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    int detInverse = modInverse(det, 26);
    if (detInverse == -1) {
        printf("Error: Determinant is not invertible modulo 26. Choose a different key matrix.\n");
        return;
    }

    // Calculate the inverse of the key matrix
    int keyInverse[SIZE][SIZE];
    keyInverse[0][0] = key[1][1];
    keyInverse[0][1] = -key[0][1];
    keyInverse[1][0] = -key[1][0];
    keyInverse[1][1] = key[0][0];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            keyInverse[i][j] *= detInverse;
            keyInverse[i][j] %= 26;
            if (keyInverse[i][j] < 0) {
                keyInverse[i][j] += 26;
            }
        }
    }

    // Decrypt the ciphertext matrix using the inverse key matrix
    int decryptedMatrix[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            decryptedMatrix[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                decryptedMatrix[i][j] += keyInverse[i][k] * ciphertext[k][j];
            }
            decryptedMatrix[i][j] %= 26; // Apply modulo 26 for each element
        }
    }

    // Print the decrypted message
    printf("Decrypted Message: ");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c", decryptedMatrix[i][j] + 'A');
        }
    }
    printf("\n");
}

int main() {
    // Example known plaintext-ciphertext pair
    int ciphertext[SIZE][SIZE] = {{17, 20}, {5, 3}};
    int key[SIZE][SIZE] = {{3, 7}, {8, 11}}; // A key matrix with a invertible determinant

    decryptHill(ciphertext, key);

    return 0;
}

