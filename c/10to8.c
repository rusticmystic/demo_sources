/* Shivdeep Singh
 * 10 bit YUV to 8bit yuv conversion. Clip MSB.
 * Simple conversion of a 5 10bits chunk to 4 8bits chunk clipping off the MSB*/

// Headers
#include <stdio.h>

// Main
int
main (int arg, char *argv[])
{

    char *inputFile;
    char *outputFile;

    char inputchunk[5]; // Stores 5bytes, 40 bits
    char outputchunk[4]; // stores 32 bits output

    FILE *fi, *fo;

    // Set Files
    inputFile = argv[1];
    outputFile = argv[2];

    // Open files
    fi = fopen (inputFile, "rb+");
    fo = fopen (outputFile, "wb+");

    if (!fo || !fi)
    {
        perror ("Error  Opening File\n");
        return -1;
    }

    printf ("Input File %s Output File %s\n", inputFile, outputFile);

    //read from input file
    while (!feof (fi))
    {
        fread (inputchunk, 1, 5, fi);

        // convert
        *(outputchunk) = *inputchunk;
        *(outputchunk + 1) =
            0xc0 & (*(inputchunk + 2) << 6) | (*(inputchunk + 1) >> 2) & 0x3f;
        *(outputchunk + 2) =
            0xf0 & (*(inputchunk + 3) << 4) | (*(inputchunk + 2) >> 4) & 0x0f;
        *(outputchunk + 3) =
            0xfc & (*(inputchunk + 4) << 2) | (*(inputchunk + 3) >> 6) & 0x03;

        fwrite (outputchunk, 4, 1, fo);
    }

    // close file pointers
    fclose (fo);
    fclose (fi);
    
    return 1;
}
