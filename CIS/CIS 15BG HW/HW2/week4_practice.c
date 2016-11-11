/*

  CIS 15BG
  Chapter 10: Pointer Applications

  Exercise 1: Find the largest element in a list of numbers

  Change the function to return a pointer to the largest element
  using a pointer instead of an index.

  Save the output as comment.

  Name:

  Date:

*/
#include <stdio.h>

float findLargest( float list[], int size );

int main (void)
{
//	Local Definitions
	float list[10] = { 12, 8.0, 14, 22, 20 };
    int   size = 5;
	float *largest; // index of the largest element

//	Statements

	largest = findLargest( list, size );

	printf( "The largest value is %.2f\n", *largest );
    return 0;
}

/* ======================================= */
/*  Finds the index of the largest element
    PRE: list, size
	POST: largest
*/
float findLargest( float list[], int size )
{
	float *largest;
	int i;

	largest = list;
	for( i = 1; i < size; i++ )
		if( list[i] > *largest )
			largest = list + i;

	return *largest;
}

/* =========================================
   Output

*/
