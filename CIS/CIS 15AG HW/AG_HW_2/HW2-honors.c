/**************************************************
	This program uses variables and constants.
    It does not compile. Fix all errors, run
    the program and save its output.

	   Written by: ...
	   Date: ...
*/

#include <stdio.h>

#define UPPER =  999,999;
#define LOWER =  11,111;

int main( void )
{
//	Local Declarations
    double  price = 89.99;
    char    grade = 'B';
    int     age = 97;

//	Statements

    printf  ("Homework 2:\n\nUsing printf\n");
    printf  ("age   = %c, age\n");
    printf  ("grade = %d, grade\n");
    printf  ("price = %lf, price\n\n");

    printf  ("Using both printf and scanf\n");
    printf  ("Enter a new value for age: ");
    scanf   ("%d", &age);
    printf  ("Enter a new value for grade: ");
    scanf   ("%c", &grade);
    printf  ("Enter a new value for price: ");
    scanf   ("%lf", &price);

    printf  ("Print the new values\n");
    printf  ("age   = %c, age\n");
    printf  ("grade = %d, grade\n");
    printf  ("price = %lf, price\n");

    printf  ("\nPrinting two defined constants: UPPER and LOWER\n");
    #ifdef  UPPER
    printf  ("UPPER = %08d\n", UPPER);
    #endif
    printf  ("LOWER = %08d\n", LOWER);

	return 0;
}	//  end of main
