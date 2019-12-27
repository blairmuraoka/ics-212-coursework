#include <stdio.h>
#include <string.h>
#include "record.h"

void menu(struct record **, int *);
void getaddress(char [], int);

void getaddress(char address[], int size)
{
    int i = 0;
    int exit = 0;
    char c;
    while (i < size && exit != 1)
    {
        c = fgetc(stdin);
                 
        if (c == '\n')
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

void menu(struct record ** start, int * numAccounts)
{
    int userchoice = 0;
    int i = 0;
    int user_accountno, user_yob, numDeleted;
    char buffer[100];
    char temp_int[10];
    char user_name[25];
    char user_address[80];
    
    while (userchoice != 6)
    {
        printf("\n***********BANK ACCOUNT MANAGEMENT***********\n");
        printf("1. Add a new record to the database\n");
        printf("2. Modify an existing record\n");
        printf("3. Print record information\n");
        printf("4. Print all record information\n");
        printf("5. Delete an existing record from the database\n");
        printf("6. Quit the program\n");
        printf("***********[Please enter a choice]***********\n--> ");
        
        fgets(buffer, sizeof buffer, stdin);
        sscanf(buffer, "%d", &userchoice);
        
        if (userchoice == 1)
        {
            printf("Enter an account number: ");
            fgets(buffer, sizeof buffer, stdin);
            sscanf(buffer, "%d", &user_accountno);
            printf("Enter a name: ");
            fgets(user_name, sizeof user_name, stdin);
            user_name[strcspn(user_name, "\n")] = 0;
            printf("Enter year of birth: ");
            fgets(buffer, sizeof buffer, stdin);
            sscanf(buffer, "%d", &user_yob);
            printf("Enter your address, then type a exclamation mark at the end (!): \n");
            getaddress(user_address, 80);
            addRecord(&*start, user_accountno, user_name, user_address, user_yob);
            printf("\nBankSystem: Record added to database successfully.\n");
            i++;
        }
        else if (userchoice == 2)  
        {
            printf("Enter account number: ");
            fgets(buffer, sizeof buffer, stdin);
            sscanf(buffer, "%d", &user_accountno);
            getaddress(user_address, 80);
            modifyRecord(*start, user_accountno, user_address);
        }    
        else if (userchoice == 3)
        {
            printf("Enter account number: ");
            fgets(buffer, sizeof buffer, stdin);
            sscanf(buffer, "%d", &user_accountno);
            printRecord(*start, user_accountno);
        }      
        else if (userchoice == 4)
        {
            printAllRecords(*start);
        } 
        else if (userchoice == 5)
        {
            printf("Enter account number: ");
            fgets(buffer, sizeof buffer, stdin);
            sscanf(buffer, "%d", &user_accountno);
            numDeleted = deleteRecord(&*start, user_accountno);
            i -= numDeleted;
            printf("\nBankSystem: %d record(s) deleted successfully.\n");
            
        }
        else if (userchoice == 6)
        {
            printf("hehe xd\n");
            *numAccounts = i + *numAccounts;
        }
        else
        {
            printf("Error: Enter a valid choice.\n");
            userchoice = 0;
        }
    }
}
