#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char InputFileName[100];
char OutputFileName[100];
char DecryptedFileName[100];

// Function declarations
void encryptData(FILE *inputFile, FILE *outputFile, int shift);
void decryptData(FILE *inputFile, FILE *outputFile, int shift);
int openFile();

int main() {
    int shift;
    char ch;

    printf("\n\n ************* DATA ENCRYPTION/DECRYPTION PROGRAM ***************\n\n\n");

    //Enter E/e for decrypt
    //Enter D/d for decrypt
    printf("\n\n  Do You want to ENCRYPT (E) or DECRYPT (D) a file? \n  Enter E or D : ");
    scanf(" %c", &ch);

    if (ch == 'E' || ch == 'e') {
        printf("\n\n  Enter the file name that you want to encrypt (example.txt)  : ");
        scanf("%s", InputFileName);

        // openFile function call
        openFile();

        // Shift value determines how many positions each character in the input text should be shifted to create the encrypted output.
        printf("\n\n  Enter the shift value (a positive integer): ");
        scanf("%d", &shift);

        printf("\n\n  Enter the output file name for encryption (encrypt_file.txt)   : ");
        scanf("%s", OutputFileName);

        FILE *inputFile = fopen(InputFileName, "r");
        FILE *outputFile = fopen(OutputFileName, "w");

        // Encryption function call
        encryptData(inputFile, outputFile, shift);

        fclose(inputFile);
        fclose(outputFile);

        printf("\n\n\n ----------The %s file is encrypted Successfully----------\n\n", InputFileName);

    } else if (ch == 'D' || ch == 'd') {
        printf("\n\n  Enter the file name that you want to decrypt (encrypt_file.txt)  : ");
        scanf("%s", InputFileName);

        printf("\n\n  Enter the shift value (the same positive integer used for encryption): ");
        scanf("%d", &shift);

        printf("\n\n  Enter the output file name for decryption (decrypt_file.txt)   : ");
        scanf("%s", DecryptedFileName);

        FILE *inputFile = fopen(InputFileName, "r");
        FILE *outputFile = fopen(DecryptedFileName, "w");

        // Decryption function call
        decryptData(inputFile, outputFile, shift);

        fclose(inputFile);
        fclose(outputFile);

        printf("\n\n\n ----------The %s file is decrypted Successfully----------\n\n", InputFileName);
    } else {
        printf("\n\n  ++++++++++ Invalid Input! Program is Terminated ! ++++++++++\n\n");
        exit(1);
    }

    return 0;
}

int openFile() {
    FILE *file;
    extern char InputFileName[100];

    // Open the file in read mode
    file = fopen(InputFileName, "r");

    // Check if the file exists
    if (file == NULL) {
        printf("\n\n   File does not exist. Please create the file first.\n");
        exit(1);
    }

    printf("\n\n  File exists and is opened. \n");
    printf("\n\n  You can proceed with Encryption or Decryption... \n");
    fclose(file);
    return 0;
}

void encryptData(FILE *inputFile, FILE *outputFile, int shift) {
    char ch;

    while ((ch = fgetc(inputFile)) != EOF) {
        if (ch >= 'A' && ch <= 'Z') {
            ch = ((ch - 'A') + shift) % 26 + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            ch = ((ch - 'a') + shift) % 26 + 'a';
        }
        fputc(ch, outputFile);
    }
}

void decryptData(FILE *inputFile, FILE *outputFile, int shift) {
    char ch;

    // The decryption process is the same as encryption, but we use the reverse shift value.
    int reverseShift = 26 - (shift % 26);

    while ((ch = fgetc(inputFile)) != EOF) {
        if (ch >= 'A' && ch <= 'Z') {
            ch = ((ch - 'A') + reverseShift) % 26 + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            ch = ((ch - 'a') + reverseShift) % 26 + 'a';
        }
        fputc(ch, outputFile);
    }
}

