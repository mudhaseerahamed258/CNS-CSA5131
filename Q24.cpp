#include <stdio.h>

// Function to calculate the greatest common divisor (GCD) using Euclidean algorithm
int gcd(int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

// Function to calculate the multiplicative inverse using extended Euclidean algorithm
int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    // Apply extended Euclidean algorithm
    while (a > 1) {
        // q is quotient
        q = a / m;

        t = m;
        // m is remainder now, process same as Euclid's algorithm
        m = a % m, a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}

int main() {
    int e = 31; // Public exponent
    int n = 3599; // Modulus
    int phi_n = 3438; // Euler's totient function phi(n)

    int d = modInverse(e, phi_n); // Calculate private key using extended Euclidean algorithm

    printf("Private key (d): %d\n", d);

    return 0;
}

