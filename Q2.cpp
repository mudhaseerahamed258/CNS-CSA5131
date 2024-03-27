#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encryptMonoalphabetic(char message[], char key[]);
void generateKey(char key[], const char originalKey[]);

int main() {
    char message[100];
    char key[26];

    printf("Enter a message to encrypt: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter the encryption key (26 letters without spaces, case-insensitive): ");
    fgets(key, sizeof(key), stdin);

    // Encrypt the key and generate the modified key
    generateKey(key, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    encryptMonoalphabetic(message, key);

    return 0;
}

void encryptMonoalphabetic(char message[], char key[]) {
    int i;
    int length = strlen(message);

    // Remove newline characters from the input strings
    message[strcspn(message, "\n")] = '\0';

    // Encrypt the message using the modified key
    for (i = 0; i < length; i++) {
        char ch = message[i];
        if (isalpha(ch)) {
            if (isupper(ch)) {
                message[i] = key[ch - 'A'];
            } else {
                message[i] = tolower(key[toupper(ch) - 'A']);
            }
        }
    }

    printf("Ciphered String: %s\n", message);
}

void generateKey(char key[], const char originalKey[]) {
    int i, j;
    int keyLength = strlen(key);

    // Convert the key to uppercase
    for (i = 0; i < keyLength; i++) {
        key[i] = toupper(key[i]);
    }

    // Fill remaining alphabetical letters in the key
    j = 0;
    for (i = 0; i < 26; i++) {
        if (!isalpha(key[i])) {
            while (isalpha(originalKey[j]) && strchr(key, originalKey[j])) {
                j++;
            }
            key[i] = originalKey[j++];
        }
    }
}

