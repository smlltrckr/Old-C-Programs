/*	Generate a set of random numbers
	   Written by:
	   Date:

  	REQUIREMENTS:
	A.
	- Run the program
	- write the set of the random numbers that could be generated by this program

	B.
	- Generate 8 random numbers from the following set
      4 9 14 19 24 29
	- Run the program again
	- Save the output
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void)
{
//	Local Declarations
	int r1, r2, r3, r4, r5, r6, r7, r8;

//	Statements
	srand(time(NULL));
	r1 = 1 + 3 * (rand() % 10);
	r2 = 1 + 3 * (rand() % 10);
	r3 = 1 + 3 * (rand() % 10);
	r4 = 1 + 3 * (rand() % 10);
	r5 = 1 + 3 * (rand() % 10);
	r6 = 1 + 3 * (rand() % 10);
    r7 = 1 + 3 * (rand() % 10);
    r8 = 1 + 3 * (rand() % 10);

	printf("PART A\n");
	printf(" %d %d %d %d %d %d %d %d\n\n",
             r1, r2, r3, r4, r5, r6, r7, r8);
	printf("The set of the random numbers is:\n 1 to 28 \n\n\n"); // Fill in the blanks

	// ============================================
	// write your code below
	// ============================================
	printf("PART B\n");
    printf("Generate 8 random numbers from the following set:\n"
           " 4 9 14 19 24 29\n\n");

//  Local Declarations
    int rnum1, rnum2, rnum3, rnum4, rnum5, rnum6, rnum7, rnum8;

//  Statements
    srand(time(NULL));
    rnum1 = 4 + 5 * (rand() % 6);
    rnum2 = 4 + 5 * (rand() % 6);
    rnum3 = 4 + 5 * (rand() % 6);
    rnum4 = 4 + 5 * (rand() % 6);
    rnum5 = 4 + 5 * (rand() % 6);
    rnum6 = 4 + 5 * (rand() % 6);
    rnum7 = 4 + 5 * (rand() % 6);
    rnum8 = 4 + 5 * (rand() % 6);

    printf("Here are the 8 random numbers:\n %d %d %d %d %d %d %d %d",
           rnum1, rnum2, rnum3, rnum4, rnum5, rnum6, rnum7, rnum8);


	return 0;
}	// main

/**	Results:
Test 1:

PART B

Here are the 8 random numbers:
 14 14 4 24 14 14 29 24

Test 2:

PART B

Here are the 8 random numbers:
 24 14 19 19 29 9 4 19
*/
