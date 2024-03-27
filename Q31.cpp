#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8 // 64 bits block size in bytes

// Constants for CMAC subkey generation (for 64-bit blocks)
#define CONST64 0x1B // Predefined constant for XOR operation

// Perform block cipher encryption (dummy function for demonstration)
void blockCipherEncrypt(const uint8_t *block, uint8_t *output) {
    // This is a dummy function, replace it with actual block cipher encryption
    memcpy(output, block, BLOCK_SIZE);
}

// Generate the CMAC subkeys
void generateCMACSubkeys(const uint8_t *key, uint8_t *subkey1, uint8_t *subkey2) {
    uint8_t zerosBlock[BLOCK_SIZE] = {0};
    uint8_t blockCipherOutput[BLOCK_SIZE];

    // Generate first subkey by encrypting zeros block
    blockCipherEncrypt(zerosBlock, blockCipherOutput);
    memcpy(subkey1, blockCipherOutput, BLOCK_SIZE);

    // Check MSB of first subkey for carry
    uint8_t carry = (subkey1[0] & 0x80) ? 1 : 0;

    // Left shift first subkey and apply XOR with constant if needed
    for (int i = 0; i < BLOCK_SIZE; i++) {
        uint8_t temp = subkey1[i];
        subkey1[i] <<= 1;
        if (i < BLOCK_SIZE - 1 && (temp & 0x80)) {
            subkey1[i + 1] |= 1;
        }
    }
    if (carry) {
        subkey1[BLOCK_SIZE - 1] ^= CONST64;
    }

    // Generate second subkey by repeating process with first subkey
    memcpy(subkey2, subkey1, BLOCK_SIZE);
    carry = (subkey1[0] & 0x80) ? 1 : 0;
    for (int i = 0; i < BLOCK_SIZE; i++) {
        uint8_t temp = subkey2[i];
        subkey2[i] <<= 1;
        if (i < BLOCK_SIZE - 1 && (temp & 0x80)) {
            subkey2[i + 1] |= 1;
        }
    }
    if (carry) {
        subkey2[BLOCK_SIZE - 1] ^= CONST64;
    }
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF}; // Example key
    uint8_t subkey1[BLOCK_SIZE];
    uint8_t subkey2[BLOCK_SIZE];

    // Generate CMAC subkeys
    generateCMACSubkeys(key, subkey1, subkey2);

    // Print the subkeys
    printf("First CMAC subkey: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", subkey1[i]);
    }
    printf("\n");

    printf("Second CMAC subkey: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", subkey2[i]);
    }
    printf("\n");

    return 0;
}

