/*
   CIS 15BG
   Debugging Exercise 12: Dynamic Allocation of Memory

   This program uses dynamic allocation of memory to create a
   copy of an array.

   It compiles, but it gives a warning. If you ignore the warning and run the program,
   it displays the original list and then crashes.

   Use a debugger to go through the program one statement at a time, and
   fix the errors.

   Hint: There are three logical errors.

============================================================================================= */
#include <stdio.h>
#include <stdlib.h>

void createCopy ( double *pFirst, double *pLast, double *newList );
void printList ( double *pFirst, double *pLast );

int main( void )
{
   int     size = 5;
   double  ary[5] = { 2.1, 3.5, 8.7, 1.9, 5.6 };
   double  *list;

   createCopy ( ary, ary + size - 1, list );
   printList ( ary, ary + size - 1 );
   printList ( list, list + size - 1 );

   free(list);
   free(ary);

   return 0;
}

/* =================== printList  =================== */
/* This function prints an array
 	PRE: pFirst - pointer to the first element
	     pLast - pointer to the last element
	POST: list printed
*/
void printList ( double *pFirst, double *pLast )
{
   double *pWalk;

   for( pWalk = pFirst; pWalk <= pLast; pWalk++ )
   {
	   printf("%6.2f ",  *pWalk );
   }
   printf("\n\n");

   return;
}

/* =================== copyList  =================== */
/* This function creates a copy of an array
 	PRE: pFirst - pointer to the first element
	     pLast - pointer to the last element
	POST: list printed
*/
void createCopy ( double *pFirst, double *pLast, double *newList )
{
    double *pwSource;
    double *pwDest;

    newList = (double *) calloc(pLast - pFirst, sizeof(double));
    if( newList == NULL )
    {
	    printf( "Not enough memory: exit the program.\n" );
	    exit(100);
    }

    for( pwSource = pFirst, pwDest = newList; pwSource <= pLast; pwSource++, pwDest++ )
    {
	    *pwDest = *pwSource;
    }


    return;
}
