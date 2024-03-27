#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateCipherAlphabet(char keyword[], char cipherAlphabet[]);
void monoalphabeticEncrypt(char plaintext[], char cipherAlphabet[]);
void monoalphabeticDecrypt(char ciphertext[], char cipherAlphabet[]);

int main() {
    char keyword[100];
    char cipherAlphabet[26];
    char plaintext[1000];
    char ciphertext[1000];

    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);

    // Generate the cipher alphabet based on the keyword
    generateCipherAlphabet(keyword, cipherAlphabet);

    printf("Enter the plaintext to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    monoalphabeticEncrypt(plaintext, cipherAlphabet);

    printf("Encrypted ciphertext: %s\n", plaintext);

    printf("Enter the ciphertext to decrypt: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    monoalphabeticDecrypt(ciphertext, cipherAlphabet);

    printf("Decrypted plaintext: %s\n", ciphertext);

    return 0;
}

// Function to generate the cipher alphabet based on the keyword
void generateCipherAlphabet(char keyword[], char cipherAlphabet[]) {
    int keywordLength = strlen(keyword);
    int index = 0;

    // Fill the cipher alphabet with uppercase letters not present in the keyword
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        int found = 0;

        for (int i = 0; i < keywordLength; i++) {
            if (toupper(keyword[i]) == ch) {
                found = 1;
                break;
            }
        }

        if (!found) {
            cipherAlphabet[index++] = ch;
        }
    }

    // Append the keyword letters to the cipher alphabet
    for (int i = 0; i < keywordLength; i++) {
        char ch = toupper(keyword[i]);
        if (isalpha(ch)) {
            cipherAlphabet[index++] = ch;
        }
    }

    cipherAlphabet[26] = '\0'; // Null-terminate the cipher alphabet
}

// Function to encrypt plaintext using the monoalphabetic cipher
void monoalphabeticEncrypt(char plaintext[], char cipherAlphabet[]) {
    int length = strlen(plaintext);

    for (int i = 0; i < length; i++) {
        char ch = plaintext[i];

        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            int index = ch - base;

            plaintext[i] = cipherAlphabet[index];
        }
    }
}

// Function to decrypt ciphertext using the monoalphabetic cipher
void monoalphabeticDecrypt(char ciphertext[], char cipherAlphabet[]) {
    int length = strlen(ciphertext);

    for (int i = 0; i < length; i++) {
        char ch = ciphertext[i];

        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            int index = 0;

            while (cipherAlphabet[index] != ch) {
                index++;
            }

            ciphertext[i] = base + index;
        }
    }
}

