#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <time.h>

// Function to encrypt plaintext using AES-128 in CBC mode with PKCS7 padding
void encrypt_aes_128_cbc(const unsigned char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext, const int length)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    // Create and initialize the context
    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);

    // Enable padding
    EVP_CIPHER_CTX_set_padding(ctx, EVP_PADDING_PKCS7);

    // Perform the encryption
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, length);
    ciphertext_len = len;

    // Finalize the encryption
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);
}

// Function to decrypt ciphertext using AES-128 in CBC mode with PKCS7 padding
void decrypt_aes_128_cbc(const unsigned char *ciphertext, const unsigned char *key, const unsigned char *iv, unsigned char *plaintext, const int length)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;

    // Create and initialize the context
    ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);

    // Enable padding
    EVP_CIPHER_CTX_set_padding(ctx, EVP_PADDING_PKCS7);

    // Perform the decryption
    EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, length);
    plaintext_len = len;

    // Finalize the decryption
    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    plaintext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);
}

// Function to perform PKCS7 padding
void add_pkcs7_padding(unsigned char *data, int data_len, int block_size)
{
    int padding_len = block_size - (data_len % block_size);

    for (int i = 0; i < padding_len-1; i++) {
        data[data_len + i] = (unsigned char)padding_len;
    }


}

// Function to remove PKCS7 padding
void remove_pkcs7_padding(unsigned char *data, int *data_len)
{
    int padding_len = data[*data_len - 1];
    *data_len -= padding_len;
}

int main()
{
    // Define the plaintext and key
    unsigned char plaintext[] = "0xD{Pvzzl€Cr4ck}";
    unsigned char key[] = "aesEncryptionKey";
    unsigned char iv[EVP_MAX_IV_LENGTH] = {"encryptionIntVec"}; // Initialization Vector

    // Ensure that the plaintext length is a multiple of the block size
    int plaintext_len = strlen((char *)plaintext);
    int padded_len = plaintext_len;

    if (padded_len % EVP_CIPHER_block_size(EVP_aes_128_cbc()) != 0)
        padded_len = (plaintext_len / EVP_CIPHER_block_size(EVP_aes_128_cbc()) + 1) * EVP_CIPHER_block_size(EVP_aes_128_cbc());

    // Allocate memory for the ciphertext and padded plaintext
    unsigned char *ciphertext = (unsigned char *)malloc(padded_len);
    unsigned char *decryptedtext = (unsigned char *)malloc(padded_len);

    // Perform PKCS7 padding on the plaintext
    add_pkcs7_padding(plaintext, plaintext_len, EVP_CIPHER_block_size(EVP_aes_128_cbc()));

    // Encrypt the padded plaintext
    encrypt_aes_128_cbc(plaintext, key, iv, ciphertext, padded_len);

    // Decrypt the ciphertext
//    decrypt_aes_128_cbc(ciphertext, key, iv, decryptedtext, padded_len);

    // Remove PKCS7 padding from the decrypted plaintext
    remove_pkcs7_padding(decryptedtext, &padded_len);

    // Print the results
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < padded_len; i++)
        printf("%02x", ciphertext[i]);
    printf("\n");
//    printf("Decrypted text: %s\n", decryptedtext);

    // Clean up
    free(ciphertext);
//    free(decryptedtext);

    printf("\n Press any key to continue...");

    return 0;
}
