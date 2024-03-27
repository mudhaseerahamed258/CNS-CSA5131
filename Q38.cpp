#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MATRIX_SIZE 2

int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1;
}

void matrix_multiply(int key[MATRIX_SIZE][MATRIX_SIZE], int *plaintext, int *result) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        result[i] = 0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i] += key[i][j] * plaintext[j];
        }
        result[i] %= 26;
    }
}

void encrypt_hill(const int key[MATRIX_SIZE][MATRIX_SIZE], const char *plaintext, char *ciphertext) {
    int len = strlen(plaintext);
    int padded_len = len + (MATRIX_SIZE - len % MATRIX_SIZE) % MATRIX_SIZE;
    int *plain_num = (int *)malloc(padded_len * sizeof(int));
    for (int i = 0; i < padded_len; i++) {
        plain_num[i] = (i < len) ? plaintext[i] - 'a' : 25; // Padding with 'z'
    }

    for (int i = 0; i < padded_len; i += MATRIX_SIZE) {
        int result[MATRIX_SIZE];
        matrix_multiply(key, &plain_num[i], result);
        for (int j = 0; j < MATRIX_SIZE; j++) {
            ciphertext[i + j] = result[j] + 'a';
        }
    }
    ciphertext[padded_len] = '\0';

    free(plain_num);
}

int main() {
    const int key[MATRIX_SIZE][MATRIX_SIZE] = {{6, 24}, {13, 16}}; // Example key matrix
    const char *plaintext = "hello";
    char ciphertext[10];

    encrypt_hill(key, plaintext, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    return 0;
}

