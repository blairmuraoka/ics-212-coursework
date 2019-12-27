/**
 * Name:        Blair Muraoka
 * Homework:    Project1
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        10-21-2016
 * File:        main.c
 * 
 * Description: Driver file. Contains the main method that will tie the code from different files
 *              together. Global variable debug is set in the definition of main.
 */
 
#include <stdio.h>
#include <string.h>
#include "record.h"

int debugmode = 0;

/** 
 * Function name:   main
 * Description:     Driver function. Checks command-line arguments to see if it should run debug mode.
 *                  If valid arguments are inputted, readfile will check if a database already exists.
 *                  Menu will be displayed, and upon exiting menu function, the program will
 *                  write/overwrite the file bankrecords.txt and exit.
 *                  Functions takes pointer values so values changed within the functions will 
 *                  modify the values within main (*start and numAccounts).                 
 */
int main(int argc, char * argv[])
{
    struct record * start = NULL;
    int numAccounts;  
    
    if (argc < 3)
    {
        if (argc == 2)
        {
            if ( strcmp("debug", argv[1]) == 0 )
            {
                debugmode = 1;
                printf("\n::DEBUG:: Debug mode activated.\n");
            }
            else {
                printf("ERROR: Invalid arguments. Exiting program...\n");
            }
        }
        
        if ( argc == 1 || debugmode == 1 )
        {
            readfile(&start, &numAccounts, "bankrecords.txt");
            menu(&start, &numAccounts);
            writefile(start, numAccounts, "bankrecords.txt");           
        }    
        
        free(start);
    }

    else
    {
        printf("ERROR: Too many arguments. Exiting program...\n");
    }   
}
