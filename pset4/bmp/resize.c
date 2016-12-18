/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a bitmap image
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames and factor value
    int factor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // check if num is positive and is in range
    if(factor < 1 || factor > 100)
    {
        printf("number inputed must be > 1 and <= 100\n");
        return 3;
    }
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // Retain old height and width
    int oldHeight = bi.biHeight;
    int oldWidth = bi.biWidth;
    // Update height and width according to factor
    bi.biHeight *= factor;
    bi.biWidth *= factor;

    // determine original padding for scanlines
    int padding =  (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // determine the new padding for scanlines
    int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // Update the size of the image
    bi.biSizeImage = ((bi.biWidth * sizeof(RGBTRIPLE)) + newPadding) * abs(bi.biHeight);
    // Update the file size
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(oldHeight); i < biHeight; i++)
    {
        // Retain the location of the start of the scanline
        fpos_t start_pos;
        fgetpos(inptr, &start_pos);
        
        for(int j = 0; j < factor; j++)
        {
            // If not done iterating go back to the start of the line
            if (j < factor)
                fsetpos(inptr, &start_pos);
                
            // iterate over pixels in scanline
            for (int m = 0; m < oldWidth; m++)
            {
                // temporary storage
                RGBTRIPLE triple;   
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                for(int k = 0; k < factor; k++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
                
            }
        }    
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // add any padding that is required 
        for (int z = 0; z < newPadding; z++)
            fputc(0x00, outptr);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
