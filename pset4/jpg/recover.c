/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <cs50.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define SIZE 512

int getHex(int i);

int main(int argc, char* argv[])
{
    // Variable declerations
    int counter = 0;
    bool isfound = false;
    uint8_t buffer[SIZE];
    
    // Open the input file
    FILE* file = fopen("card.raw", "r");
    FILE* img = NULL;
    
    if (file == NULL)
    {
        printf("Could not open card.raw\n");
        return 1;
    }
    
    // While still able to read 512 bytes of data run loop
    while(fread(buffer, SIZE, 1, file) == 1)
    {
        for(int i = 0; i < 16; i++)
        {
            // If the first 4 bytes are jpeg signatures then create new file
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] == getHex(i))
            {
                isfound = true;
                
                // Close output file if already open
                if (img != NULL)
                    fclose(img);
                
                // Declare and assign filename    
                char filename[8];
                sprintf(filename, "%03d.jpg", counter++);
            
                // Open output file            
                img = fopen(filename, "a");
                
                if (img == NULL)
                {
                    printf("Unable to open %s", filename);
                    return 2;
                }    
                break;
            }
        }
        if (isfound)
        {
            // Write to output file
            if (img != NULL)
                fwrite(buffer, SIZE, 1, img);
        }    
    }
    
    if (img != NULL)
        fclose(img);
        
    fclose(file);
    
    return 0;
}

int getHex(int i)
{
    switch(i)
    {
        case 0:
            return 0xe0;
        case 1:
            return 0xe1;
        case 2:
            return 0xe2;
        case 3:
            return 0xe3;
        case 4:
            return 0xe4;
        case 5:
            return 0xe5;
        case 6:
            return 0xe6;
        case 7:
            return 0xe7;
        case 8:
            return 0xe8;
        case 9:
            return 0xe9;
        case 10:
            return 0xeA;
        case 11:
            return 0xeB;
        case 12:
            return 0xeC;
        case 13:
            return 0xeD;
        case 14:
            return 0xeE;
        case 15:
            return 0xeF;
        default: 
            return 0xe0;
    }
}