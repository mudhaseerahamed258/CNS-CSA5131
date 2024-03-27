#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to preprocess the message (remove spaces, handle 'J' and 'I' substitution)
void preprocessMessage(char *message) {
    int len = strlen(message);
    int index = 0;
    for (int i = 0; i < len; i++) {
        char ch = toupper(message[i]);
        if (ch >= 'A' && ch <= 'Z') {
            if (ch == 'J') {
                message[index++] = 'I';
            } else {
                message[index++] = ch;
            }
        }
    }
    message[index] = '\0';
}

// Function to find the row and column of a character in the Playfair matrix
void findPosition(char (*matrix)[5], char ch, int *row, int *col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt using the Playfair cipher
void encryptPlayfair(char *message, char (*matrix)[5], char *ciphertext) {
    int len = strlen(message);
    int index = 0;
    for (int i = 0; i < len; i += 2) {
        char a = message[i];
        char b = (i + 1 < len) ? message[i + 1] : 'X'; // Add 'X' if message length is odd
        int row_a, col_a, row_b, col_b;
        findPosition(matrix, a, &row_a, &col_a);
        findPosition(matrix, b, &row_b, &col_b);
        if (row_a == row_b) {
            ciphertext[index++] = matrix[row_a][(col_a + 1) % 5];
            ciphertext[index++] = matrix[row_b][(col_b + 1) % 5];
        } else if (col_a == col_b) {
            ciphertext[index++] = matrix[(row_a + 1) % 5][col_a];
            ciphertext[index++] = matrix[(row_b + 1) % 5][col_b];
        } else {
            ciphertext[index++] = matrix[row_a][col_b];
            ciphertext[index++] = matrix[row_b][col_a];
        }
    }
    ciphertext[index] = '\0';
}

int main() {
    char message[] = "Must see you over Cadogan West. Coming at once.";
    char matrix[5][5] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    preprocessMessage(message);

    char ciphertext[100];
    encryptPlayfair(message, matrix, ciphertext);

    printf("Original Message: %s\n", message);
    printf("Encrypted Message: %s\n", ciphertext);

    return 0;
}

