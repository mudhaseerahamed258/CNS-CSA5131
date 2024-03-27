#include <stdio.h>
#include <string.h>
#include <ctype.h>

void decryptSimpleSubstitution(char ciphertext[]);

int main() {
    char ciphertext[1000];

    printf("Enter the ciphertext to decrypt: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    decryptSimpleSubstitution(ciphertext);

    return 0;
}

// Function to decrypt ciphertext using simple substitution algorithm based on frequency analysis
void decryptSimpleSubstitution(char ciphertext[]) {
    // Define the frequency of characters in English text
    // Based on https://en.wikipedia.org/wiki/Letter_frequency
    char frequency[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        char ch = ciphertext[i];

        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            int index = ch - base;

            // Decrypt the character using frequency analysis
            if (isupper(ch)) {
                ciphertext[i] = frequency[index] - 'A' + 'A';
            } else {
                ciphertext[i] = frequency[index] - 'A' + 'a';
            }
        }
    }

    printf("Decrypted plaintext: %s\n", ciphertext);
}

