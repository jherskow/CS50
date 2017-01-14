/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4

 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy n infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    int n = atoi(argv[1]);
    
        if (n < 1 || n > 100)
    {
        printf("Range: 1-10\n");
        return 1;
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
    // determine padding and width for INPUT scanlines
    int inPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int inWidth = bi.biWidth;
    int inHeight = bi.biHeight;
    
    // re-assign size-influenced parts of output file
    bi.biWidth *= n; 
    bi.biHeight *= n;
    bf.bfSize -= bi.biSizeImage;
    int outPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; // determine padding for OUTPUT scanlines
    bi.biSizeImage = ((bi.biWidth * abs(bi.biHeight) * sizeof(RGBTRIPLE)) + (abs(bi.biHeight) * outPadding));
    bf.bfSize += bi.biSizeImage; 

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    


    // iterate over infile's scanlines 
    for (int i = 0, abInHeight = abs(inHeight); i < abInHeight; i++)
    {
        for (int line = 0; line < n; line++) // repeat n times for each scanline
        {
            // iterate over pixels in scanline
            for (int j = 0; j < inWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // write RGB triple to outfile
                for (int pixel = 0; pixel < n; pixel++) //redo pixel n times
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            // skip over padding in input, if any
            fseek(inptr, inPadding, SEEK_CUR);
            
            // write padding to output
            for (int k = 0; k < outPadding; k++)
            fputc(0x00, outptr);
    
            if (line < n-1) //return cursor to input scanline start, except on nth iteration
            fseek(inptr, -1*(sizeof(RGBTRIPLE)*inWidth + inPadding), SEEK_CUR);
            
            //fseek(inptr, -12, SEEK_CUR); //this works
            //3 width by 3 pixel size gives 9, and inpadding is already the byte value of padding
            //(inWidth * sizeof(one pixel) + paddingBytes).
        }

        
    }
    //int debug = -1*(sizeof(RGBTRIPLE)*inWidth + inPadding);
    //printf("inwidth %i inpadding %i \n DEBUG: %i \n" , inWidth, inPadding, debug); //DEBUG DEBUG
     
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
