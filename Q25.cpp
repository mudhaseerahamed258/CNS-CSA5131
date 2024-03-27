#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    int p, q, n, phi_n, e, d, plaintext, ciphertext, decrypted;

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
    printf("\nEnter plaintext (integer): ");
    scanf("%d", &plaintext);

    // Encryption: C = M^e mod n
    ciphertext = fmod(pow(plaintext, e), n);
    printf("\nEncrypted ciphertext (C) = %d\n", ciphertext);

    // Decryption: M' = C^d mod n
    decrypted = fmod(pow(ciphertext, d), n);
    printf("\nDecrypted plaintext (M') = %d\n", decrypted);

    return 0;
}

