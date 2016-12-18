#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height= 0;
    // Prompt for height of pyramid until height is >= 0 but <= 23
    do
    {
        printf("Height: ");
        // Get input for height using GetInt() method
        height = GetInt();
    }while(height < 0 || height > 23);
    
    for (int i = 1; i <= height; i++)
    {
        // Print number of spaces that the pyramid stars are offset
        for (int k = i; k < height; k++)
        {
            printf(" ");
        }
        // Print stars increasingly as the row number increases
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
