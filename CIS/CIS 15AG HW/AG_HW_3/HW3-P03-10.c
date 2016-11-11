/**	Print rightmost digit of an integer.
	   Written by: Sam Rucker
	   Date:10/17/12

	REQUIREMENTS:
	- Write statements to calculate and display the second to the last digit of an integer
	  For instance, for 21987, the last digit is 7, the second to the last digit is 8
	- Save the new output
*/
#include <stdio.h>

int main (void)
{
//	Local Declarations
	int  intNum;
	int  secondDigit;

//	Statements
	printf  ("Enter an integral number: ");
	scanf   ("%d", &intNum);

	secondDigit = intNum / 10 % 10;
	printf  ("\nThe second to last digit is: %d", secondDigit);

	return 0;
}	// main

/***************************************************************
	Results:
Enter an integral number: 185

The right digit is: 5
*/
/***************************************************************
    New Results:
Enter an integral number: 185

The second to last digit is: 8
*/
