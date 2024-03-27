#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initial permutation IP
int IP[] = {2, 6, 3, 1, 4, 8, 5, 7};

// Final permutation IP^-1
int IP_INV[] = {4, 1, 3, 5, 7, 2, 8, 6};

// Expansion permutation E/P
int EP[] = {4, 1, 2, 3, 2, 3, 4, 1};

// Permutation P4
int P4[] = {2, 4, 3, 1};

// S-boxes (S0 and S1)
int S0[4][4] = {{1, 0, 3, 2},
                {3, 2, 1, 0},
                {0, 2, 1, 3},
                {3, 1, 3, 2}};

int S1[4][4] = {{0, 1, 2, 3},
                {2, 0, 1, 3},
                {3, 0, 1, 0},
                {2, 1, 0, 3}};

// Function declarations
void generateKey(char *key, char *key1, char *key2);
void initialPermutation(char *block);
void finalPermutation(char *block);
void expand(char *input, char *output);
void xorArrays(char *arr1, char *arr2, char *result, int size);
void substitution(char *input, char *output);
void permuteP4(char *input, char *output);
void sdesEncrypt(char *plaintext, char *key, char *ciphertext);
void sdesDecrypt(char *ciphertext, char *key, char *plaintext);

// Key generation
void generateKey(char *key, char *key1, char *key2) {
    // Permuted choice 1 (PC-1)
    int PC1[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};

    // Permuted choice 2 (PC-2)
    int PC2[] = {6, 3, 7, 4, 8, 5, 10, 9};

    char tempKey[11]; // Adjusted size to include null terminator
    for (int i = 0; i < 10; i++) {
        tempKey[i] = key[PC1[i] - 1];
    }
    tempKey[10] = '\0'; // Null terminator

    // Split into two halves
    char left[6], right[6];
    memcpy(left, tempKey, 5);
    memcpy(right, tempKey + 5, 5);
    left[5] = '\0'; // Null terminator
    right[5] = '\0'; // Null terminator

    // Perform circular left shifts
    for (int round = 1; round <= 2; round++) {
        // Left shift for both halves
        char tempLeft = left[0];
        char tempRight = right[0];
        for (int i = 0; i < 4; i++) {
            left[i] = left[i + 1];
            right[i] = right[i + 1];
        }
        left[4] = tempLeft;
        right[4] = tempRight;

        // Combine halves and apply PC-2
        char combined[11]; // Adjusted size to include null terminator
        memcpy(combined, left, 5);
        memcpy(combined + 5, right, 5);
        combined[10] = '\0'; // Null terminator
        for (int i = 0; i < 8; i++) {
            key1[i] = combined[PC2[i] - 1];
            key2[i] = combined[PC2[i + 2] - 1]; // Circular shift in PC-2
        }
    }
}

// Initial permutation IP
void initialPermutation(char *block) {
    char temp[9]; // Adjusted size to include null terminator
    for (int i = 0; i < 8; i++) {
        temp[i] = block[IP[i] - 1];
    }
    temp[8] = '\0'; // Null terminator
    memcpy(block, temp, 8);
}

// Final permutation IP^-1
void finalPermutation(char *block) {
    char temp[9]; // Adjusted size to include null terminator
    for (int i = 0; i < 8; i++) {
        temp[i] = block[IP_INV[i] - 1];
    }
    temp[8] = '\0'; // Null terminator
    memcpy(block, temp, 8);
}

// Expansion permutation E/P
void expand(char *input, char *output) {
    for (int i = 0; i < 8; i++) {
        output[i] = input[EP[i] - 1];
    }
}

// XOR operation on two arrays
void xorArrays(char *arr1, char *arr2, char *result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = (arr1[i] - '0') ^ (arr2[i] - '0') + '0';
    }
}

// S-box substitution
void substitution(char *input, char *output) {
    int row, col, val;
    row = (input[0] - '0') * 2 + (input[3] - '0');
    col = (input[1] - '0') * 2 + (input[2] - '0');
    val = S0[row][col];
    output[0] = ((val >> 1) & 1) + '0';
    output[1] = (val & 1) + '0';

    row = (input[4] - '0') * 2 + (input[7] - '0');
    col = (input[5] - '0') * 2 + (input[6] - '0');
    val = S1[row][col];
    output[2] = ((val >> 1) & 1) + '0';
    output[3] = (val & 1) + '0';
}

// Permutation P4
void permuteP4(char *input, char *output) {
    for (int i = 0; i < 4; i++) {
        output[i] = input[P4[i] - 1];
    }
}

// Simplified Data Encryption Standard (S-DES) encryption function
void sdesEncrypt(char *plaintext, char *key, char *ciphertext) {
    char key1[8], key2[8];
    generateKey(key, key1, key2);

    // Initial permutation
    initialPermutation(plaintext);

    // Split into two halves
    char left[4], right[4];
    memcpy(left, plaintext, 4);
    memcpy(right, plaintext + 4, 4);

    // First round
    char temp[4], expanded[8], xorResult[8], substituted[4], permuted[4];
    expand(right, expanded);
    xorArrays(expanded, key1, xorResult, 8);
    substitution(xorResult, substituted);
    permuteP4(substituted, temp);
    xorArrays(temp, left, temp, 4);
    memcpy(left, right, 4);
    memcpy(right, temp, 4);

    // Second round
    expand(right, expanded);
    xorArrays(expanded, key2, xorResult, 8);
    substitution(xorResult, substituted);
    permuteP4(substituted, temp);
    xorArrays(temp, left, temp, 4);

    // Final permutation
    memcpy(ciphertext, temp, 4);
    memcpy(ciphertext + 4, right, 4);
    finalPermutation(ciphertext);
}

// S-DES decryption function (inverse of encryption)
void sdesDecrypt(char *ciphertext, char *key, char *plaintext) {
    char key1[8], key2[8];
    generateKey(key, key1, key2);

    // Initial permutation
    initialPermutation(ciphertext);

    // Split into two halves
    char left[4], right[4];
    memcpy(left, ciphertext, 4);
    memcpy(right, ciphertext + 4, 4);

    // First round
    char temp[4], expanded[8], xorResult[8], substituted[4], permuted[4];
    expand(right, expanded);
    xorArrays(expanded, key2, xorResult, 8);
    substitution(xorResult, substituted);
    permuteP4(substituted, temp);
    xorArrays(temp, left, temp, 4);
    memcpy(left, right, 4);
    memcpy(right, temp, 4);

    // Second round
    expand(right, expanded);
    xorArrays(expanded, key1, xorResult, 8);
    substitution(xorResult, substituted);
    permuteP4(substituted, temp);
    xorArrays(temp, left, temp, 4);

    // Final permutation
    memcpy(plaintext, temp, 4);
    memcpy(plaintext + 4, right, 4);
    finalPermutation(plaintext);
}

int main() {
    char plaintext[25] = "000000010000001000000100"; // Binary plaintext: 0000 0001 0000 0010 0000 0100
    char key[11] = "0111111101"; // Binary key: 01111 11101
    char ciphertext[8], decryptedText[8];

    // Encrypt plaintext
    sdesEncrypt(plaintext, key, ciphertext);
    printf("Encrypted ciphertext: %s\n", ciphertext);

    // Decrypt ciphertext
    sdesDecrypt(ciphertext, key, decryptedText);
    printf("Decrypted plaintext: %s\n", decryptedText);

    return 0;
}

