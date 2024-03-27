#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_TEXT_SIZE 1000

// Function to compute the greatest common divisor (GCD)
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to compute the modular inverse of 'a' modulo 'm'
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if (((a % m) * (x % m)) % m == 1)
            return x;
    }
    return -1; // Modular inverse doesn't exist
}

int main() {
    int p, q, n, phi_n, e, d;
    char plaintext[MAX_TEXT_SIZE];
    int ciphertext[MAX_TEXT_SIZE];
    char decrypted[MAX_TEXT_SIZE];

    // Input prime numbers p and q
    printf("Enter prime number p: ");
    scanf("%d", &p);
    printf("Enter prime number q: ");
    scanf("%d", &q);

    // Calculate n and phi(n)
    n = p * q;
    phi_n = (p - 1) * (q - 1);

    // Choose public exponent e (commonly e = 65537)
    e = 65537;

    // Calculate private exponent d using modular inverse
    d = mod_inverse(e, phi_n);

    // Display RSA parameters
    printf("\nRSA Parameters:\n");
    printf("n = %d\n", n);
    printf("phi(n) = %d\n", phi_n);
    printf("Public Key (e) = %d\n", e);
    printf("Private Key (d) = %d\n", d);

    // Input plaintext message
    printf("\nEnter plaintext message (uppercase letters only): ");
    scanf("%s", plaintext);

    int len = strlen(plaintext);

    // Encrypt each character separately
    printf("\nEncrypted ciphertext: ");
    for (int i = 0; i < len; i++) {
        int letter = plaintext[i] - 'A'; // Convert letter to integer (A=0, B=1, ..., Z=25)
        ciphertext[i] = fmod(pow(letter, e), n); // RSA encryption
        printf("%d ", ciphertext[i]);
    }
    printf("\n");

    // Decrypt each ciphertext separately
    printf("\nDecrypted plaintext: ");
    for (int i = 0; i < len; i++) {
        int letter = fmod(pow(ciphertext[i], d), n); // RSA decryption
        decrypted[i] = letter + 'A'; // Convert back to ASCII letter
        printf("%c", decrypted[i]);
    }
    printf("\n");

    return 0;
}

