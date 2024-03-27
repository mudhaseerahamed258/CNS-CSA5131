#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to remove spaces and convert to uppercase
void preprocessMessage(char *message) {
    int len = strlen(message);
    int index = 0;
    for (int i = 0; i < len; i++) {
        if (message[i] != ' ') {
            message[index++] = toupper(message[i]);
        }
    }
    message[index] = '\0';
}

// Function to decrypt the Playfair cipher
void decryptPlayfair(char *message, char (*matrix)[5], char *plaintext) {
    int len = strlen(message);
    int index = 0;
    int row_a = 0, col_a = 0, row_b = 0, col_b = 0; // Initialize variables
    for (int i = 0; i < len; i += 2) {
        char a = message[i];
        char b = message[i + 1];
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                if (matrix[row][col] == a) {
                    row_a = row;
                    col_a = col;
                }
                if (matrix[row][col] == b) {
                    row_b = row;
                    col_b = col;
                }
            }
        }
        if (row_a == row_b) {
            plaintext[index++] = matrix[row_a][(col_a - 1 + 5) % 5];
            plaintext[index++] = matrix[row_b][(col_b - 1 + 5) % 5];
        } else if (col_a == col_b) {
            plaintext[index++] = matrix[(row_a - 1 + 5) % 5][col_a];
            plaintext[index++] = matrix[(row_b - 1 + 5) % 5][col_b];
        } else {
            plaintext[index++] = matrix[row_a][col_b];
            plaintext[index++] = matrix[row_b][col_a];
        }
    }
    plaintext[index] = '\0';
}

int main() {
    char message[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ";
    char matrix[5][5] = {
        {'P', 'L', 'A', 'Y', 'F'},
        {'I', 'R', 'E', 'X', 'M'},
        {'B', 'C', 'D', 'G', 'H'},
        {'K', 'N', 'O', 'Q', 'S'},
        {'T', 'U', 'V', 'W', 'Z'}
    };
    preprocessMessage(message);

    char plaintext[100];
    decryptPlayfair(message, matrix, plaintext);

    printf("Decrypted Message: %s\n", plaintext);

    return 0;
}

