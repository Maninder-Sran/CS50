#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Declaration of constants representing start and end value of alphas in ASCII
#define TOTAL_LETTER 25
#define UPPER_END 90
#define UPPER_START 65
#define LOWER_END 122
#define LOWER_START 97

int main(int argc, string argv[])
{
     // If the argument count is not equal to 2(name and arg) then prompt user
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    // Store the string relative of the key in a variable
    string key = argv[argc - 1];
    string message;
    bool check = true;
    
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        // If the char is not alpha then set the check for alpha false
        if (!isalpha(key[i]))
        {
            check = false;
        }
    }
    
    // If the string contains something other than alpha then prompt error
    if (!check)
    {
        printf("Usage: ./caesar key(word)\n");
        return 1;
    }
    
    // Get an input message to encrypt from the user 
    message = GetString();
    
    for (int i = 0, n = strlen(message), key_length = strlen(key), counter = 0; i < n; i++)
    {
        
        if (counter == key_length)
        {
            counter = 0;
        }
         // If the letter is an alphabetical encrypt else do nothing to it
        if (isalpha(message[i]))
        {
             // If the letter in the message is uppercase use the appropriate formula
            if (isupper(message[i]))
            {
                 // If the letter in the keyword is uppercase use the appropriate formula
                if (isupper(key[counter]))
                {
                    message[i] = ((TOTAL_LETTER - (UPPER_END - (int) message[i]) + (TOTAL_LETTER - (UPPER_END - (int) key[counter]))) % 26) + UPPER_START;
                }
                else
                {
                    message[i] = ((TOTAL_LETTER - (UPPER_END - (int) message[i]) + (TOTAL_LETTER - (LOWER_END - (int) key[counter]))) % 26) + UPPER_START;
                }
            }
            else
            {
                // If the letter in the keyword is uppercase use the appropriate formula
                if (isupper(key[counter]))
                {
                    message[i] = ((TOTAL_LETTER - (LOWER_END - (int) message[i]) + (TOTAL_LETTER - (UPPER_END - (int) key[counter]))) % 26) + LOWER_START;
                }
                else
                {
                    message[i] = ((TOTAL_LETTER - (LOWER_END - (int) message[i]) + (TOTAL_LETTER - (LOWER_END - (int) key[counter]))) % 26) + LOWER_START;
                }
            }
            counter++;
        }
    }
    
    printf("%s\n",message);
    
    return 0;   
}