/**
 * Name:        Blair Muraoka
 * Homework:    9
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        12-05-2016
 * File:        Homework9.java
 * 
 * Description: This file contains the java class and functions that will
 *              handle menu operations and printing, while tying in code from a
 *              C source.
 */
 
import java.util.Scanner;

public class Homework9 
{
    static
    {
        System.loadLibrary("Homework9");
    }
    
    public native float convertCtoF(int n);
    
    public native int roundUp(int n);
    
    /** 
     * Function name:   printTable
     * Description:     Prints a formatted table of the conversions up to 
     *                  the user-inputted maximum. Assigns tempInF's value
     *                  based on the return of convertCtoF. 
     *                  After printing a line, increments the tempInC counter by 5
     *                  and repeats while tempInC isn't larger than max.
     * Parameters:      max - holds value of when to end the while loop (roundUp value)
     */
    public void print(int max)
    {
        int tempInC = 0;
        float tempInF = 0;
        
        System.out.printf(" temp in C%8stemp in F%n", "");
        while (tempInC <= max)
        {
            //print i then converted
            System.out.printf("%10d%17.2f%n", tempInC, tempInF);
            tempInF = convertCtoF(tempInC);
            tempInC += 5;
        }
    }
	
	
    /** 
     * Function name:   getInput
     * Description:     UI function to get proper user input, rounds it up, if needed, to the nearest
	 *					multiple of 5.
     * Return:			The rounded up value of the user input
     */
    public int getInput()
    {
        Scanner s = new Scanner(System.in);
        int input;
		boolean pass = true;
        
        System.out.print("Please enter a maximum temperature in Fahrenheit (C) --> ");
		do
		{
			while(!s.hasNextInt())
			{
				System.out.print("ERROR: Please enter a valid integer --> ");
				s.next();
			}
			input = s.nextInt();
			pass = true;
			
			if (input <= 0)
			{
				System.out.print("ERROR: Please enter a valid integer --> ");
				pass = false;
			}
		} while (!pass);
			
		System.out.println(" input: " + input);	
        input = roundUp(input);
        
        return input;
    }
    
	
	/* Function name:   main
	 * Description:     Driver function. Calls the getInput function to obtain input value,
	 *                  then calls print function to print the list.
	 */
    public static void main(String args[])
    {
        int input;
        Homework9 hw9 = new Homework9();
        
        System.out.println("\n::TEMP CONVERSION PROGRAM (C to F)::");
        
        input = hw9.getInput();
        
        hw9.print(input);
    }
}
