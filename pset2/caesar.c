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
    string strKey = argv[argc - 1];
    string message;
    int key = 0;
    bool check = true;
    
    for (int i = 0, n = strlen(strKey); i < n; i++)
    {
        // If the char is not an int equivalent then set the check for int false
        if (!isdigit(strKey[i]))
        {
            check = false;
        }
    }
    
    // If the string contains only an int then convert it to an int and store it
    if (check)
    {
        key = atoi(strKey);
    }
    else 
    {
        // If the check is false prompt user to enter an arg that is int 
        printf("Usage: ./caesar key(int)\n");
        return 1;
    }
    
    // Get an input message to encrypt from the user 
    message = GetString();
    
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        // If the letter is an alphabetical encrypt else do nothing to it
        if (isalpha(message[i]))
        {
            // If the letter is uppercase use the appropriate formula
            if (isupper(message[i]))
            {
                message[i] = ((TOTAL_LETTER - (UPPER_END - (int) message[i]) + key) % 26) + UPPER_START;
            }
            else
            {
                message[i] = ((TOTAL_LETTER - (LOWER_END - (int) message[i]) + key) % 26) + LOWER_START;
            }
        }
    }
    
    printf("%s\n",message);
    
    return 0;
}
