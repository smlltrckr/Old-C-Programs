/* 
   CIS 15C
   Lab 6: Sorting		   5 Points

   Insertion Sort versus Shell Sort

   Requirements:
		1. Change the Shell Sort algorithm to keep track of the
		         - data comparisons
				 - data movements
		2. Run the program with different sizes: 10, 100, 1000, 10000, and 100000
		   and save each output at the end of the program as a comment
		3. Write a short report to explain your findings   
		4. Upload your files
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define SIZE 10
//#define SIZE 100
//#define SIZE 1000
//#define SIZE 10000
//#define SIZE 100000


void createAry     ( int ary[], int n );
void copyAry       ( int ary[], int n, int cAry[] );
void printAry      ( int ary[], int n );
void insertionSort ( int ary[], int n, long *cmpCount, long *movCount );
void shellSort     ( int ary[], int n, long *cmpCount, long *movCount );

int main ( void )
{
	long listSize   = SIZE;
	int  list[SIZE];
	int  cList[SIZE];
	long  cmpCount = 0;
	long  movCount = 0; 
	
	srand( time( NULL ) );

	createAry ( list, listSize );
	copyAry    ( list, listSize, cList);
    printAry  ( list, listSize );

	printf( "BEGIN sorting using Insertion Sort\n\n" );
	insertionSort ( list, listSize, &cmpCount, &movCount );

	printf( "\tNumber of data comparisons: %15ld\n", cmpCount );
	printf( "\t      Number of data moves: %15ld\n\n", movCount );

	printf( "END sorting using Insertion Sort\n\n" );

	printf( "BEGIN sorting using Shell Sort\n\n" );

	cmpCount = 0;
	movCount = 0;
	shellSort ( cList, listSize, &cmpCount, &movCount );

	printf( "\tNumber of data comparisons: %15ld\n", cmpCount );
	printf( "\t      Number of data moves: %15ld\n\n", movCount );


	printAry  ( list, listSize );

	system("pause");
    	
	return 0;
}

/* ================================================================== */
void insertionSort ( int ary[], int n, long *cmpCount, long *movCount )
{
	int current;
	int walk;
	int temp;

	for( current = 1; current < n; current++ )
	{
		temp = ary[current];
		(*movCount)++;
		walk = current - 1;		
		while( walk >= 0 && ( (*cmpCount)++ , temp < ary[walk] ) )
		{
			ary[walk + 1] = ary[walk];
			(*movCount)++;
			walk--;
		}

		ary[walk + 1] = temp;
		(*movCount)++;
	}

	return;
}

/* ================================================================== */
void shellSort ( int ary[], int n, long *cmpCount, long *movCount)
{
	int current;
	int walk;
	int temp;
	int k;

	for( k = n / 2; k >= 1; k /= 2 )
	{
		for( current = k; current < n; current++ )
		{			
			temp = ary[current];
			(*movCount)++;
			walk = current - k;
			while( walk >= 0 && ( (*cmpCount)++ , temp < ary[walk] ) )
			{			
				ary[walk + k] = ary[walk];
				(*movCount)++;
				walk -= k;
			}
			ary[walk + k] = temp;
			(*movCount)++;
		}
	}

	return;
}

/* ================================== */
void createAry ( int ary[], int n )
{
	int i;

	for( i = 0; i < n; i++ )
		ary[i] = rand() % 999 + 1;

	return;
}

/* =========================================== */
void copyAry ( int ary[], int n, int cAry[] )
{
	int i;

	for( i = 0; i < n; i++ )
		cAry[i] = ary[i];

	return;
}

/* ================================= */
void printAry( int ary[], int n )
{
	int i;

	if( n <= 500 )
	{
		printf( "\n" );
		for( i = 0; i < n; i++ )
		{
			printf( "%4d", ary[i] );
			if( (i + 1) % 19 == 0 )
				printf( "\n" );
		}
		printf( "\n" );
	}

	return;
}
/*************************************************
==================================================
					SIZE 10
==================================================

  55 500 636 389 529 668 493 304 967 838
BEGIN sorting using Insertion Sort

        Number of data comparisons:              23
              Number of data moves:              32

END sorting using Insertion Sort

BEGIN sorting using Shell Sort

        Number of data comparisons:              27
              Number of data moves:              52


  55 304 389 493 500 529 636 668 838 967
Press any key to continue . . .
==================================================
					SIZE 100
==================================================

 476 997 365 587 409 711 791 117  43 163 292 492 170 975 427 334  16 410 975
  16 318 457 363  82 995 121 703 808 946 322 588 559 496  53 926 335 226 797
 189 572 299 247 352 789 217 936 690 914 725  30 929 132 194 864 293 247 402
 113 349 816  53 135  19 669 925 802 225  15 827 578 748 406  25 896 986 747
 112 261 561 583 431 691 476 710 567 336 779 302 642  84 631 606 343 394 307
 818 590 373 278 567
BEGIN sorting using Insertion Sort

        Number of data comparisons:            2518
              Number of data moves:            2622

END sorting using Insertion Sort

BEGIN sorting using Shell Sort

        Number of data comparisons:             924
              Number of data moves:            1483


  15  16  16  19  25  30  43  53  53  82  84 112 113 117 121 132 135 163 170
 189 194 217 225 226 247 247 261 278 292 293 299 302 307 318 322 334 335 336
 343 349 352 363 365 373 394 402 406 409 410 427 431 457 476 476 492 496 559
 561 567 567 572 578 583 587 588 590 606 631 642 669 690 691 703 710 711 725
 747 748 779 789 791 797 802 808 816 818 827 864 896 914 925 926 929 936 946
 975 975 986 995 997
Press any key to continue . . .
==================================================
					SIZE 1000
==================================================
BEGIN sorting using Insertion Sort

        Number of data comparisons:          252661
              Number of data moves:          253666

END sorting using Insertion Sort

BEGIN sorting using Shell Sort

        Number of data comparisons:           14817
              Number of data moves:           23325

Press any key to continue . . .
==================================================
					SIZE 10000
==================================================
BEGIN sorting using Insertion Sort

        Number of data comparisons:        24924039
              Number of data moves:        24934045

END sorting using Insertion Sort

BEGIN sorting using Shell Sort

        Number of data comparisons:          248123
              Number of data moves:          373174

Press any key to continue . . .
==================================================
					SIZE 100000
==================================================
BEGIN sorting using Insertion Sort

        Number of data comparisons:     -1794735161
              Number of data moves:     -1794635158

END sorting using Insertion Sort

BEGIN sorting using Shell Sort

        Number of data comparisons:         3653801
              Number of data moves:         5204172

Press any key to continue . . .
*************************************************/