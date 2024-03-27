#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void prepareKey(char key[], char preparedKey[]);
void createPlayfairMatrix(char key[], char matrix[5][5]);
void encryptPlayfair(char plaintext[], char matrix[5][5]);

int main() {
    char key[26];
    char preparedKey[26];
    char matrix[5][5];
    char plaintext[100];

    printf("Enter the keyword (letters only, no spaces): ");
    fgets(key, sizeof(key), stdin);

    printf("Enter the plaintext to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    prepareKey(key, preparedKey);
    createPlayfairMatrix(preparedKey, matrix);
    encryptPlayfair(plaintext, matrix);

    return 0;
}

// Function to prepare the key by removing duplicates and filling the preparedKey array
void prepareKey(char key[], char preparedKey[]) {
    int keyLength = strlen(key);
    int preparedIndex = 0;

    // Convert the key to uppercase
    for (int i = 0; i < keyLength; i++) {
        if (isalpha(key[i])) {
            key[i] = toupper(key[i]);
        }
    }

    // Remove duplicate letters from the key
    for (int i = 0; i < keyLength; i++) {
        if (isalpha(key[i])) {
            if (!strchr(preparedKey, key[i])) {
                preparedKey[preparedIndex++] = key[i];
            }
        }
    }

    // Fill the remaining characters in preparedKey with the alphabet (except 'J')
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch != 'J' && !strchr(preparedKey, ch)) {
            preparedKey[preparedIndex++] = ch;
        }
    }

    preparedKey[preparedIndex] = '\0';
}

// Function to create the Playfair matrix based on the prepared key
void createPlayfairMatrix(char key[], char matrix[5][5]) {
    int keyIndex = 0;

    // Fill the matrix with the key
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = key[keyIndex++];
        }
    }
}

// Function to encrypt the plaintext using the Playfair matrix
void encryptPlayfair(char plaintext[], char matrix[5][5]) {
    int length = strlen(plaintext);
    int i, j, k;
    char encrypted[1000];
    int encryptedIndex = 0;

    // Convert the plaintext to uppercase
    for (i = 0; i < length; i++) {
        if (isalpha(plaintext[i])) {
            plaintext[i] = toupper(plaintext[i]);
        }
    }

    // Replace 'J' with 'I' in the plaintext
    for (i = 0; i < length; i++) {
        if (plaintext[i] == 'J') {
            plaintext[i] = 'I';
        }
    }

    // Remove non-alphabetic characters and spaces from the plaintext
    k = 0;
    for (i = 0; i < length; i++) {
        if (isalpha(plaintext[i])) {
            plaintext[k++] = plaintext[i];
        }
    }
    plaintext[k] = '\0';

    length = strlen(plaintext); // Update length after removing non-alphabetic characters

    // Ensure the plaintext length is even
    if (length % 2 != 0) {
        strcat(plaintext, "X");
        length++;
    }

    // Encrypt the plaintext two letters at a time
    for (i = 0; i < length; i += 2) {
        char first = plaintext[i];
        char second = plaintext[i + 1];
        int row1, col1, row2, col2;

        // Find the positions of the letters in the matrix
        for (j = 0; j < 5; j++) {
            for (k = 0; k < 5; k++) {
                if (matrix[j][k] == first) {
                    row1 = j;
                    col1 = k;
                }
                if (matrix[j][k] == second) {
                    row2 = j;
                    col2 = k;
                }
            }
        }

        // Apply the Playfair cipher rules to encrypt the pair of letters
        if (row1 == row2) {
            encrypted[encryptedIndex++] = matrix[row1][(col1 + 1) % 5];
            encrypted[encryptedIndex++] = matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            encrypted[encryptedIndex++] = matrix[(row1 + 1) % 5][col1];
            encrypted[encryptedIndex++] = matrix[(row2 + 1) % 5][col2];
        } else {
            encrypted[encryptedIndex++] = matrix[row1][col2];
            encrypted[encryptedIndex++] = matrix[row2][col1];
        }
    }

    encrypted[encryptedIndex] = '\0';

    printf("Ciphered String: %s\n", encrypted);
}

