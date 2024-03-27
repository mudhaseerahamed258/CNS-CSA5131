#include <stdio.h>
#include <string.h>

void encrypt_vigenere(const char *plaintext, const int *key, char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        ciphertext[i] = (plaintext[i] - 'a' + key[i]) % 26 + 'a';
    }
    ciphertext[len] = '\0';
}

void decrypt_vigenere(const char *ciphertext, const int *key, char *decrypted) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        decrypted[i] = (ciphertext[i] - 'a' - key[i] + 26) % 26 + 'a';
    }
    decrypted[len] = '\0';
}

int main() {
    const char *plaintext = "hello";
    const int key[] = {3, 19, 5, 10, 7}; // Example key

    char ciphertext[6];
    encrypt_vigenere(plaintext, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    char decrypted[6];
    decrypt_vigenere(ciphertext, key, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}

