#include <cs50.h>
#include <stdio.h>
#include <math.h>

// Prototype for function that calculates num of digits
int numDigits(int num);

int main(void)
{
    // Initialize variables 
    int numCoins     = 0;
    int formatChange = 0;
    int num_digits = 0;
    int lastDigit = 0;
    int change_int = 0;
    float change  = 0;

    // Prompt for input of "owed change" until input is greater than 0
    do
    {
        printf("How much change is owed?\n");
        // Get input for change using GetFloat() method
        change = GetFloat();
    }while(change < 0);
    
    // Set desired number of place values required for calculations 
    change *= 100;
    // Cast from float to int to turnicate any place values that were not needed
    change_int = (int) change;
    
    // Calculate number of digits using defined function
    num_digits = numDigits(change_int);
    // Determine the last_digit for rounding calculations
    lastDigit = change_int % 10;
    
    // If the digit is 0 or number of digits is too small don't round 
    if (lastDigit == 0 || num_digits <= 2)
    {
        formatChange = change_int;
    }
    else if (lastDigit < 5)
    {
        // If the last digit is less then 5 round down
        formatChange = change_int - 1;
    }
    else
    {
        // If the last digit is greater then 5 round up
        formatChange = change_int + 1;
    }
    
    // Increase numCoins by number of quarters that can be given
    numCoins += formatChange / 25;
    // Decrease the amount of change to account for quarters "given"
    formatChange -= (formatChange / 25) * 25;
    
    // Increase numCoins by number of dimes that can be given
    numCoins += formatChange / 10;
    // Decrease the amount of change to account for dimes "given"
    formatChange -= (formatChange / 10) * 10;
    
    // Increase numCoins by number of nickels that can be given
    numCoins += formatChange / 5;
    // Decrease the amount of change to account for nickels "given"
    formatChange -= (formatChange / 5) * 5;
    
    // Increase numCoins by number of pennies that can be given
    numCoins += formatChange / 1;
    
    printf("%i\n",numCoins);
    
    return 0;
}

int numDigits(int num)
{
    int counter = 0;
    // Increment counter by 1 for every place value in num
    while(num > 0)
    {
        num /= 10;
        counter++;
    }
    return counter;
}
