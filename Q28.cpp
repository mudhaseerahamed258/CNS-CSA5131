#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compute modular exponentiation: (base^exponent) mod modulus
int mod_exp(int base, int exponent, int modulus) {
    int result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

int main() {
    int q, a, xa, xb;
    int Ya, Yb, Ka, Kb;

    // Input public numbers q and a
    printf("Enter a prime number q: ");
    scanf("%d", &q);
    printf("Enter a primitive root modulo q (a): ");
    scanf("%d", &a);

    // Input secret numbers xa and xb
    printf("\nEnter Alice's secret number (xa): ");
    scanf("%d", &xa);
    printf("Enter Bob's secret number (xb): ");
    scanf("%d", &xb);

    // Calculate public keys Ya and Yb
    Ya = mod_exp(a, xa, q);
    Yb = mod_exp(a, xb, q);

    // Exchange public keys and calculate shared secret keys Ka and Kb
    Ka = mod_exp(Yb, xa, q);
    Kb = mod_exp(Ya, xb, q);

    printf("\nPublic Key for Alice (Ya): %d\n", Ya);
    printf("Public Key for Bob (Yb): %d\n", Yb);
    printf("Shared Secret Key for Alice (Ka): %d\n", Ka);
    printf("Shared Secret Key for Bob (Kb): %d\n", Kb);

    return 0;
}

