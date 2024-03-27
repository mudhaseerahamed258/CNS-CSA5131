#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define ALPHABET_SIZE 26
#define MAX_PLAINTEXTS 10

// English letter frequency table (source: https://en.wikipedia.org/wiki/Letter_frequency)
const double ENGLISH_FREQ[] = {
    0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, // A-G
    0.0609, 0.0697, 0.0015, 0.0077, 0.0403, 0.0241, 0.0675, // H-N
    0.0751, 0.0193, 0.0009, 0.0599, 0.0633, 0.0906, 0.0276, // O-U
    0.0098, 0.0236, 0.0015, 0.0197, 0.0007 // V-Z
};

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

// Function to decrypt a message using a given key
void decryptMessage(const char *ciphertext, const char *key, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int decryptedChar = key[toupper(ciphertext[i]) - 'A'];
            plaintext[i] = isupper(ciphertext[i]) ? toupper(decryptedChar) : tolower(decryptedChar);
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    plaintext[len] = '\0';
}

// Function to calculate the frequency difference between observed and expected frequencies
double freqDifference(const int observedFreq[], const double expectedFreq[]) {
    double diff = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        diff += fabs(observedFreq[i] - (int)(expectedFreq[i] * 1000)); // Scale expected frequencies
    }
    return diff;
}

// Function to generate permutations of a given key
void generatePermutations(char *key, int start, int end, void (*callback)(const char *)) {
    if (start == end) {
        callback(key);
    } else {
        for (int i = start; i <= end; i++) {
            // Swap characters at indices start and i
            char temp = key[start];
            key[start] = key[i];
            key[i] = temp;

            generatePermutations(key, start + 1, end, callback);

            // Undo the swap for backtracking
            temp = key[start];
            key[start] = key[i];
            key[i] = temp;
        }
    }
}

// Function to perform a letter frequency attack on a monoalphabetic substitution cipher
void letterFrequencyAttack(const char *ciphertext, int topPlaintexts) {
    int observedFreq[ALPHABET_SIZE] = {0}; // Initialize observed frequencies to zero

    // Calculate observed letter frequencies in the ciphertext
    int totalChars = 0;
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            observedFreq[toupper(ciphertext[i]) - 'A']++;
            totalChars++;
        }
    }

    char *plaintexts[MAX_PLAINTEXTS];
    double freqDiffs[MAX_PLAINTEXTS];

    for (int i = 0; i < topPlaintexts; i++) {
        plaintexts[i] = strdup(ciphertext);
        freqDiffs[i] = INFINITY; // Initialize frequency differences to infinity
    }

    // Generate all possible keys (permutations of the alphabet)
    char key[ALPHABET_SIZE + 1];
    key[ALPHABET_SIZE] = '\0';
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        key[i] = 'A' + i;
    }

    // Callback function to process each permutation
    void permutationCallback(const char *permutedKey) {
        char plaintext[strlen(ciphertext) + 1];
        decryptMessage(ciphertext, permutedKey, plaintext);

        double diff = freqDifference(observedFreq, ENGLISH_FREQ);
        // Update top plaintexts if the new plaintext has a smaller frequency difference
        for (int i = 0; i < topPlaintexts; i++) {
            if (diff < freqDiffs[i]) {
                free(plaintexts[i]);
                plaintexts[i] = strdup(plaintext);
                freqDiffs[i] = diff;
                break;
            }
        }
    }

    // Generate permutations and process them using the callback
    generatePermutations(key, 0, ALPHABET_SIZE - 1, permutationCallback);

    // Sort plaintexts by frequency differences
    for (int i = 0; i < topPlaintexts - 1; i++) {
        for (int j = i + 1; j < topPlaintexts; j++) {
            if (freqDiffs[i] > freqDiffs[j]) {
                double tempDiff = freqDiffs[i];
                freqDiffs[i] = freqDiffs[j];
                freqDiffs[j] = tempDiff;

                char *tempPlaintext = plaintexts[i];
                plaintexts[i] = plaintexts[j];
                plaintexts[j] = tempPlaintext;
            }
        }
    }

    printf("Top %d Possible Plaintexts (Likelihood):\n", topPlaintexts);
    for (int i = 0; i < topPlaintexts; i++) {
        printf("%d. Freq Diff: %.2f, Plaintext: %s\n", i + 1, freqDiffs[i], plaintexts[i]);
        free(plaintexts[i]);
    }
}

int main() {
    char ciphertext[] = "GWC WCWGX LWZ LZXEE CEEWL KALZX";
    int topPlaintexts = MAX_PLAINTEXTS; // Top N possible plaintexts to display

    letterFrequencyAttack(ciphertext, topPlaintexts);

    return 0;
}

