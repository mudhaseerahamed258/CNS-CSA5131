#include <stdio.h>
#include <string.h>

int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1;
}

void encrypt_affine_caesar(const char *plaintext, int a, int b, char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((a * (plaintext[i] - 'a') + b) % 26) + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len] = '\0';
}

void decrypt_affine_caesar(const char *ciphertext, int a, int b, char *decrypted) {
    int a_inv = mod_inverse(a, 26);
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            decrypted[i] = (a_inv * (ciphertext[i] - 'a' - b + 26) % 26) + 'a';
        } else {
            decrypted[i] = ciphertext[i];
        }
    }
    decrypted[len] = '\0';
}

int main() {
    const char *plaintext = "hello";
    int a = 5; // Example values for a and b
    int b = 8;

    char ciphertext[6];
    encrypt_affine_caesar(plaintext, a, b, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    char decrypted[6];
    decrypt_affine_caesar(ciphertext, a, b, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}

