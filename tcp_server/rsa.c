#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
 
//int e, d, n;
#define p 41
#define q 491

#define d 10333
#define e 2997
#define n 20131

#define BUFFER_SIZE 1024

#define DECRYPTED_FILE "decrypted.bmp"
#define INPUT_FILE "out.bmp"

int FastExponention(int bit, int* y, int* a);
int FindT(int a, int m);
 
int FastExponention(int bit, int* y, int* a)
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
 
char Decryption(int value)
{
    return (char)FindT(value, d);
}
 
int main(int argc, char *argv[])
{
    FILE *input_file, *output_file;
    char buffer[BUFFER_SIZE]; //space to store the buffer read from file
    int encrypted_buffer[BUFFER_SIZE];
    int read_count = 0;

    //printf("argc: %d' \n", argc);

    if(argc<=2){
        printf("missing file as argument. please use 'rsa.exe encrypted_file decrypted_file' \n");
        exit(1);
    }

    if(argc>=4){
        printf("too many arguments. please use 'rsa.exe encrypted_file decrypted_file' \n");
        exit(1);
    }

    // destroy contents of decrypted files (from previous runs, if any)
    //output_file = fopen(argv[2], "w+");
    //fclose(output_file);
 
    // decryption starts
    input_file = fopen(argv[1], "rb");
    if (input_file == NULL) {
        printf("Error opening Cipher Text.\n");
        exit(1);
    }
 
    output_file = fopen(argv[2], "w+b");
    if (output_file == NULL) {
        printf("Error opening File.\n");
        exit(1);
    }

    //first read before entering the loop
    read_count = fread(encrypted_buffer, sizeof(int), BUFFER_SIZE, input_file);

    // this loop encrypts char by char of the buffer, and after write it to the encrypted file
    while (read_count > 0)  {
        for(int i = 0; i<read_count; i++){
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