#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// English letter frequency table (source: https://en.wikipedia.org/wiki/Letter_frequency)
const double ENGLISH_FREQ[] = {
    0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, // A-G
    0.0609, 0.0697, 0.0015, 0.0077, 0.0403, 0.0241, 0.0675, // H-N
    0.0751, 0.0193, 0.0009, 0.0599, 0.0633, 0.0906, 0.0276, // O-U
    0.0098, 0.0236, 0.0015, 0.0197, 0.0007 // V-Z
};

#define ALPHABET_SIZE 26
#define MAX_PLAINTEXTS 10

// Function to calculate the index of coincidence (IoC) for a given text
double indexOfCoincidence(const char *text) {
    int freq[ALPHABET_SIZE] = {0};
    int totalChars = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            freq[toupper(text[i]) - 'A']++;
            totalChars++;
        }
    }

    double ioc = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        ioc += (freq[i] * (freq[i] - 1.0)) / (totalChars * (totalChars - 1.0));
    }

    return ioc;
}

// Function to decrypt a message using a given shift
void decryptMessage(const char *ciphertext, int shift, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int decryptedChar = ((ciphertext[i] - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
            plaintext[i] = decryptedChar;
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    plaintext[len] = '\0';
}

// Function to sort possible plaintexts by their index of coincidence values
void sortPlaintextsByIoC(double iocValues[], char *plaintexts[], int numPlaintexts) {
    for (int i = 0; i < numPlaintexts - 1; i++) {
        for (int j = i + 1; j < numPlaintexts; j++) {
            if (iocValues[i] < iocValues[j]) {
                // Swap IoC values
                double tempIoc = iocValues[i];
                iocValues[i] = iocValues[j];
                iocValues[j] = tempIoc;
                // Swap plaintexts
                char *tempPlaintext = plaintexts[i];
                plaintexts[i] = plaintexts[j];
                plaintexts[j] = tempPlaintext;
            }
        }
    }
}

// Function to perform a letter frequency attack on an additive cipher
void letterFrequencyAttack(const char *ciphertext, int maxShifts, int topPlaintexts) {
    double iocValues[maxShifts];
    char *plaintexts[maxShifts];

    for (int shift = 1; shift <= maxShifts; shift++) {
        char plaintext[strlen(ciphertext) + 1];
        decryptMessage(ciphertext, shift, plaintext);
        iocValues[shift - 1] = indexOfCoincidence(plaintext);
        plaintexts[shift - 1] = strdup(plaintext);
    }

    sortPlaintextsByIoC(iocValues, plaintexts, maxShifts);

    printf("Top %d Possible Plaintexts:\n", topPlaintexts);
    for (int i = 0; i < topPlaintexts; i++) {
        printf("%d. IoC: %.4f, Plaintext: %s\n", i + 1, iocValues[i], plaintexts[i]);
        free(plaintexts[i]);
    }
}

int main() {
    char ciphertext[] = "LXFOPVEFRNHR"; // Example ciphertext
    int maxShifts = ALPHABET_SIZE; // Maximum possible shifts for the additive cipher
    int topPlaintexts = MAX_PLAINTEXTS; // Top N possible plaintexts to display

    letterFrequencyAttack(ciphertext, maxShifts, topPlaintexts);

    return 0;
}

