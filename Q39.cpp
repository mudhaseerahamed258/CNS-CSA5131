#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void decrypt_additive_cipher(const char *ciphertext, int shift, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
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
    char plaintext[100];
    int shift = 3; // Example shift value

    int frequency[ALPHABET_SIZE] = {0};
    calculate_frequency(ciphertext, frequency);

    // Sort the frequency array to determine the most common letters
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (frequency[i] < frequency[j]) {
                int temp = frequency[i];
                frequency[i] = frequency[j];
                frequency[j] = temp;

                char temp_char = 'a' + i;
                'a' + i;
                'a' + i = 'a' + j;
                'a' + j = temp_char;
            }
        }
    }

    decrypt_additive_cipher(ciphertext, shift, plaintext);
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}

