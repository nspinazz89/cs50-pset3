/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    //make sure n is positive
    if (n < 0 )
    {
        return false;
    }
    //create variables for first last and middle values
    int firstValue = 0;
    int lastValue = n - 1;
    int middle = (firstValue + lastValue) / 2;
    
    //loop through, first checking if we found value in the middle and then 
    //setting first value to middle plus one if we are too low and 
    //last value to middle minus one if we are too high. Then calculate new middle 
    //and try again till first value is greater than last value. 
    while (firstValue <= lastValue)
    {
        if (values[middle] == value)
        {
            return true;
        }
        else if (values[middle] < value)
        {
            firstValue = middle + 1;
        }
        else
        {
            lastValue = middle - 1;
        }
        middle = (firstValue + lastValue) / 2;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    //create temp variable and swap counter set to non zero
    int temp;
    int swapCounter = -1;
    //loop through till swap counter = 0
    while (swapCounter != 0)
    {
        //on each iteration set the swap counter to zero
        swapCounter = 0;
        for (int i = 0; i < n; i++)
        {
            //check to see if the current value is larger than the next value 
            //if so swap them and increment the swap counter
            if (values[i] > values[i + 1])
            {
                temp = values[i];
                values[i] = values[i + 1];
                values[i + 1] = temp;
                swapCounter++;
            }
            
        }
    }
}