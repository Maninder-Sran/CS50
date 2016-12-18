#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
    
    message = GetString();
    
    for(int i = 0, n = strlen(message); i < n; i++)
    {
        if(isalpha(message[i]))
        {
            if(isupper(message[i]))
            {
                message[i] = ((TOTAL_LETTER-(UPPER_END-(int)message[i])+key)%26)+UPPER_START;
            }
            else
            {
                message[i] = ((TOTAL_LETTER-(LOWER_END-(int)message[i])+key)%26)+LOWER_START;
            }
        }
        else if(ispunct(message[i]))
        {
        }
            
    }
    
    printf("%s\n",message);

}

