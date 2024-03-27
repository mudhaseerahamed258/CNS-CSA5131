#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

#define DES_BLOCK_SIZE 8
#define DES3_KEY_SIZE 24

void des3_cbc_encrypt(const unsigned char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext, int size) {
    DES_cblock des_key1, des_key2, des_key3;
    DES_key_schedule key_schedule1, key_schedule2, key_schedule3;

    memcpy(des_key1, key, 8);
    memcpy(des_key2, key + 8, 8);
    memcpy(des_key3, key + 16, 8);

    DES_set_key_unchecked(&des_key1, &key_schedule1);
    DES_set_key_unchecked(&des_key2, &key_schedule2);
    DES_set_key_unchecked(&des_key3, &key_schedule3);

    DES_cblock ivec;
    memcpy(ivec, iv, 8);

    DES_ede3_cbc_encrypt(plaintext, ciphertext, size, &key_schedule1, &key_schedule2, &key_schedule3, &ivec, DES_ENCRYPT);
}

int main() {
    const unsigned char plaintext[] = "This is a plaintext message.";
    const unsigned char key[DES3_KEY_SIZE] = "0123456789ABCDEF01234567"; // 24 bytes for 3DES
    const unsigned char iv[8] = "12345678"; // Initialization Vector (IV)

    int plaintext_size = strlen((char *)plaintext);
    int padded_size = plaintext_size + (DES_BLOCK_SIZE - (plaintext_size % DES_BLOCK_SIZE));

    unsigned char padded_plaintext[padded_size];
    memcpy(padded_plaintext, plaintext, plaintext_size);
    memset(padded_plaintext + plaintext_size, DES_BLOCK_SIZE - (plaintext_size % DES_BLOCK_SIZE), DES_BLOCK_SIZE - (plaintext_size % DES_BLOCK_SIZE));

    unsigned char ciphertext[padded_size];

    des3_cbc_encrypt(padded_plaintext, key, iv, ciphertext, padded_size);

    printf("Plaintext: %s\n", plaintext);
    printf("Encrypted: ");
    for (int i = 0; i < padded_size; i++) {
        printf("%02X", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

