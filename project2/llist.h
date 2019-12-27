#ifndef llist_h
#define llist_h

#include <iostream>
#include "record.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class llist
{
    private:
        record *    start;
        string      filename;
        int         readfile();
        int         writefile();
        record *    reverse(record *);
        void        cleanup();
    
    public:
        llist();
        llist(string);
        llist(llist&);
        ~llist();
        int addRecord(int, string, string, int);
        int printRecord(int);
        int modifyRecord(int, string);
        void printAll();
        int deleteRecord(int);
        void reverse();
        llist& operator= (llist&);
        friend ostream& operator<< (ostream&, llist&);
};

#endif
