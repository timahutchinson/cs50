// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // Check for correct number of arguments
    if (argc != 4)
    {
        printf("Usage: resize n file1.bmp file2.bmp\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n > 100 || n < 0)
    {
        printf("Resize value must be between 0 and 100.\n");
        return 1;
    }

    // Save the file names
    char* infile = argv[2];
    char* outfile = argv[3];

    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL) // can't open file to read
    {
        printf("The input file could not be opened.\n");
        return 1;
    }

    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL) // can't open file to write
    {
        printf("The output file could not be created.\n");
        return 1;
    }

    // Read BITMAPFILEHEADER (old and new version)
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    BITMAPFILEHEADER bfNew = bf;

    // Read BITMAPINFOHEADER (old and new version)
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    BITMAPINFOHEADER biNew = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine old and new padding for scanlines
    int oldPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding = (4 - (bi.biWidth * n * sizeof(RGBTRIPLE)) % 4) % 4;

    // Alter the BITMAPFILEHEADER and BITMAPINFOHEADER for the resized file
    biNew.biWidth = bi.biWidth * n;
    biNew.biHeight = bi.biHeight * n;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * biNew.biWidth) + newPadding) * abs(biNew.biHeight);
    bfNew.bfSize = biNew.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfNew, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biNew, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Iterate over the original file's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Each line needs to be written n times
        for (int j = 0; j < n; j ++)
        {
            // Iterate over pixels in the line
            for (int k = 0; k < bi.biWidth; k++)
            {
                // Store pixel value
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // Write this pixel n times
                for (int m = 0; m < n; m++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // Write the correct number of padding pixels
            for (int m = 0; m < newPadding; m++)
            {
                fputc(0x00, outptr);
            }

            // Move the curser back to the beginning of this line to read it again
            fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
        }

        // Move the curser forward over this lines pixels + padding
        fseek(inptr, bi.biWidth * sizeof(RGBTRIPLE) + newPadding, SEEK_CUR);
    }

    // Close infile
    fclose(inptr);

    // Close outfile
    fclose(outptr);

    // Return success
    return 0;
}
