#include <iostream>
#include <cstring>

#define BLOCK_SIZE 9 // Increased size to accommodate the string and null terminator

// Function to perform CBC-MAC calculation
void cbcMac(const char *key, const char *message, char *mac) {
    // Initialize the MAC with all zeros
    char temp[BLOCK_SIZE] = {0};
    char xorResult[BLOCK_SIZE];

    // XOR operation on the message block with the initial MAC (zero block)
    for (int i = 0; i < BLOCK_SIZE; i++) {
        xorResult[i] = message[i] ^ temp[i];
    }

    // Perform encryption (in this example, just copying the XOR result)
    memcpy(temp, xorResult, BLOCK_SIZE);

    // Copy the final MAC to the output variable
    memcpy(mac, temp, BLOCK_SIZE);
}

int main() {
    char key[BLOCK_SIZE] = "1234567"; // Updated key (fits within BLOCK_SIZE)
    char message[BLOCK_SIZE] = "Hello123"; // Truncated message to fit within BLOCK_SIZE - 1
    char mac[BLOCK_SIZE]; // MAC will be stored here

    // Calculate the MAC using CBC-MAC
    cbcMac(key, message, mac);

    // Print the MAC
    std::cout << "CBC-MAC for the message: ";
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", (unsigned char)mac[i]);
    }
    std::cout << std::endl;

    return 0;
}

