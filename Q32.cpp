#include <stdio.h>
#include <openssl/dsa.h>
#include <openssl/sha.h>

#define MESSAGE "Hello, World!"
#define MESSAGE_LEN 13

int main() {
    // Initialize OpenSSL's PRNG
    RAND_poll();

    // Generate DSA key pair
    DSA *dsa = DSA_new();
    if (dsa == NULL) {
        printf("Error creating DSA key pair.\n");
        return 1;
    }

    DSA_generate_parameters_ex(dsa, 1024, NULL, 0, NULL, NULL, NULL);
    DSA_generate_key(dsa);

    // Prepare the message to be signed
    const unsigned char *message = (const unsigned char *)MESSAGE;
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(message, MESSAGE_LEN, hash);

    // Sign the message
    DSA_SIG *signature = DSA_do_sign(hash, SHA_DIGEST_LENGTH, dsa);
    if (signature == NULL) {
        printf("Error signing the message.\n");
        DSA_free(dsa);
        return 1;
    }

    // Verify the signature (should return 1 for successful verification)
    int verified = DSA_do_verify(hash, SHA_DIGEST_LENGTH, signature, dsa);
    printf("Signature verification result: %d\n", verified);

    // Free resources
    DSA_free(dsa);
    DSA_SIG_free(signature);

    return 0;
}

