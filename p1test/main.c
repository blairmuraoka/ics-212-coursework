#include <stdio.h>
#include <string.h>
#include "record.h"

int debugmode = 0;

int main(int argc, char * argv[])
{
    struct record * start = NULL;
    int numAccounts;  
    
    if (argc < 3)
    {
        if (argc == 2)
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
            readfile(&start, &numAccounts, "bankrecords.txt");
            menu(&start, &numAccounts);
            writefile(start, numAccounts, "bankrecords.txt");           
        }    
    }

    else
    {
        printf("ERROR: Too many arguments. Exiting program...\n");
    }    
}
