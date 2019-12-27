/**
 * Name:        Blair Muraoka
 * Homework:    1
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        08-30-2016
 * File:        homework1.c
 * 
 * Description: This program contains the driver and user-interface functions
 *              for Homework 1 - the temperature conversion program.
 */
 
#include <stdio.h>

float convertCtoF(int);
int roundUp(int);
void printTable(int, int);

/** 
 * Function name:   convertCtoF
 * Description:     Takes an integer value and performs the conversion from
 *                  Celsius to Fahrenheit
 * Parameters:      temperature (int): the temperature to be converted to F
 * Return values:   The original temperature (C) as a Fahrenheit of float type
 */
 
float convertCtoF(int temperature) 
{
    return temperature * 9/5 + 32;
}

/** 
 * Function name:   roundUp
 * Description:     Takes the number given to the function and uses
 *                  the modulo function to see if it is equal to 0
 *                  Increments until number % 5 = 0
 * Parameters:      number (int): the number to be rounded up
 * Return values:   Either the original number or the new rounded number
 */
 
int roundUp(int number) 
{
    while ((number % 5) != 0)
    {
        number++;
    }
    
    return number;
}

/** 
 * Function name:   printTable
 * Description:     Prints a formatted table of the conversions up to 
 *                  the user-inputted maximum
 * Parameters:      current (int): placeholder from where to start from
 *                  max (int): holds value of when to end the while loop
 * Return values:   none
 */
 
void printTable(int current, int max)
{
    printf("\n\tTemperature in C\tTemperature in F\n");
    
    while (current <= max) 
    {
        printf("\t%16d\t%16.2f\n", current, convertCtoF(current));
        current += 5;
    }
}

/** 
 * Function name:   main
 * Description:     Driver - accepts user input and executes the conversion
 *                  based on the user's input.
 * Parameters:      argc (int): number of arguments (1 in this case)
 *                  argv (char * []): string values of each argument
 * Return values:   0: success
 */
 
int main(int argc, char * argv[])
{
	printf("This program will accept a user-inputted integer and convert it from Celsius to\n Fahrenheit in increments of five.\n");
    char userInput[10];
    int valid = 0;
    int i, maxTemp;

    while (valid == 0)
    {
        printf("Please enter a maximum temperature in Celsius (C): ");
        valid = 1;
        fgets(userInput, 10, stdin);
        /** checking first index for a negative sign generally */
        if (userInput[0] != '-' && !isdigit(userInput[0]))
            valid = 0;
        else
        {
            /** strlen(userInput) - 1 because there is a nonblankspacechar after the last input */
            for (i = 1; i < strlen(userInput) - 1; i++)
            {
                if (!isdigit(userInput[i]))
                {
                    valid = 0;
                }
            }
        }
        
        if (valid == 0)
            printf("Error, please enter a valid integer greater than 0.\n");      
        else 
            sscanf(userInput, "%d", &maxTemp);        
            
        if (valid == 1 && maxTemp <= 0)
        {
            printf("Error, please enter a valid integer greater than 0.\n");
            valid = 0;
        }
    }
    
    maxTemp = roundUp(maxTemp);
    printTable(0, maxTemp);
    
    return 0;
}
