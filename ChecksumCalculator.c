#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

//Prototype Functions
unsigned char checkSum8(const char* text, int length);
unsigned short checkSum16(const char* text, int length);
unsigned int checkSum32(const char* text, int length);
void xPad(char* text, int* length, int blockSize);

int main(int argc, char** argv) {

    //File pointer
    FILE* file;
    int checksize;
    int index = 0;


    // Convert checksum size argument to integer
    checksize = atoi(argv[2]);

    // Open file
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("File cannot be opened");
        return 1;
    }

    // Check valid checksum size
    if (checksize != 8 && checksize != 16 && checksize != 32) {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return 1;
    }

    // Read characters from file into plaintext array
    char plaintext[1000];
    int c;
    int charCnt = 0;  

    //This increments the Character Counter
    while ((c = fgetc(file)) != EOF && index < 999) {
        plaintext[index++] = c;
        charCnt++;  
    }
    
    plaintext[index] = '\0';  // Ensure string termination

    // Close file
    fclose(file);

    // Pad data if needed
    if (checksize == 16) {
        xPad(plaintext, &index, 2);
    } else if (checksize == 32) {
        xPad(plaintext, &index, 4);
    }

    // Update character count to include padding
    charCnt = index;


    // Print plaintext with line which breaks every 80 characters
    printf("\n");
    for (int i = 0; i < index; i++) {
        printf("%c", plaintext[i]);
        if ((i + 1) % 80 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    // Calculates the checksum and displays it
    unsigned long checksum;
    if (checksize == 8) {
        unsigned char checksum8 = checkSum8(plaintext, index);
        checksum = checksum8;
        printf("%2d bit checksum is %8lx for all %4d chars\n", checksize, checksum, charCnt);
    } else if (checksize == 16) {
        unsigned short checksum16 = checkSum16(plaintext, index);
        checksum = checksum16;
        printf("%2d bit checksum is %8lx for all %4d chars\n", checksize, checksum, charCnt);
    } else if (checksize == 32) {
        unsigned int checksum32 = checkSum32(plaintext, index);
        checksum = checksum32;
        printf("%2d bit checksum is %8lx for all %4d chars\n", checksize, checksum, charCnt);
    }

    return 0;
}

//Functions

unsigned char checkSum8(const char* text, int length) {
    unsigned char checksum = 0;
    for (int i = 0; i < length; i++) {
        checksum += text[i];
    }
    return checksum;
}

unsigned short checkSum16(const char* text, int length) {
    unsigned short checksum = 0;
    // Sum pairs of characters
    for (int i = 0; i < length; i += 2) {
        checksum += (text[i] << 8) | (i + 1 < length ? text[i + 1] : 0);
    }
    return checksum;
}

unsigned int checkSum32(const char* text, int length) {
    unsigned int checksum = 0;
    // Sum pairs of 16-bit checksums
    for (int i = 0; i < length; i += 4) {
        checksum += (text[i] << 24) | (i + 1 < length ? text[i + 1] << 16 : 0) | (i + 2 < length ? text[i + 2] << 8 : 0) | (i + 3 < length ? text[i + 3] : 0);
    }
    return checksum;
}

void xPad(char* text, int* length, int blockSize) {
    int padLength = blockSize - (*length % blockSize);
    if (padLength != blockSize) {
        for (int i = 0; i < padLength; i++) {
            text[(*length)++] = 'X';
        }
        text[*length] = '\0';  
    }
}

