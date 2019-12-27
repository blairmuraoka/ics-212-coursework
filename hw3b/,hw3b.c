/**
 * Name:        Blair Muraoka
 * Homework:    3b
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        09-20-2016
 * File:        hw3b.c
 * 
 * Description: This file contains the user-interface that allows the user to interact and
 *              make changes based on their input to the bank database.
 *              I wasn't sure where to put function prototypes so I put them together with 
 *              their definitions.
 */
 
#include <stdio.h>
#include "record.h"

int debugmode = 0;

/** 
 * Function name:   main
 * Description:     Driver function. Outputs a menu that the user will interact with to update/change
 *                  the bank database. The menu will loop until the user selects the exit option.
 */
int main(int argc, char * argv[])
{
    if ( argc < 3 )
    {
        if ( argc == 2 )
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
            struct record * start = NULL;
            int userchoice = 0;
            int exit = 0;
            int user_accountno;
            int user_yob;
            char buffer[100];
            char temp_int[10];
            char user_name[25];
            char user_address[80];
            
            while (exit != 1)
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
                    printf("Enter desired account number: ");
                    fgets(buffer, sizeof buffer, stdin);
                    sscanf(buffer, "%d", &user_accountno);
                    
                    printf("Enter a name: ");
                    fgets(user_name, sizeof user_name, stdin);
                    user_name[strcspn(user_name, "\n")] = 0;
                    
                    printf("Enter year of birth: ");
                    fgets(buffer, sizeof buffer, stdin);
                    sscanf(buffer, "%d", &user_yob);
                    
                    printf("Enter your address, then type a question mark at the end (?), followed by ENTER: \n");
                    getaddress(user_address, 80);
                    addRecord(&start, user_yob, user_name, user_address, user_accountno);
                }
                else if (userchoice == 2)  
                {
                    printf("Enter account number: ");
                    fgets(buffer, sizeof buffer, stdin);
                    sscanf(buffer, "%d", &user_accountno);
                    
                    printf("Enter your address, then type a question mark at the end (?), followed by ENTER: \n");
                    getaddress(user_address, 80);
                    modifyRecord(start, user_accountno, user_address);
                }    
                else if (userchoice == 3)
                {
                    printf("Enter account number: ");
                    fgets(buffer, sizeof buffer, stdin);
                    sscanf(buffer, "%d", &user_accountno);
                    
                    printRecord(start, user_accountno);
                }      
                else if (userchoice == 4)
                {
                    printAllRecords(start);
                } 
                else if (userchoice == 5)
                {
                    printf("Enter account number: ");
                    fgets(buffer, sizeof buffer, stdin);
                    sscanf(buffer, "%d", &user_accountno);
                    
                    deleteRecord(&start, user_accountno);
                }
                else if (userchoice == 6)
                {
                    printf("hehe xd\n");
                    exit = 1;
                }
                else
                {
                    printf("Error: Enter a valid choice.\n");
                    userchoice = 0;
                }
                
            }
        }
    }
    else
    {
        printf("ERROR: Too many arguments. Exiting program...\n");
    }
}
