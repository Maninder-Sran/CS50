#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int mins  = 0;
    int bottles = 0;
    
    printf("minutes: \n");
    // Get input from user for time spent in shower
    mins = GetInt();
    // Calculate the amount of bottles used for that length of shower
    bottles = mins * 12;
    // Output amount of bottles that the specified length of shower uses
    printf("bottles: %i\n" ,bottles);
}