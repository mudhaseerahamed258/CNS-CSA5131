#include <stdio.h>
#include <string.h>
#include <ctype.h>

void affineCipherDecrypt(char ciphertext[], int a, int b);
int gcd(int a, int b);
int modInverse(int a, int m);

int main() {
    char ciphertext[1000];
    int a, b;

    printf("Enter the ciphertext generated with an affine cipher: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    // Assume 'B' corresponds to 'E' and 'U' corresponds to 'T'
    // Calculate 'a' and 'b' based on these assumptions
    int eIndex = 'E' - 'A';
    int tIndex = 'T' - 'A';
    int bIndex = 'B' - 'A';
    int uIndex = 'U' - 'A';

    // Solve for 'a' using the equation: (a * eIndex + b) % 26 = bIndex
    for (a = 1; a < 26; a++) {
        if ((a * eIndex + b) % 26 == bIndex) {
            break;
        }
    }

    // Solve for 'b' using the equation: (a * tIndex + b) % 26 = uIndex
    for (b = 0; b < 26; b++) {
        if ((a * tIndex + b) % 26 == uIndex) {
            break;
        }
    }

    affineCipherDecrypt(ciphertext, a, b);

    return 0;
}

// Function to decrypt ciphertext using the affine cipher
void affineCipherDecrypt(char ciphertext[], int a, int b) {
    int aInverse = modInverse(a, 26);

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

