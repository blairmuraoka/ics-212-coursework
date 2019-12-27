/**
 * Name:        Blair Muraoka
 * Homework:    8
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        11-13-2016
 * File:        hw8.cpp
 * 
 * Description: This program contains the driver and user-interface functions for
 *              the C++ implementation of Homework 1 (Temperature conversion).
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

void convertCtoF(int, float &);
void roundUp(int &);
void interface();
void printTable();

/** 
 * Function name:   convertCtoF
 * Description:     Takes an integer value and performs the conversion from
 *                  Celsius to Fahrenheit. Stores it in converted.
 * Parameters:      temperature - the temperature to be converted to F
 *                  converted   - the address of the converted temperature  
 */
void convertCtoF(int val, float& converted)
{
    converted = (val * 9)/5 + 32;
}

/** 
 * Function name:   roundUp
 * Description:     Takes the number given to the function and uses
 *                  the modulo function to see if it is equal to 0
 *                  Increments until val % 5 = 0
 * Parameters:      val - address of the number to be rounded up
 */
void roundUp(int& val)
{
    while ((val % 5) != 0)
    {
        val++;
    }
}

/** 
 * Function name:   printTable
 * Description:     Prints a formatted table of the conversions up to 
 *                  the user-inputted maximum. Calls convertCtoF with local variable
 *                  tempInF. After printing a line, increments the current counter by 5
 *                  and repeats while current isn't larger than max.
 * Parameters:      current - placeholder from where to start from
 *                  max     - holds value of when to end the while loop (roundUp value)
 * Return values:   none
 */
void printTable(int current, int max)
{
    cout << "\n" << setw(16) << "Temperature in C" << setw(19) << "Temperature in F\n";
    float tempInF;
    while (current <= max) 
    {
        convertCtoF(current, tempInF);
        cout << setw(16) << current << setw(18) << tempInF << "\n";
        current += 5;
    }
}

/** 
 * Function name:   interface
 * Description:     UI function to get proper user input, and stores it in input
 *                  Reads the user input as a string and checks if it can be parsed
 *                  as an integer. 
 *                  Error message 1 - invalid input (not an integer)
 *                  Error message 2 - integer is <= 0
 * Parameters:      input - address of input
 */
void interface(int& input)
{
    bool next  = false;
    bool valid = true;
    int i = 0;
    string buffer;
    
    cout << "Please input a valid integer larger than 0: ";
    while(!next)
    {
        valid = true;
        i = 0;
        
        getline(cin, buffer);
        
        // Check each character of the string, ignoring '-' and '\0'
        while (i < (buffer.length())  && buffer[i] != '\0' && valid)
        {
            if (!isdigit(buffer[i]))
            {
                if (buffer[i] == '-' && i == 0)
                {
                    valid = true;
                }
                else
                {
                    valid = false;
                }
            }
            i++;
        }
        
        if (!valid)
        {
            cout << "1: Invalid input. Please input a valid integer larger than 0: ";
        }
        else
        {
            stringstream(buffer) >> input;
            if (input <= 0)
            {
                cout << "2: Invalid input. Please input a valid integer larger than 0: ";
            }
            else
            {
                // Finally a valid input
                next = true;
            }
        }
    }
    
}

/** 
 * Function name:   main
 * Description:     Driver function. Calls the interface function to obtain input value,
 *                  then calls roundUp function to get the right value to start printing.
 */
int main(int argc, char * argv[])
{
    cout << "**********************************\n";
    cout << "* TEMPERATURE CONVERSION PROGRAM *\n";
    cout << "**********************************\n\n";
    int input;
    interface(input);
    roundUp(input);
    printTable(0, input);
}
