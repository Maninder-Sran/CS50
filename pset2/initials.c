#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void printInits(string name);

int main(void)
{
    // Get input of name from user
    string name = GetString(); 
    // Call function that outputs initials using name as input
    printInits(name); 
}

void printInits(string name)
{
    // Print the first letter which is guaranteed initial
    printf("%c",toupper(name[0]));
    
    for(int i = 0, n = strlen(name); i < n; i++)
    {
        // If there is a space the next char will be the beginning of a name
        if (isspace(name[i]))
        {
            printf("%c",toupper(name[i + 1]));
        }
    }
    
    printf("\n");
}