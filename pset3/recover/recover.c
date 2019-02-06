#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCKSIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Catch wrong number of arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover filename\n");
        return 1;
    }

    // Open the memory card file
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");

    // Return 2 if file cannot be opened.
    if (inptr == NULL)
    {
        fprintf(stderr, "File cannot be opened.\n");
        return 2;
    }

    // Create our buffer
    BYTE buffer[512];

    // Track file count
    int fileNum = 0;

    // Output filename
    char filename[8];

    // Pointer for output files
    FILE *outptr = NULL;

    while (1)
    {
        // Read in a block
        size_t bytesRead = fread(buffer, sizeof(BYTE), BLOCKSIZE, inptr);

        // If the length of the block is less than 512, it's the end of the file
        if (bytesRead < 512)
        {
            break;
        }

        // Check for the start of a new JPG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close existing output file if one is open
            if (outptr != NULL)
            {
                fclose(outptr);
                fileNum++;
            }

            // Open a new file
            sprintf(filename, "%03d.jpg", fileNum);
            outptr = fopen(filename, "w");
        }

        // If we have an open file, write to it
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCKSIZE, outptr);
        }
    }

    // Close the remaining open files
    fclose(outptr);
    fclose(inptr);

    // Success
    return 0;
}
