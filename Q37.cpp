#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void decrypt_monoalphabetic(const char *ciphertext, const char *key, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            if (isupper(ciphertext[i])) {
                plaintext[i] = toupper(key[ciphertext[i] - 'A']);
            } else {
                plaintext[i] = tolower(key[ciphertext[i] - 'a']);
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0';
}

void calculate_frequency(const char *text, int *frequency) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            int index = tolower(text[i]) - 'a';
            frequency[index]++;
        }
    }
}

int main() {
    const char *ciphertext = "Khoor, Zruog!";
    char key[ALPHABET_SIZE + 1] = "abcdefghijklmnopqrstuvwxyz"; // Initial key assumption
    char plaintext[100];

    int frequency[ALPHABET_SIZE] = {0};
    calculate_frequency(ciphertext, frequency);

    // Sort the frequency array to determine the most common letters
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (frequency[i] < frequency[j]) {
                int temp = frequency[i];
                frequency[i] = frequency[j];
                frequency[j] = temp;

                char temp_char = key[i];
                key[i] = key[j];
                key[j] = temp_char;
            }
        }
    }

    decrypt_monoalphabetic(ciphertext, key, plaintext);
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}

