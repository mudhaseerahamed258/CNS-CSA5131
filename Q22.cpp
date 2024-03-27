#include <stdio.h>
#include <string.h>

// Expansion permutation E/P
void expand(char *input, char *output) {
    int EP[] = {4, 1, 2, 3, 2, 3, 4, 1};
    for (int i = 0; i < 8; i++) {
        output[i] = input[EP[i] - 1];
    }
}

// S-box substitution
void substitution(char *input, char *output) {
    int S0[4][4] = {{1, 0, 3, 2},
                    {3, 2, 1, 0},
                    {0, 2, 1, 3},
                    {3, 1, 3, 2}};

    int S1[4][4] = {{0, 1, 2, 3},
                    {2, 0, 1, 3},
                    {3, 0, 1, 0},
                    {2, 1, 0, 3}};

    int row, col, val;

    // S0 box substitution
    row = (input[0] - '0') * 2 + (input[3] - '0');
    col = (input[1] - '0') * 2 + (input[2] - '0');
    val = S0[row][col];
    output[0] = ((val >> 1) & 1) + '0';
    output[1] = (val & 1) + '0';

    // S1 box substitution
    row = (input[4] - '0') * 2 + (input[7] - '0');
    col = (input[5] - '0') * 2 + (input[6] - '0');
    val = S1[row][col];
    output[2] = ((val >> 1) & 1) + '0';
    output[3] = (val & 1) + '0';
}

// Permutation P4
void permuteP4(char *input, char *output) {
    int P4[] = {2, 4, 3, 1};
    for (int i = 0; i < 4; i++) {
        output[i] = input[P4[i] - 1];
    }
}

// S-DES encryption
void sdesEncrypt(char *plaintextBlock, char *key, char *ciphertextBlock) {
    char expanded[9]; // Adjusted size to include null terminator
    expand(plaintextBlock, expanded);

    char xorResult[9]; // Adjusted size to include null terminator
    for (int i = 0; i < 8; i++) {
        xorResult[i] = (expanded[i] - '0') ^ (key[i] - '0') + '0';
    }
    xorResult[8] = '\0'; // Null terminator

    char substituted[5]; // Adjusted size to include null terminator
    substitution(xorResult, substituted);

    char permuted[5]; // Adjusted size to include null terminator
    permuteP4(substituted, permuted);

    memcpy(ciphertextBlock, permuted, 4);
    ciphertextBlock[4] = '\0'; // Null terminator
}

// Key generation and S-DES encryption
void sdesEncryptWithKey(char *plaintext, char *key, char *ciphertext) {
    char temp[9], xorResult[9];
    memcpy(temp, "00000000", 8); // Initial temp value

    int numBlocks = strlen(plaintext) / 4;
    for (int i = 0; i < numBlocks; i++) {
        char plaintextBlock[5]; // Adjusted size to include null terminator
        memcpy(plaintextBlock, plaintext + i * 4, 4);
        plaintextBlock[4] = '\0'; // Null terminator

        // Encrypt plaintext block
        sdesEncrypt(plaintextBlock, key, xorResult);
        memcpy(ciphertext + i * 4, xorResult, 4); // Store encrypted block in ciphertext
    }
}

int main() {
    char plaintext[33] = "000000010010001100000100"; // Binary plaintext: 0000 0001 0010 0011 0000 0100
    char key[10] = "101000001"; // Binary key: 1010 00001
    char ciphertext[33];

    // Encrypt plaintext using S-DES
    sdesEncryptWithKey(plaintext, key, ciphertext);
    printf("Encrypted ciphertext: %s\n", ciphertext);

    return 0;
}

