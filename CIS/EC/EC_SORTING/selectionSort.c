/* 
   Selection Sort

   One of the simple sorting algorithms to sort an array is selection sort.
   The list is divided in two parts: the first part is the sublist of items
   already sorted; the second part is the sublist of items to be sorted.
   It finds the smallest value in the second sublist and swaps it with the 
   value in the first position of the sublist. For a list of n elements, this
   process is repeated n - 1 times,
   
   It has O(n2) complexity.
*/

#include <stdio.h>

#define SIZE 100

void printAry      ( int ary[], int n );
void selectionSort ( int ary[], int n );

int main ( void )
{
	int listSize   = 10;
	int list[SIZE] = { 20, 30, 80, 15, 50, 10, 40, 60, 25, 70 };
	

	printAry( list, listSize );

	selectionSort ( list, listSize );

	printAry( list, listSize );
	
	return 0;
}


/*	=================================================== */
void selectionSort  (int list[ ], int size)
{
	int smallest;
	int holdData;
	int current;
	int walker;
	int last = size - 1;


	for (current = 0; current < last; current++) {
	     smallest = current;
	     for (walker = current + 1;
	              walker <= last;
	              walker++)
	         if (list[ walker ] < list[ smallest ])
	            smallest = walker;

	     // Smallest selected: exchange with current 
	     holdData        = list[ current ];
	     list[current]   = list[ smallest ];
	     list[smallest]  = holdData;
	} 

	return;
}


/* ================================= */
void printAry( int ary[], int n )
{
	int i;

	printf( "\n" );
	for( i = 0; i < n; i++ )
		printf( "%3d", ary[i] );
	printf( "\n" );

	return;
}