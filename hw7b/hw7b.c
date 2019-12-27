/**
 * Name:        Blair Muraoka
 * Homework:    7b
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        11-05-2016
 * File:        hw7b.c
 * 
 * Description: Recursive definition of calculating the cost of painting. This includes the main function
 *              and the costofpainting function.
 */
#include <stdio.h>

int costofpainting(double);

/** 
 * Function name: costofpainting
 * Description:   Recursive function. If length is larger than 2, then the painter will divide the length
 *                into 3 equal parts and charge 100. Those 3 equal parts will be calls on costofpainting(length/3).
 *                If the length is 2 or less, the painter will charge 200. 
 * Parameters:    length   - user-inputted length of how many miles to paint
 * Return:        100 + costofpainting(length / 3) * 3 
 *                  if length >  2
 *                200   if length <= 2
 *                -1    if bad input
 */
int costofpainting(double length)
{
    double split = length / 3;
    int subtotal;
    if (length > 2)
    {
        subtotal = 100 + costofpainting(split) * 3;
    }
    else if (length < 0)
    {
        printf("bad input\n");
        subtotal =  -1;
    }
    else
    {
        subtotal = 200;
    }

    return subtotal;
}

/** 
 * Function name: main
 * Description:   Driver function. Asks user for input of a number and runs that number through the
 *                costofpainting function.
 */
int main(int argc, char * argv[])
{
    double input;
    printf("enter number of miles as a number: ");
    scanf("%lf", &input);
    int total = costofpainting(input);
    if (total != -1)
    {
        printf("Total cost for painting %lf miles: $%d\n", input, total);
    }

    return 0;
}
