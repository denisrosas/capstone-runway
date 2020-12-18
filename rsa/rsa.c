#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
 
//int e, d, n;
#define d 10333
#define e 2997
#define n 20131

#define BUFFER_SIZE 1024

void FastExponention(int bit, int* y, int* a)
{
    if (bit == 1)
        *y = (*y * (*a)) % n;
    
    *a = (*a) * (*a) % n;
}
 
int FindT(int a, int m)
{
    int r;
    int y = 1;
 
    while (m > 0) {
        r = m % 2;
        FastExponention(r, &y, &a);
        m = m / 2;
    }
    return y;
}
 
 
int Encryption(int value)
{
    return FindT(value, e);
}
 
char Decryption(int value)
{
    return (char)FindT(value, d);
}

int RSAEncryptFile(char *input_file_name, char *encrypted_file_name) {

    FILE* input_file, * output_file;
    char buffer[BUFFER_SIZE]; //space to store the buffer read from file
    int encrypted_buffer[BUFFER_SIZE];
    int read_count = 0;

    printf("RSAEncryptFile filename: %s \n", input_file_name);
    printf("RSAEncryptFile output filename: %s \n", encrypted_file_name);
    fflush(stdout);

    // destroy contents of these files (from previous runs, if any)
    //output_file = fopen(encrypted_file_name, "w+");
    //fclose(output_file);

    input_file = fopen(input_file_name, "rb");
    if (input_file == NULL) {
        printf("Error opening Source File.\n");
        exit(1);
    }

    output_file = fopen(encrypted_file_name, "w+b");
    if (output_file == NULL) {
        printf("Error opening Destination File.\n");
        exit(1);
    }

    //first read before entering the loop
    read_count = fread(buffer, sizeof(char), BUFFER_SIZE, input_file);

    // this loop encrypts char by char of the buffer, and after write it to the encrypted file
    while (read_count > 0) {
        for (int i = 0; i < read_count; i++) {
            encrypted_buffer[i] = Encryption(buffer[i]);
            //printf("encrypted_buffer[%d]: %d \n", i, encrypted_buffer[i]);
        }

        //write encrypted buffer size to file
        fwrite(encrypted_buffer, sizeof(int), read_count, output_file);

        //read BUFFER_SIZE characters from file
        read_count = fread(buffer, sizeof(char), BUFFER_SIZE, input_file);
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}

int RSADecryptFile(char *encrypted_file_name, char *decrypted_file_name) {
    FILE* input_file, * output_file;
    char buffer[BUFFER_SIZE]; //space to store the buffer read from file
    int encrypted_buffer[BUFFER_SIZE];
    int read_count = 0;

    // destroy contents of these files (from previous runs, if any)
    output_file = fopen(decrypted_file_name, "w+");
    fclose(output_file);

    // decryption starts
    input_file = fopen(encrypted_file_name, "rb");
    if (input_file == NULL) {
        printf("Error opening Cipher Text.\n");
        exit(1);
    }

    output_file = fopen(decrypted_file_name, "w+b");
    if (output_file == NULL) {
        printf("Error opening Destination File.\n");
        exit(1);
    }

    //first read before entering the loop
    read_count = fread(encrypted_buffer, sizeof(int), BUFFER_SIZE, input_file);

    // this loop encrypts char by char of the buffer, and after write it to the encrypted file
    while (read_count > 0) {
        for (int i = 0; i < read_count; i++) {
            buffer[i] = Decryption(encrypted_buffer[i]);
        }

        //write encrypted buffer size to file
        fwrite(buffer, sizeof(char), read_count, output_file);

        //read BUFFER_SIZE characters from file
        read_count = fread(encrypted_buffer, sizeof(int), BUFFER_SIZE, input_file);
    }

    fclose(output_file);

    return 0;
}
