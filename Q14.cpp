#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

// Function to encrypt a message using the one-time pad Vigenère cipher
void encryptOneTimePadVigenere(char *plaintext, int *keyStream, char *ciphertext) {
    int len = strlen(plaintext);
    int keyIndex = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            int shift = keyStream[keyIndex++];
            int plaintextIndex = charToInt(toupper(plaintext[i]));
            int encryptedIndex = (plaintextIndex + shift) % 26;
            ciphertext[i] = intToChar(encryptedIndex);
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[len] = '\0';
}

// Function to decrypt a ciphertext using the one-time pad Vigenère cipher with a specific key
void decryptOneTimePadVigenere(char *ciphertext, int *key, char *plaintext) {
    int len = strlen(ciphertext);
    int keyIndex = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            int shift = key[keyIndex++];
            int ciphertextIndex = charToInt(toupper(ciphertext[i]));
            int decryptedIndex = (ciphertextIndex - shift + 26) % 26;
            plaintext[i] = intToChar(decryptedIndex);
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    plaintext[len] = '\0';
}

int main() {
    char plaintext[] = "send more money";
    int keyStream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    char ciphertext[strlen(plaintext) + 1];

    // Encrypt the plaintext using the key stream
    encryptOneTimePadVigenere(plaintext, keyStream, ciphertext);
    printf("Encrypted Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext to find the key
    char recoveredPlaintext[strlen(ciphertext) + 1];
    int key[strlen(ciphertext)];

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < strlen(ciphertext); j++) {
            key[j] = (charToInt(toupper(ciphertext[j])) - i + 26) % 26;
        }
        decryptOneTimePadVigenere(ciphertext, key, recoveredPlaintext);
        if (strcmp(recoveredPlaintext, "cash not needed") == 0) {
            printf("Found Key: ");
            for (int k = 0; k < strlen(ciphertext); k++) {
                printf("%d ", key[k]);
            }
            printf("\n");
            break;
        }
    }

    return 0;
}

