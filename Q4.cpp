#include <stdio.h>
#include <string.h>
#include <ctype.h>

void polyalphabeticCipher(char plaintext[], char keyword[]);

int main() {
    char plaintext[1000];
    char keyword[100];

    printf("Enter the plaintext to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the keyword (letters only, no spaces): ");
    fgets(keyword, sizeof(keyword), stdin);

    polyalphabeticCipher(plaintext, keyword);

    return 0;
}

void polyalphabeticCipher(char plaintext[], char keyword[]) {
    int plaintextLength = strlen(plaintext);
    int keywordLength = strlen(keyword);
    int keywordIndex = 0;

    // Convert the keyword to uppercase
    for (int i = 0; i < keywordLength; i++) {
        if (isalpha(keyword[i])) {
            keyword[i] = toupper(keyword[i]);
        }
    }

    // Encrypt the plaintext using the polyalphabetic substitution cipher
    for (int i = 0; i < plaintextLength; i++) {
        char ch = plaintext[i];

        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            char shift = keyword[keywordIndex] - 'A';

            ch = (ch - base + shift) % 26 + base;
            keywordIndex = (keywordIndex + 1) % keywordLength;
        }

        printf("%c", ch);
    }

    printf("\n");
}

