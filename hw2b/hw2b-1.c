/**
 * Name:        Blair Muraoka
 * Homework:    2b
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        09-08-2016
 * File:        hw2b-1.c
 * 
 * Description: This program contains the driver and function for taking
 * the second half a string and placing it in another array.
 */
 
#include <stdio.h>

int findlength(char []);
void halfstring(char [], char []);


/** 
 * Function name:   findlength
 * Description:     Takes an array (or pointer to array) and returns the 
 *                  number of chars in the array
 * Parameters:      input: The array being analyzed
 * Return values:   The amount of chars in the string
 */
int findlength(char input[])
{
    int length = 0;
    while (input[length] != '\0')
    {
        length++;
    }
    return length;
}
 
/** 
 * Function name:   halfstring
 * Description:     Takes two array parameters, full being the one with the whole
 *                  string, and half being the "container" for the string half
 * Parameters:      input: The array being analyzed
 */ 
void halfstring(char full[], char half[])
{
    int high = findlength(full);
    int i, mid, halfsize;
    
    if (high % 2 != 0) 
    {
        mid = (int)(high / 2);  
    }
    else
    {
        mid = (high / 2);
    }
    
    /* so it iterates the right amount of times */
    halfsize = mid + 1;
    
    for (i = 0; i < halfsize; i++) 
    {
        half[i] = full[mid];
        mid++;
    }
    half[halfsize] = '\0';
}

/** 
 * Function name:   main
 * Description:     Driver function. Creates a char array of size 100 and uses the
 *                  findlength function to get the string length and halves it to 
 *                  determine how large the second array being passed through the
 *                  halfstring function. Outputs the two strings at the end.
 */
int main(int argc, char * argv[])
{
    char inputstring[100] = "EvensLength";
    int length = 0;
    int half, i;
    
    length = findlength(inputstring);
	
    /* No "half" of a char */
    if (length % 2 != 0)
    {
        half = (int)(length / 2) + 1;
    }
    else
    {
        half = length / 2;
    }
    
    char halfer[half];
    
    halfstring(inputstring, halfer);
    
    printf("InputString: %s\n", inputstring);
    printf("HalfString : %s\n", halfer);
	
    return 0;
}
