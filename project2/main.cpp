/**
 * Name:        Blair Muraoka
 * Homework:    Project2
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        11-26-2016
 * File:        main.cpp
 * 
 * Description: This file contains the menu user-interface function and main. Main will create a
 *              new llist object on the heap and pass it to the menu function by reference. After 
 *              the user exits the menu, it will then call the copy constructor to make a copy of the
 *              database and then remove both from heap, resulting in two .txt files.
 */

#include "llist.h"

void menu(llist &);
void getValidInput(int &);
void getAddress(string &);


/** 
 * Function name:   menu
 * Description:     Outputs a menu that the user will interact with to update/change
 *                  the bank database. The menu will loop until the user selects the exit option.
 * Parameters:      database - the database to be manipulated
 */
void menu(llist & database)
{
    int input, uaccno, uyob, numChanged;
    string uname, uaddr, buffer;
    bool invalid = false;
    bool reverse = false;
    bool pass    = false;
    
    #ifdef DEBUGMODE
        cout << "\n==============DEBUG==============\n";
        cout << "menu function called with params:\n";
        cout << "database being worked with"
        cout << "==============DEBUG==============\n";
    #endif
    while (input != 7) 
    {
        input = 0;
        uaddr.clear();
        
        cout << "\n**********[BANK ACCOUNT MANAGEMENT]**********\n";
        cout << "1. Add record to database\n";
        cout << "2. Modify existing record(s)\n";
        cout << "3. Print record(s) information\n";
        cout << "4. Print all records information\n";
        cout << "5. Delete record(s) from database\n";
        cout << "6. Reverse the order of database\n";
        cout << "7. Exit program\n";
        cout << "***********[Please enter a choice]***********\n--> ";        
        getValidInput(input);
        if (input == 1)
        {
            if (reverse)
            {
                cout << "ERROR: You must call reverse again before you can add to the database.\n";
            }
            else
            {
                cout << "Enter desired account number: ";
                getValidInput(uaccno);
                cout << "Enter desired name: ";
                getline(cin, uname);
                cout << "Enter your address, then type a exclamation mark at the end (!):\n";
                getAddress(uaddr);
                cout << "Enter your year of birth: ";
                getValidInput(uyob);
                
                database.addRecord(uaccno, uname, uaddr, uyob);
                cout << "\nRecord [" << uaccno << "] added to database successfully.\n";
            }
        }
        else if (input == 2)
        {
            cout << "Enter account number: ";
            getValidInput(uaccno);
            cout << "Enter your address, then type an exclamation mark at the end (!):\n";
            getAddress(uaddr);
            
            numChanged = database.modifyRecord(uaccno, uaddr);
            if (numChanged == 0)
            {
                cout << "BankSys: Record with account number [" << uaccno << "] was not found.\n";
            }
            else
            { 
                cout << numChanged << " records modified successfully.\n";
            }
        }
        else if (input == 3)
        {
            cout << "Enter account number: ";
            getValidInput(uaccno);
            
            numChanged = database.printRecord(uaccno);
            if (numChanged == 0)
            {
                cout << "BankSys: Record with account number [" << uaccno << "] was not found.\n";
            }
            else
            { 
                cout << numChanged << " records printed successfully.\n";
            }
        }
        else if (input == 4)
        {
            cout << database;
            //database.printAll();
        }
        else if (input == 5)
        {
            cout << "Enter account number: ";
            getValidInput(uaccno);
            
            numChanged = database.deleteRecord(uaccno);
            if (numChanged == 0)
            {
                cout << "BankSys: Record with account number [" << uaccno << "] was not found.\n";
            }
            else
            {
                cout << numChanged << " records deleted successfully.\n";
            }
        }
        else if (input == 6)
        {
            database.reverse();
            if (!reverse)
            {
                reverse = true;
                cout << "Database is now in reversed order. You may not add records/exit until reverse is called again.\n";
            }
            else
            {
                reverse = false;
                cout << "Database is back in it's original order. You may add records/exit if you wish.\n";
            }
        }
        else if (input == 7)
        {
            if (reverse)
            {
                cout << "ERROR: You must call reverse again before you can exit the program.\n";
                input = 0;
            }
            else
            {
                cout << "hehe xd \n(exiting program...)\n";
            }
        }    
        else
        {
            cout << "Invalid input. Please choose an integer from 1-7.\n";
        }
    }
}


/** 
 * Function name:   main
 * Description:     Driver function.                
 */
int main(int argc, char * argv[])
{
    llist * database = new llist();
    
    menu(*database);
    // Destructor call
    llist * copy;
    copy = database;
    
    delete database;
    delete copy;
    
}
