/**
 * Name:        Blair Muraoka
 * Homework:    Project2
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        11-26-2016
 * File:        iofunctions.cpp
 * 
 * Description: This file contains class methods of llist readfile and writefile. It also contains
 *              some functions used by the menu function in main.cpp, namely getAddress and getValidInput,
 *              which obtain input from the user.
 */

#include "llist.h"

// llist class methods
/** 
 * Method name:     readfile 
 * Description:     Reads the file specified by the constructor. Calls the addRecord function to add to database
 *                  if the file exists until an EOF is found. If the file does not exist, it will not make any 
 *                  changes to the database.
 * Return:          0 all cases
 */
int llist::readfile()
{
    string buffer, uname, uaddr;
    int uaccno, uyob, count;
    bool pass;
    ifstream blairefile;
    
    #ifdef DEBUGMODE
        cout << "\n==============DEBUG==============\n";
        cout << "readfile method called\n";
        cout << "==============DEBUG==============\n";
    #endif
    
    blairefile.open(filename.c_str());
    count = 0;
    pass  = false;
    
    cout << "Adding entries from " << filename << "...\n";
    if (blairefile.is_open())
    {
        while (!blairefile.eof())
        {
            pass = false;
            blairefile >> uaccno;
            // Obtain the newline to read next line
            blairefile.get();
            getline(blairefile, uname);
            while (!pass)
            {
                getline(blairefile, buffer);
                uaddr += buffer;
                if (buffer[buffer.size() - 1] == '!')
                {
                    uaddr.erase(uaddr.size() - 1);
                    pass = true;
                }
                else 
                {
                    uaddr += '\n';
                }
            }            
            blairefile >> uyob;
            
            addRecord(uaccno, uname, uaddr, uyob);
            count++;
            uaddr.clear();
        }
        
        blairefile.close();
        cout << count << " records from file added to database successfully.\n";
    }
    else
    {
        cout << "ERROR: Unable to open file. File does not exist.\n";
    }
    
    return 0;
}


/** 
 * Method name:     writefile 
 * Description:     Write to the file specified by the constructor. If the file does not exist, it
 *                  will create it and input the data into that file.
 * Return:          0 all cases
 */
int llist::writefile()
{
    ofstream blairefile;
    record * current = start;
    
    #ifdef DEBUGMODE
        cout << "\n==============DEBUG==============\n";
        cout << "writefile method called\n";
        cout << "==============DEBUG==============\n";
    #endif
    
    blairefile.open(filename.c_str());
    if (blairefile.is_open())
    {
        while (current)
        {
            blairefile << current-> accountno   << "\n";
            blairefile << current-> name        << "\n";
            blairefile << current-> address     << "!\n";
            blairefile << current-> yearofbirth;
            
            if (current-> next)
            {
                blairefile << "\n";
            }
            current = current-> next;
        }
    }
    else
    {
        cout << "ERROR: Unable to open file.\n";
    }
    
    return 0;
}


// Non-class functions
/** 
 * Function name:   getaddress
 * Description:     Takes the user input for the address field using getline and puts in a loop.
 *                  The loop ends when an exclamation mark at the end is found.
 * Parameters:      uaddr - the string that we will store input into
 */
void getAddress(string & uaddr)
{
    string buffer;
    bool pass = false;
    
    #ifdef DEBUGMODE
        cout << "\n==============DEBUG==============\n";
        cout << "getAddress called with params:\n";
        cout << "reference to string uaddr\n";
        cout << "==============DEBUG==============\n";
    #endif
    
    while (!pass)
    {
        getline(cin, buffer);
        uaddr += buffer;
        if (buffer[buffer.size() - 1] == '!')
        {
            uaddr.erase(uaddr.size() - 1);
            pass = true;
        }
        else 
        {
            uaddr += '\n';
        }
    }
}


/** 
 * Function name:   getValidInput
 * Description:     Handles grabbing a valid integer choice and doesn't allow user
 *                  to move on until a valid integer has been read.
 * Parameters:      input - the integer that we will store input into
 */
void getValidInput(int & input)
{
    bool next  = false;
    bool valid;
    int i = 0;
    string buffer;
    
    #ifdef DEBUGMODE
        cout << "\n==============DEBUG==============\n";
        cout << "getValidInput called with params:\n";
        cout << "reference to int input\n";
        cout << "==============DEBUG==============\n";
    #endif
    
    while(!next)
    {
        valid = true;
        i = 0;
        
        getline(cin, buffer);
        
        // Check each character of the string and '\0'
        while (i < (buffer.length())  && buffer[i] != '\0' && valid)
        {
            if (!isdigit(buffer[i]))
            {
                if (buffer[i] == '-' && i == 0)
                {
                    valid = true;
                }
                else
                {
                    valid = false;
                }
            }
            i++;
        }
        
        if (!valid || buffer.length() == 0)
        {
            cout << "ERROR: Invalid input. Please input a valid integer: ";
        }
        else
        {
            stringstream(buffer) >> input;
            // Finally a valid input
            next = true;        
        }
    }
    
}
