#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Structure to store letter frequencies
typedef struct {
    char letter;
    int frequency;
} Frequency;

// Function to count letter frequencies in a string
void countLetterFrequency(const char *text, Frequency *frequencies) {
    for (int i = 0; i < strlen(text); i++) {
        char c = text[i];
        if (isalpha(c)) {
            c = tolower(c);
            frequencies[c - 'a'].frequency++;
        }
    }
}

// Function to compare frequencies for sorting
int compareFrequencies(const void *a, const void *b) {
    const Frequency *fa = (const Frequency *)a;
    const Frequency *fb = (const Frequency *)b;
    return fb->frequency - fa->frequency;
}

// Function to decrypt the text using a given key
void decryptText(const char *cipherText, const char *key) {
    char decryptedText[strlen(cipherText) + 1];
    for (int i = 0; i < strlen(cipherText); i++) {
        if (isalpha(cipherText[i])) {
            char c = tolower(cipherText[i]);
            int index = key[c - 'a'] - 'a';
            decryptedText[i] = islower(cipherText[i]) ? 'a' + index : 'A' + index;
        } else {
            decryptedText[i] = cipherText[i];
        }
    }
    decryptedText[strlen(cipherText)] = '\0';
    printf("Decrypted Text: %s\n", decryptedText);
}

int main() {
    char cipherText[1000];
    printf("Enter the ciphertext: ");
    fgets(cipherText, sizeof(cipherText), stdin);

    Frequency frequencies[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i].letter = 'a' + i;
        frequencies[i].frequency = 0;
    }

    countLetterFrequency(cipherText, frequencies);

    // Sort frequencies in descending order
    qsort(frequencies, ALPHABET_SIZE, sizeof(Frequency), compareFrequencies);

    // Assuming 'e' is the most frequent letter in English
    char key[ALPHABET_SIZE + 1];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        key[frequencies[i].letter - 'a'] = 'e' - ('a' - i);
    }
    key[ALPHABET_SIZE] = '\0';

    printf("Key: %s\n", key);

    // Decrypt using the derived key
    decryptText(cipherText, key);

    return 0;
}

