/**
 * Name:        Blair Muraoka
 * Homework:    2b
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        09-08-2016
 * File:        hw2b-2.c
 * 
 * Description: This program contains the driver that will handle the string functions
 *              from the library.
 */
 
#include <stdio.h>

/** 
 * Function name:   main
 * Description:     Driver function. Creates a string and uses the following:
 *                  strlen(): for parameters and size of second array
 *                  strncat(): grabbing subsets of the first string and appending them
 *                  strcpy(): making copies of strings
 *                  strcat(): append a string to another
 *                  strcmp(): return 0 if the two are equal                 
 */
int main(int argc, char * argv[])
{
    char special[200] = "Narayan";
    char not_as_special[strlen(special)];
    strcpy(not_as_special, special);

    int i;
    printf("%d\n", strlen(not_as_special));
    
    /* Appends a subset of not_as_special to the special string */
    for (i = strlen(not_as_special) - 1; i > 0; i--)
    {
        strncat(special, not_as_special, i);
        printf("%s\n", special);
    }
    
    /* Copies the altered special string to a new string that is fitted for its length */
    char veryspecialstring[strlen(special)];
    strcpy(veryspecialstring, special);
    
    /* No function, just string comparing returning true or not (true) */
    if (strcmp(special, veryspecialstring) == 0)
        printf("Strings are the same. \n");
    else
        printf("Strings are not the same. \n");
    
    /* Appending a '!' to the end of new string and then strcmp again (false) */
    strcat(veryspecialstring, "!");
    
    if (strcmp(special, veryspecialstring) == 0)
        printf("Strings are the same. \n");
    else
        printf("Strings are not the same. \n");
    
    printf("%s\n", veryspecialstring);
    
    return 0;
}
