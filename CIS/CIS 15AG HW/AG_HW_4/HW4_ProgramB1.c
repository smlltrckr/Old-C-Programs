/***************************************************
This Program will:
1.	Prompt the user to enter a number named one
    (type long int).
2.	Read one
3.	Prompt the user to enter another named two
    (type double).
4.	Read two
5.	Display one using the following format: XXXXXXXX
6.	Display two using the following format: XXXXX.XX
7.	Calculate three (a long int) by dividing one by
    the integer part of two
8.	Display three using the following format: XXXXXXXX
9.	Display the three digits in the middle of one
    (assume the number has 5 digits)
10.	Display the smallest integer that is greater than or
    equal to two and the largest integer that is
    less than or equal to two:
         XXXXXX <= XXXXX.XX <= XXXXXX

         Written by:    Sam Rucker
         Date:          10/30/12
*****************************************************/

#include <stdio.h>
#include <math.h>

int main( void )

{
//  Local Definitions
    long int    one;
    long int    three;

    double      two;
    long int    xtwo;

    int         middig;

//  Statements
    //  Getting Data (input)
        printf  ("Please enter a five digit integer number:");
        scanf   ("%ld", &one);

        printf  ("\nPlease enter a real number:");
        scanf   ("%lf", &two);

    //  Calculations
        xtwo    =   two;
        three   =   one / xtwo;
        middig  =   one / 10 % 1000;
    //  Print Section (output)
        printf  ("\n    One   =   %8ld\n", one);
        printf  ("    Two   =   %8.2lf\n", two);
        printf  ("    Three =   %8ld\n", three);
        printf  ("    The three digits in the middle of %ld are %d\n",
                 one, middig);
        printf  ("%6.0lf <= %8.2lf <= %6.0lf\n",
                 floor( two ), two, ceil( two));

    return 0;
}

/**********************************************************************
Test 1:

Please enter a five digit integer number:12345

Please enter a real number:25.7

    One   =      12345
    Two   =      25.70
    Three =        493
    The three digits in the middle of 12345 are 234
    25 <=    25.70 <=     26

Test 2:

Please enter a five digit integer number:28280

Please enter a real number:10.5

    One   =      28280
    Two   =      10.50
    Three =       2828
    The three digits in the middle of 28280 are 828
    10 <=    10.50 <=     11

***********************************************************************/
