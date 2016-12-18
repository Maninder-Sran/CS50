/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

bool b_search(int values[], int key, int min, int max);
int midValue(int min, int max);
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 0)
    {
        return false;
    }
    // Linear search for value in array values
    if (b_search(values, value, 0, n - 1))
    {
        return true;
    }
    return false;
}

bool b_search(int values[], int key, int start, int end)
{
    bool state = true;
    // If max < min then the number was not found after recursion
    if (end < start || (start == end && key != values[start]))
    {
        return false;
    }
    else if (start == end && key == values[start])
    {
        // If the number is in the final division then return true
        return true;
    }
    
    int midpoint = midValue(start,end);

    // Depending on size of element at midpoint a particular half is eliminated
    if (values[midpoint] < key)
    {
        // If the element is less look in the right half
        state = b_search(values, key, midpoint + 1, end);
    }
    else if(values[midpoint] > key)
    {
        // If the element is greater then look in the left half
        state = b_search(values, key, start, midpoint - 1);
    }
    else
    {
        // If no half needs to be eliminated then the key was found
        return true;
    }
    return state;
}

int midValue(int min, int max)
{
    int result = (int) (min + max / 2);
    return result;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Bubble Sort that has O(n^2)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (values[j + 1] < values[j])
            {
                int temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
            }
        }
    }
}

