/**
 * Name:        Blair Muraoka
 * Homework:    Project2
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        11-26-2016
 * File:        llist.cpp
 * 
 * Description: This file contains the definitions of the prototypes defined in llist.h
 *              This file does not contain the readfile/writefile (that is in a separate file).
 *              This file will handle the manipulation of the database.
 */

#include "llist.h"

/** 
 * Method name:     llist 
 * Description:     Default Constructor. Sets a default filename and calls readfile.
 */
llist::llist()
{
    #ifdef DEBUGMODE
        cout << "\n==============DEBUG==============\n";
        cout << "llist default constructor called\n";
        cout << "==============DEBUG==============\n";
    #endif
    
    this-> filename = "database.txt";
    this-> start    = NULL;
    readfile();
}


/** 
 * Method name:     llist 
 * Description:     Constructor with filename parameter. Sets filename to given parameter and calls readfile.
 * Parameters:      ufilen - filename provided
 */
llist::llist(string ufilen)
{
    #ifdef DEBUGMODE
        cout << "\n==============DEBUG==============\n";
        cout << "llist constructor called with params:\n";
        cout << "ufilen: " << ufilen << "\n";
        cout << "==============DEBUG==============\n";
    #endif
    
    this-> filename = ufilen;
    this-> start    = NULL;
    readfile();
}


/** 
 * Method name:     llist 
 * Description:     Copy constructor. Reads from a different list, filename is parameter's filename prefixed
 *                  by Copy of. Iterates through the list and calls addRecords with values of those items
 *                  being copied, rather than copying pointers.
 * Parameters:      list - the list that is being imported
 */
llist::llist(llist & list)
{
    #ifdef DEBUGMODE
        cout << "\n==============DEBUG==============\n";
        cout << "llist copy constructor called with params:\n";
        cout << "reference to llist list\n";
        cout << "==============DEBUG==============\n";
    #endif
    
    record * temp   = list.start;
    this-> start    = NULL;
    this-> filename = "Copy of " + list.filename;
    
    while (temp)
    {
        this-> addRecord(temp-> accountno, temp-> name, temp-> address, temp-> yearofbirth);
        temp = temp-> next;
    }
}


/** 
 * Method name:     llist 
 * Description:     Destructor. Calls writefile to store the file and then the cleanup function, which
 *                  takes care of removing items from the heap.
 */
llist::~llist()
{
    writefile();
    cleanup();
}


/** 
 * Method name:     addRecord 
 * Description:     Adds a record to the database at position based on year of birth (desc).
 * Parameters:      uaccno - account number for new record
 *                  uname  - name for new record
 *                  uaddr  - address for new record
 *                  uyob   - year of birth for new record
 * Return:          0 all cases, successful add
 */
int llist::addRecord(int uaccno, string uname, string uaddr, int uyob)
{    
    bool found = false;
    record * newRecord, * prev, * temp;
    
    #ifdef DEBUGMODE
        cout << "\n==============DEBUG==============\n";
        cout << "addRecord called with params:\n";
        cout << "uaccno: "  << uaccno << "\n";
        cout << "uname : "  << uname  << "\n";
        cout << "uaddr :\n" << uaddr  << "\n";
        cout << "uyob  : "  << uyob   << "\n";
        cout << "==============DEBUG==============\n";
    #endif

    newRecord = new record();
    
    newRecord-> name           = uname;
    newRecord-> address        = uaddr;
    newRecord-> accountno      = uaccno;
    newRecord-> yearofbirth    = uyob;
    newRecord-> next           = NULL;

    if (start == NULL)
    {
        start = newRecord;
        start-> next = NULL;
    }
    else
    {
        temp = start;
        while (temp && !found)
        {
            if (uyob < temp-> yearofbirth)
            {
                prev = temp;
                temp = temp-> next;
            }
            else
            {
                found = true;
            }
        }
        
        if (temp == start)
        {
            temp        = newRecord;
            temp-> next = start;
            start       = temp;
        }
        
        else if (temp == NULL)
        {
            prev-> next = newRecord;
        }
        
        else
        {
            prev-> next      = newRecord;
            newRecord-> next = temp;
        }
    }
    
    return 0;
}


/** 
 * Method name:     printRecord 
 * Description:     Prints record information based on account number provided. Can print duplicates.
 * Parameters:      uaccno - account number for record(s) being printed
 * Return:          found  - number of records that were printed 
 */
int llist::printRecord(int uaccno)
{
    record * temp = start;
    int found = 0;
    
    #ifdef DEBUGMODE
        cout << "\n==============DEBUG==============\n";
        cout << "printRecord called with params:\n";
        cout << "uaccno: "  << uaccno << "\n";
        cout << "==============DEBUG==============\n";
    #endif    
    
    while (temp)
    {
        if (temp-> accountno == uaccno)
        {
            cout << "\n=============================\n";
            cout << "Account number: " << temp-> accountno << "\n";
            cout << "Name: " << temp-> name << "\n";
            cout << "Year of Birth: " << temp-> yearofbirth << "\n";
            cout << "Address:\n" << temp-> address << "\n";
            cout << "=============================\n";
            found++;
        }
        temp = temp-> next;
    }
    
    return found;
}


/** 
 * Method name:     modifyRecord 
 * Description:     Modifies address value of all records with correspnding account number.
 * Parameters:      uaccno - account number for record(s) being modified
 *                  uaddr  - modified address
 * Return:          found  - number of records that were modified
 */
int llist::modifyRecord(int uaccno, string uaddr)
{
    record * temp = start;
    int found = 0;
    
    #ifdef DEBUGMODE
        cout << "\n==============DEBUG==============\n";
        cout << "modifyRecord called with params:\n";
        cout << "uaccno: "  << uaccno << "\n";
        cout << "uaddr :\n" << uaddr  << "\n";
        cout << "==============DEBUG==============\n";
    #endif   
    
    while (temp != NULL)
    {
        if (temp-> accountno == uaccno)
        {
            temp-> address = uaddr;
            found++;
        }
        temp = temp-> next;
    }
    
    return found;
}


/** 
 * Method name:     printAll 
 * Description:     Prints all records in the database.
 */
void llist::printAll()
{
    record * temp = start;
    
    #ifdef DEBUGMODE
        cout << "\n==============DEBUG==============\n";
        cout << "printAll called\n";
        cout << "==============DEBUG==============\n";
    #endif
    
    if (temp == NULL)
    {
        cout << "\nBankSystem: There are no records.\n";
    }
    else
    {
        while (temp)
        {
            cout << "\n=============================\n";
            cout << "Account number: " << temp-> accountno << "\n";
            cout << "Name: " << temp-> name << "\n";
            cout << "Year of Birth: " << temp-> yearofbirth << "\n";
            cout << "Address:\n" << temp-> address << "\n";
            cout << "=============================\n";        
            temp = temp-> next;
        }
    }
}


/** 
 * Method name:     deleteRecord 
 * Description:     Deletes all records with the corresponding account number. 
 *                  Removes them from heap after deletion.
 * Parameters:      uaccno - account number for record(s) being deleted
 * Return:          found  - number of records that were deleted
 */
int llist::deleteRecord(int uaccno)
{
    record * prev, * temp;
    int numDeleted = 0;
    
    #ifdef DEBUGMODE
        cout << "\n==============DEBUG==============\n";
        cout << "deleteRecord called with params:\n";
        cout << "uaccno: "  << uaccno << "\n";
        cout << "==============DEBUG==============\n";
    #endif
    
    if (start != NULL)
    {
        temp = start;
        prev = temp;
        
        while (temp)
        {
            if (uaccno == temp-> accountno)
            {
                if (temp == start)
                {
                    start = temp-> next;
                    delete temp;
                    temp = start;
                }
                else
                {
                    if (temp-> next == NULL)
                    {
                        prev-> next = NULL;
                    }
                    else
                    {
                        prev-> next = temp-> next;
                    }
                    delete temp;
                    temp = prev-> next;
                }
                numDeleted++;
            }
            else
            {
                prev = temp;
                temp = temp-> next;
            }
        }
    }
    
    return numDeleted;
}


/** 
 * Function name:   operator<< 
 * Description:     Alternate printAll function. Overloads the << operator.
 *                  Can be called like "cin << list", where list is an llist object.
 * Parameters:      stream   - output stream
 *                  database - llist object to read and print from
 * Return:          stream   - output stream
 */
ostream& operator<< (ostream& stream, llist& database)
{
    record * temp = database.start;
    
    #ifdef DEBUGMODE
        cout << "\n==============DEBUG==============\n";
        cout << "operator<< overload called\n";
        cout << "database: " << &database << "\n";
        cout << "This is the address of database obj\n";
        cout << "==============DEBUG==============\n";
    #endif
    
    while (temp)
    {
        cout << "\n=============================\n";
        cout << "Account number: " << temp-> accountno << "\n";
        cout << "Name: " << temp-> name << "\n";
        cout << "Year of birth: " << temp-> yearofbirth << "\n";
        cout << "Address: " << temp-> address << "\n";
        cout << "=============================\n";
        temp = temp-> next;
    }
    
    return stream;
}


/** 
 * Method name:     reverse 
 * Description:     Wrapper method for the private reverse method. Will call reverse if the
 *                  database has more than one record.
 */
void llist::reverse()
{
    #ifdef DEBUGMODE
        cout << "\n==============DEBUG==============\n";
        cout << "PUBLIC reverse called\n";
        cout << "==============DEBUG==============\n";
    #endif
    
    if (start-> next != NULL)
    {
        reverse(start);
    }
}

llist& llist::operator= (llist & database)
{
	*this = new llist(database);
	return *this;
}

// Private functions below
/** 
 * Method name:     reverse 
 * Description:     Recursive reverse definition. If the next value is null, it will assign that
 *                  record as start and return current.
 *                  Removes them from heap after deletion.
 * Parameters:      uaccno - account number for record(s) being deleted
 * Return:          temp    - 
 *                  current - last node in the list being reversed. 
 */
record * llist::reverse(record * current)
{
    record * temp;

    #ifdef DEBUGMODE
        cout << "\n==============DEBUG==============\n";
        cout << "PRIVATE called with params:\n";
        cout << "current: "  << current << "\n";
        cout << "==============DEBUG==============\n";
    #endif
    
    // We at the end boys
    if (current-> next == NULL)
    {
        start = current;
    }
    else
    {
        temp = reverse(current-> next);
        temp-> next = current;
        current-> next = NULL;
    }
    
    return current;
}


/** 
 * Method name:     cleanup 
 * Description:     Iterates through the list and removes all objects from the dynamic memory area (heap).
 *                  current - last node in the list being reversed. 
 */
void llist::cleanup()
{
    record * current, * temp;
    current = start;
    
    #ifdef DEBUGMODE
        cout << "\n==============DEBUG==============\n";
        cout << "cleanup called\n";
        cout << "==============DEBUG==============\n";
    #endif
    
    while (current)
    {
        temp = current-> next;
        delete current;
        current = temp;
    }
    
    delete current;
    delete temp;
}
