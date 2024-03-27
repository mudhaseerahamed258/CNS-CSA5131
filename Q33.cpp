#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

void des_encrypt(const char *input, const char *key) {
    DES_cblock des_key;
    DES_key_schedule key_schedule;
    DES_set_key((const_DES_cblock *)key, &key_schedule);

    unsigned char output[8];
    DES_ecb_encrypt((const_DES_cblock *)input, (DES_cblock *)output, &key_schedule, DES_ENCRYPT);

    printf("Encrypted text: ");
    for (int i = 0; i < 8; i++) {
        printf("%02x", output[i]);
    }
    printf("\n");
}

void des_decrypt(const char *input, const char *key) {
    DES_cblock des_key;
    DES_key_schedule key_schedule;
    DES_set_key((const_DES_cblock *)key, &key_schedule);

    unsigned char output[8];
    DES_ecb_encrypt((const_DES_cblock *)input, (DES_cblock *)output, &key_schedule, DES_DECRYPT);

    printf("Decrypted text: ");
    for (int i = 0; i < 8; i++) {
        printf("%c", output[i]);
    }
    printf("\n");
}

int main() {
    const char *plain_text = "12345678";
    const char *key = "secret";

    des_encrypt(plain_text, key);
    
    const char *cipher_text = "\x85\xe7\x3f\x1a\x4d\x6e\x9a\x97"; // Example ciphertext
    des_decrypt(cipher_text, key);

    return 0;
}
