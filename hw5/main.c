/**
 * Name:        Blair Muraoka
 * Homework:    5
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        10-04-2016
 * File:        main.c
 * 
 * Description: Driver function. Calls the readfile function, then writefile if readfile
 *              was successful. Also asks the user if they wish to add more accounts into
 *              the database if the database is not full already.
 *              Change line 82 parameter "changeme.txt" for testing.
 */

#include <stdio.h>
#include <string.h>
#include "account.h"

void getaddress(char [], int);

/** 
 * Function name:   getaddress
 * Description:     Takes the user input for the address field using fgetc, so we can retrieve new lines.
 *                  The loop ends when i is equal to size, or if exit is equal to 1. 
 *                  The user can type in a '?' char to end the loop early.
 * Parameters:      address[] - the char array the string will be stored in
 *                  size - the size of the address array
 */
void getaddress(char address[], int size)
{
    int i = 0;
    int exit = 0;
    char c;
    while ( i < size && exit != 1 )
    {
        c = fgetc(stdin);
                 
        if ( c == '\n' )
        {
            if (address[i - 1] == '!')
            {
                address[i - 1] = '\0';
                exit = 1;
            }
            else 
            {
                address[i] = '\n';
                i++;
            }
        }
        
        else {
            address[i] = (char) c;
            i++;    
        }
        
        if (i >= size)
        {
            address[size - 1] = '\0';
            exit = 1;
            /* To rid the new line when over capacity (fixed a problem with segmentation fault) */
            while ((c = fgetc(stdin)) != EOF && c != '\n');
        }    
    }
}

/** 
 * Function name:   main
 * Description:     Driver function. Creates a database that is passed through to readfile and
 *                  writefile functions. If the file being read does not exist, then writefile
 *                  will not be called.
 * Return:          0 if successful read/write
 *                  1 if file doesn't exist
 */
int main(int argc, char * argv[])
{
    struct account accounts[5];
    char buffer[100];
    int numAccounts, extra;
    int i,j,x = 0;
    
    if(readfile(accounts, &numAccounts, "test5.txt") == 0)
	{
		// extra being the number of free slots open
		extra = 5 - numAccounts;
		
		// option to add more
		if (extra != 0)
		{
			printf("How many extra accounts to add? Enter an integer from 0-%d: ", extra);
			
			fgets(buffer, 100, stdin);
			sscanf(buffer, "%d", &x);
			
			while (x > extra || x < 0)
			{
				printf("Invalid number. Please enter a value from 0-%d: ", extra);
				fgets(buffer, 100, stdin);
				sscanf(buffer, "%d", &x);	
			}
			
			if (x != 0)
			{
				j = numAccounts;
				for (i = 0; i < x; i++)
				{
					printf("\nEnter information for NewAccount %d\n", i+1);
					printf("Account Number: ");
					fgets(buffer, 100, stdin);
					sscanf(buffer, "%d", &accounts[j].accountno);
					
					printf("Name: ");
					fgets(accounts[j].name, 25, stdin);
					accounts[j].name[strcspn(accounts[j].name, "\n")] = 0;
					
					printf("Address: ");
					getaddress(accounts[j].address, 80);
					
					printf("Year of birth: ");
					fgets(buffer, 100, stdin);
					sscanf(buffer, "%d", &accounts[j].yearofbirth);
					j++;
				}
				
				numAccounts += x;
			}
		}

		writefile(accounts, numAccounts, "temp.txt");
        
        // For output proof
        printf("=============================\n");
        for (i = 0; i < numAccounts; i++)
        {
            printf("\nACCOUNTNO: %d\n", accounts[i].accountno);
            printf("NAME: %s\n", accounts[i].name);
            printf("ADDRESS: %s\n", accounts[i].address);
            printf("YEAROFBIRTH: %d\n", accounts[i].yearofbirth);
        }        
	}
	else 
	{
        printf("Error: File doesn't exist. Exiting...\n");
		return 1;
	}
    return 0;
}
