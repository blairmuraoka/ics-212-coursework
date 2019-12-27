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

int modifyRecord (struct record * start, int uaccno, char address[])
{
	struct record * temp = start;
    int found = 0;
    
    if (debugmode == 1)
    {
        printf("\n::DEBUG:: Function modifyRecord called with parameters:\n");
        printf("start: %p\n", (void*)start);
        printf("u: %i\n", uaccno);
        printf("address: %s\n", address);
    }
    
	while (temp != NULL)
    {
        if (temp->accountno == uaccno)
        {
            strcpy(temp->address, address);
            found = 1;
        }
        temp = temp->next;
    }
    
    if (found == 1)
    {
        printf("\nBankSystem: Address modified successfully.\n");
        return 0;
    }
    
    /* Record not found */
    printf("\nERROR: Record not found.\n");
    return 1; 
}

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
