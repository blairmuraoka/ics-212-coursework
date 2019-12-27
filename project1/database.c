/**
 * Name:        Blair Muraoka
 * Homework:    Project1
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        10-21-2016
 * File:        database.c
 * 
 * Description: This file contains the database functions necessary to interact with the
 *              the database. A global variable debugmode will be used if debug mode is 
 *              active (debug == 1). 
 */
 
#include <stdio.h>
#include <string.h>
#include "record.h"

extern int debugmode;

/* Prototypes */
int addRecord (struct record **, int, char [ ],char [ ],int);
int printRecord (struct record *, int);
int modifyRecord (struct record *, int, char [ ]);
void printAllRecords(struct record *);
int deleteRecord(struct record **, int);

/** 
 * Function name:   addRecord
 * Description:     Adds a record to the database at position based on year of birth (desc).
 * Parameters:      start  - the pointer to pointer of the start of the database
 *                  uaccno - account number to be inputted
 *                  uname  - name to be inputted
 *                  uaddr  - address to be inputted
 *                  uyob   - year of birth to be inputted
 * Return:          0 all cases (one case, shouldn't this just be a void?)
 * Notes:           I used strcpy since adding strings wasn't working out the way I wanted.
 */
int addRecord(struct record ** start, int uaccno, char uname[], char uaddr[], int uyob)
{
    struct record *temp, *prev, *temp2;
    int found = 0;
    
    if (debugmode == 1)
    {
        printf("\n::DEBUG:: Function addRecord called with parameters:\n");
        printf("start: %p\n", (void*)&start);
        printf("accountno: %i\n", uaccno);
        printf("name: %s\n", uname);
        printf("address: %s\n", uaddr);
        printf("yob: %i\n", uyob);
    }
    
    if (*start == NULL)
    {
        temp = (struct record *) malloc(sizeof(struct record));

        strcpy(temp->name, uname);
        strcpy(temp->address, uaddr);
        temp->accountno     = uaccno;
        temp->yearofbirth   = uyob;
        temp->next          = NULL;
        *start              = temp;
    }
    
    else
    {
        temp = *start;
        // Iterate through list and keep track of a previous node
        while (temp->next != NULL && found == 0)
        {
            if (uyob < temp->yearofbirth)
            {
                prev = temp;
                temp = temp->next;
            }
            else
            {
                found = 1;
            }
        }
        
        temp2 = (struct record *) malloc(sizeof(struct record));
        strcpy(temp2->name, uname);
        strcpy(temp2->address, uaddr);
        temp2->accountno    = uaccno;
        temp2->yearofbirth  = uyob;
        
        /* Handle cases at end of list */
        if (temp->next == NULL && temp != *start)
        {
            if (uyob < temp->yearofbirth)
            {
                temp2->next = NULL;
                temp->next  = temp2;
            }
            else
            {
                prev->next  = temp2;
                temp2->next = temp;
            }
        }

        
        else {
            if (temp == *start)
            {
                /* Handles case where record is inserted at the end of a database with one record */
                if (uyob < temp->yearofbirth)
                {
                    temp->next = temp2;
                    temp2->next = NULL;
                }
                /* Inserts before the start, start changes (uyob > temp->yob) */
                else
                {
                    temp2->next = *start;
                    *start      = temp2;
                }
            }
            else
            {
                /* All other cases */
                prev->next  = temp2;
                temp2->next = temp;

            }
        }
    }
    
    return 0;
}


/** 
 * Function name:   printRecord
 * Description:     Prints record information based on account number provided. Can print duplicates.
 * Parameters:      start  - the pointer to start of the database
 *                  uaccno - account number to make comparisons
 * Return:          0 - records were found
 *                  1 - records were not found
 */
int printRecord (struct record * start, int uaccno)
{
    struct record * temp = start;
    int found = 0;
    
    if (debugmode == 1)
    {
        printf("\n::DEBUG:: Function printRecord called with parameters:\n");
        printf("start: %p\n", (void*)start);
        printf("uaccno: %i\n", uaccno);
    }
    
	while (temp != NULL)
    {
        if (temp->accountno == uaccno)
        {
            printf("\n=============================\n");
            printf("Account number: %i\n", temp->accountno);
            printf("Name: %s\n", temp->name);
            printf("Year of Birth: %i\n", temp->yearofbirth);
            printf("Address:\n%s\n", temp->address);
            printf("=============================\n");
            found = 1;
        }
        temp = temp->next;
    }
    
    if (found == 1)
    {
        return 0;
    }
    
    /* Record not found */
    printf("\nERROR: Record not found.\n");
    return 1; 
}


/** 
 * Function name:   modifyRecord
 * Description:     Modifies address value of all records with correspnding account number
 * Parameters:      start   - the pointer to start of the database
 *                  uaccno  - account number to make comparisons
 *                  address - new address value
 * Return:          0       - records were found
 *                  found   - #records found and modified
 */
int modifyRecord (struct record * start, int uaccno, char uaddr[])
{
	struct record * temp = start;
    
    int found = 0;
    
    if (debugmode == 1)
    {
        printf("\n::DEBUG:: Function modifyRecord called with parameters:\n");
        printf("start: %p\n", (void*)start);
        printf("uaccno: %i\n", uaccno);
        printf("uaddr: %s\n", uaddr);
    }
    
	while (temp != NULL)
    {
        if (temp->accountno == uaccno)
        {
            strcpy(temp->address, uaddr);
            found++;
        }
        temp = temp->next;
    }
    
    if (found != 0)
    {
        printf("\nBankSystem: %d address(es) modified successfully.\n", found);
        return found;
    }
    
    /* Record not found */
    printf("\nERROR: Record not found.\n");
    return 0; 
}


/** 
 * Function name:   printAllRecords
 * Description:     Prints all records.
 */
void printAllRecords(struct record * start)
{
    struct record * temp = start;
    
    if (debugmode == 1)
    {
        printf("\n::DEBUG:: Function printAllRecords called with parameters:\n");
        printf("start: %p\n", (void*)start);
    }

	while (temp != NULL)
    {
        printf("\n=============================\n");
        printf("Account number: %i\n", temp->accountno);
        printf("Name: %s\n", temp->name);
        printf("Year of Birth: %i\n", temp->yearofbirth);
        printf("Address:\n%s\n", temp->address);
        printf("=============================\n");
        temp = temp->next;
    }
    if (start == NULL)
    {
        printf("\nBankSystem: There are no records.\n");
    }
}


/** 
 * Function name:   deleteRecord
 * Description:     Deletes all records with the corresponding account number.
 *                  Frees them from memory.
 * Parameters:      start      - pointer to the pointer of the start of database
 *                  uaccno     - account number to make comparisons
 * Return:          numDeleted - 0 if records not found or number of records deleted
 */
int deleteRecord(struct record ** start, int uaccno)
{
    struct record *temp, *prev;
    int numDeleted = 0;
    
    if (debugmode == 1)
    {
        printf("\n::DEBUG:: Function deleteRecord called with parameters:\n");
        printf("start: %p\n", (void*)&start);
        printf("uaccno: %i\n", uaccno);
    }
    
    if (*start != NULL)
    {
        
        temp = *start;
        prev = temp;
        
        /* Handling cases at beginning of database */
        while (temp != NULL && temp->accountno == uaccno)
        {
            /* In event start is the only element */
            if (temp->next == NULL)
            {
                free(temp);
                *start = NULL;
                temp = NULL;
            }
            else
            {
                *start = temp->next;
                free(temp);
                temp = *start;
            }
            numDeleted++;
        }
        
        /* Start going through the list with keeping track of previous node */
        while (temp != NULL)
        {
            if (temp->accountno == uaccno)
            {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
                numDeleted++;
            }
            else
            {
                prev = temp;
                temp = temp->next;
            }
        }
    }
    /* Return number of records deleted */
    return numDeleted; 
}
