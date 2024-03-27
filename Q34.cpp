#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

void print_bytes(const char *bytes, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02x", bytes[i]);
    }
    printf("\n");
}

int main() {
    const char *plaintext = "Hello, World!";
    const char *key = "secret";
    const char *iv = "0123456789012345";

    // ECB mode
    AES_KEY ecb_key;
    AES_set_encrypt_key(key, 128, &ecb_key);
    unsigned char ecb_output[16];
    AES_cbc_encrypt(plaintext, ecb_output, strlen(plaintext), &ecb_key, NULL, AES_ENCRYPT);
    printf("ECB mode output: ");
    print_bytes(ecb_output, 16);

    // CBC mode
    AES_KEY cbc_key;
    AES_set_encrypt_key(key, 128, &cbc_key);
    unsigned char cbc_output[16];
    AES_cbc_encrypt(plaintext, cbc_output, strlen(plaintext), &cbc_key, (const unsigned char *)iv, AES_ENCRYPT);
    printf("CBC mode output: ");
    print_bytes(cbc_output, 16);

    // CFB mode
    AES_KEY cfb_key;
    AES_set_encrypt_key(key, 128, &cfb_key);
    unsigned char cfb_output[16];
    AES_cfb_encrypt(plaintext, cfb_output, strlen(plaintext), &cfb_key, (const unsigned char *)iv, AES_ENCRYPT, 1);
    printf("CFB mode output: ");
    print_bytes(cfb_output, 16);

    return 0;
}

