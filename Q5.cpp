#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b);
int modInverse(int a, int m);
void affineCipherEncrypt(char plaintext[], int a, int b);
void affineCipherDecrypt(char ciphertext[], int a, int b);

int main() {
    char plaintext[1000];
    char ciphertext[1000];
    int a, b;

    printf("Enter the plaintext to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the value of a for the affine cipher (must be coprime with 26): ");
    scanf("%d", &a);

    // Check if 'a' is coprime with 26
    if (gcd(a, 26) != 1) {
        printf("Error: 'a' must be coprime with 26.\n");
        return 1; // Exit with error code
    }

    printf("Enter the value of b for the affine cipher (0 <= b < 26): ");
    scanf("%d", &b);

    // Check if 'b' is within the valid range
    if (b < 0 || b >= 26) {
        printf("Error: 'b' must be between 0 and 25.\n");
        return 1; // Exit with error code
    }

    affineCipherEncrypt(plaintext, a, b);

    printf("Enter the ciphertext to decrypt: ");
    getchar(); // Consume newline character
    fgets(ciphertext, sizeof(ciphertext), stdin);

    affineCipherDecrypt(ciphertext, a, b);

    return 0;
}

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// Function to calculate the modular inverse of 'a' modulo 'm'
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No modular inverse exists
}

// Function to encrypt plaintext using the affine cipher
void affineCipherEncrypt(char plaintext[], int a, int b) {
    int length = strlen(plaintext);

    for (int i = 0; i < length; i++) {
        char ch = plaintext[i];

        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            int index = ch - base;

            int encryptedIndex = (a * index + b) % 26;
            char encryptedChar = base + encryptedIndex;

            plaintext[i] = encryptedChar;
        }
    }

    printf("Encrypted ciphertext: %s\n", plaintext);
}

// Function to decrypt ciphertext using the affine cipher
void affineCipherDecrypt(char ciphertext[], int a, int b) {
    int aInverse = modInverse(a, 26);

    if (aInverse == -1) {
        printf("Error: Modular inverse of 'a' does not exist.\n");
        return;
    }

    int length = strlen(ciphertext);

    for (int i = 0; i < length; i++) {
        char ch = ciphertext[i];

        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            int index = ch - base;

            int decryptedIndex = (aInverse * (index - b + 26)) % 26;
            char decryptedChar = base + decryptedIndex;

            ciphertext[i] = decryptedChar;
        }
    }

    printf("Decrypted plaintext: %s\n", ciphertext);
}

