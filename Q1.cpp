#include <stdio.h>
#include <string.h>

void caesarCipher(char message[], int shift);

int main() {
    char message[100];
    int shift;

    printf("Enter a message to encrypt: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter the shift value (k): ");
    scanf("%d", &shift);

    caesarCipher(message, shift);

    return 0;
}

void caesarCipher(char message[], int shift) {
    int length = strlen(message);

    // Iterate through each character in the message
    for (int i = 0; i < length; i++) {
        char ch = message[i];

        // Encrypt uppercase letters
        if (ch >= 'A' && ch <= 'Z') {
            ch = 'A' + (ch - 'A' + shift) % 26;
        }
        // Encrypt lowercase letters
        else if (ch >= 'a' && ch <= 'z') {
            ch = 'a' + (ch - 'a' + shift) % 26;
        }

        // Print the encrypted character
        printf("%c", ch);
    }

    printf("\n");
}

