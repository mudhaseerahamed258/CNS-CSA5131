#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 2

// Function to convert a character to its corresponding integer value (A=0, B=1, ..., Z=25)
int charToInt(char ch) {
    if (isalpha(ch)) {
        return toupper(ch) - 'A';
    } else {
        return -1; // Not a valid uppercase alphabet character
    }
}

// Function to convert an integer value to its corresponding character (0=A, 1=B, ..., 25=Z)
char intToChar(int num) {
    return num + 'A';
}

// Function to encrypt a message using the Hill cipher
void encryptHill(char *message, int key[][SIZE]) {
    int len = strlen(message);
    // Pad the message if its length is not a multiple of SIZE
    int padding = (SIZE - (len % SIZE)) % SIZE;
    len += padding;
    char paddedMessage[len + 1];
    strcpy(paddedMessage, message);
    for (int i = 0; i < padding; i++) {
        paddedMessage[len - padding + i] = 'X'; // Pad with 'X'
    }
    paddedMessage[len] = '\0';

    // Convert the padded message to uppercase and then to corresponding integer values
    int messageMatrix[SIZE][len / SIZE];
    for (int i = 0; i < len; i++) {
        int row = i / SIZE;
        int col = i % SIZE;
        messageMatrix[col][row] = charToInt(toupper(paddedMessage[i]));
    }

    // Encrypt the message matrix using the key matrix
    int encryptedMatrix[SIZE][len / SIZE];
    for (int i = 0; i < len / SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            encryptedMatrix[j][i] = 0;
            for (int k = 0; k < SIZE; k++) {
                encryptedMatrix[j][i] += key[j][k] * messageMatrix[k][i];
            }
            encryptedMatrix[j][i] %= 26; // Apply modulo 26 for each element
        }
    }

    // Print the encrypted message
    printf("Encrypted Message: ");
    for (int i = 0; i < len / SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c", intToChar(encryptedMatrix[j][i]));
        }
    }
    printf("\n");
}

int main() {
    char message[] = "meet me at the usual place at ten rather than eight oclock";

    int key[SIZE][SIZE] = {{9, 4}, {5, 7}};

    encryptHill(message, key);

    return 0;
}

