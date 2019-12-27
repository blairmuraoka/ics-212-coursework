/**
 * Name:        Blair Muraoka
 * Homework:    5
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        10-04-2016
 * File:        iofunctions.c
 * 
 * Description: Handles the File I/O functions necessary to read to the structure
 *				implemented: account.
 */
 
#include <stdio.h>
#include <string.h>
#include "account.h"

int readfile(struct account [], int * , char []);
void writefile(struct account [], int , char []);

/** 
 * Function name:   readfile
 * Description:     Reads an existing file's data and stores it's data in the
 *					struct accounts array that is passed through.
 * Parameters:      accounts[] - the array being altered
 *                  *numAccounts - pointer to the int that deals with the number of accounts
 *					filename[] - the name of the file being read
 * Return:			0 if successful read
 *					1 if file does not exist
 */
int readfile(struct account accounts[], int * numAccounts, char filename[])
{
    FILE *blairebuff;
    char c;
    int num;
    int i, j = 0;
    blairebuff = fopen(filename, "r");
    
    if (blairebuff == NULL) 
    {
        return 1;
    }
    else
    {
        // Put 5 as a limit as to not write into illegal memory
        while (!feof(blairebuff) && i != 5)
        {   
            j = 0;
            fscanf(blairebuff, "%d", &accounts[i].accountno);
            // fscanf doesn't read new line so need to read it
            fgetc(blairebuff);

            fgets(accounts[i].name, 100, blairebuff);
            accounts[i].name[strcspn(accounts[i].name, "\n")] = 0;
            while ((c = fgetc(blairebuff)) != '!' && c != EOF)
            {
                if (c == '\n')
                {
                    accounts[i].address[j] = c;
                }
                else
                {
                    accounts[i].address[j] = c;
                }
                j++;
            }
            accounts[i].address[j] = '\0';
            // Get the new line
            fgetc(blairebuff);

            fscanf(blairebuff, "%d", &accounts[i].yearofbirth);
            fgetc(blairebuff);
            
            i++;
        }
    }
	
    *numAccounts = i;
    
    fclose(blairebuff);
	return 0;
}

/** 
 * Function name:   writefile
 * Description:     Writes the data from the array that is passed to a specified file
 * Parameters:      accounts[] - the array that is being read
 *                  numAccounts - the size of the array
 *					filename[] - the name of the file that will be created
 */
void writefile(struct account accounts[], int numAccounts, char filename[])
{
    FILE *blairebuff;
    blairebuff = fopen(filename, "w");
    int i;
    for (i = 0; i < numAccounts; i++)
    {
        fprintf(blairebuff, "%d\n", accounts[i].accountno);
        fprintf(blairebuff, "%s\n", accounts[i].name);
        fprintf(blairebuff, "%s!\n", accounts[i].address);
        
        // If last record, don't add newline
        if (i != (numAccounts - 1))
            fprintf(blairebuff, "%d\n", accounts[i].yearofbirth);
        else
            fprintf(blairebuff, "%d", accounts[i].yearofbirth);
    }
    
    fclose(blairebuff);
}
