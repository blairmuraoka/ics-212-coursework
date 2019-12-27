/**
 * Name:        Blair Muraoka
 * Homework:    5
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        10-04-2016
 * File:        iofunctions.c
 * 
 * Description: Handles the File I/O functions necessary to read to the structure
 *				implemented: record.
 */
 
#include <stdio.h>
#include <string.h>
#include "record.h"

void readfile(struct record **, int * , char []);
void writefile(struct record *, int , char []);

/** 
 * Function name:   readfile
 * Description:     Reads an existing file's data and stores it's data in the
 *					struct records array that is passed through.
 * Parameters:      records[] - the array being altered
 *                  *numrecords - pointer to the int that deals with the number of records
 *					filename[] - the name of the file being read
 * Return:			0 if successful read
 *					1 if file does not exist
 */
 
void readfile(struct record ** start, int * numrecords, char filename[])
{
    FILE *blairebuff;
    char c;
    int num;
    int faccno, fyob;
    char fname[25];
    char faddress[80];
    
    int i = 0;
    int j = 0;
    blairebuff = fopen(filename, "r");
    
    if (blairebuff != NULL) 
    {
        /* Check if file is empty */
        fseek(blairebuff, 0, SEEK_END);
        if (ftell(blairebuff) != 0)
        {
            /* Go back to start of file if not empty */
            fseek(blairebuff, 0, SEEK_SET);
            
            while (!feof(blairebuff))
            {   
                j = 0;
                fscanf(blairebuff, "%d", &faccno);
                // fscanf doesn't read new line so need to read it
                fgetc(blairebuff);

                fgets(fname, 100, blairebuff);
                fname[strcspn(fname, "\n")] = 0;
                while ((c = fgetc(blairebuff)) != '!' && c != EOF)
                {
                    if (c == '\n')
                    {
                        faddress[j] = c;
                    }
                    else
                    {
                        faddress[j] = c;
                    }
                    j++;
                }
                faddress[j] = '\0';
                // Get the new line
                fgetc(blairebuff);

                fscanf(blairebuff, "%d", &fyob);
                fgetc(blairebuff);
                
                addRecord(&*start, faccno, fname, faddress, fyob);
                printf("\nBankSystem: Record from file added to database successfully.\n");
                i++;
            }
        }
        fclose(blairebuff);
    }
    
    *numrecords = i;

}

/** 
 * Function name:   writefile
 * Description:     Writes the data from the array that is passed to a specified file
 * Parameters:      records[] - the array that is being read
 *                  numrecords - the size of the array
 *					filename[] - the name of the file that will be created
 */
void writefile(struct record * start, int numRecords, char filename[])
{
    FILE *blairebuff;
    blairebuff = fopen(filename, "w");
    int i;
    struct record *temp;
    temp = start;
    for (i = 0; i < numRecords; i++)
    {
        fprintf(blairebuff, "%d\n", temp->accountno);
        fprintf(blairebuff, "%s\n", temp->name);
        fprintf(blairebuff, "%s!\n", temp->address);
        
        // If last record, don't add newline
        if (i != (numRecords - 1))
            fprintf(blairebuff, "%d\n", temp->yearofbirth);
        else
            fprintf(blairebuff, "%d", temp->yearofbirth);
        temp = temp->next;
    }
    
    fclose(blairebuff);
}
