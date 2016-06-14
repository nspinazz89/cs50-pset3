/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // TODO: check to make sure there are exactly 1 or 2 arguments with ./generate
    // If there are not 2 quit with error code 1 and print a statement. 
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // TODO: convert the fist arugment after program name into an int 
    // and store it in a variable n so it can be manipulated
    int n = atoi(argv[1]);

    // TODO: if there is a second argument provided after program name,
    // convert it to an int and then cast it to a long int. Next call srand48
    // on this value to seed the internal buffer for drand48. 
    // If only a single argument is provided along with the program name
    // take the current time and cast it as a long int and then use it
    // to seed the internal buffer for drand48. 
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // TODO: Multiply the constant LIMIT by drand48 which was seeded by srand48 
    // earlier, then cast the value to an int. Print this int to the screen and 
    // repeat the process n (the value from argv[1]) times. 
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}