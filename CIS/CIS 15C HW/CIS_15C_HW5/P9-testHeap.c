/*	This program tests the heap functions used in the
	text. It uses random numbers to build a heap.
	It then presents a menu that allows the user to
	insert to, delete from, and print the heap. The maximum
	heap size is 1023.
	   Written by:
	   Date:
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#include <stdbool.h>

#include "heapADT.h"
const int maxSize = 15;

//	Prototype Definitions
int  compare    (void* arguPtr, void* heapPtr);
char getAction  (void);
void DEBUGprintHeap (HEAP* heap, int  root, int  level);

int main (void)
{
//	Local Definitions
	HEAP* heap;
	int*  dataPtr;

	bool result;
	char action;
	int bldLooper;

//	Statements
	printf("Begin Heap Test\n");
	heap = heapCreate (maxSize, compare);
	if (!heap)
	   printf("Can't create heap in main\n"), exit (100);

	// Fill half the heap with random numbers
	for (bldLooper = 0;
	     bldLooper <= maxSize / 2 - 1;
	     bldLooper++)
	    {
	     dataPtr  = (int*)malloc(sizeof (int));
	     if (!dataPtr)
	        printf("Overflow in main\n"), exit (101);

	     *dataPtr = rand() % 999 + 1;
	     heapInsert (heap, dataPtr);
	    } // for
	printf("\nEnd of heap creation\n\n");

	DEBUGprintHeap (heap, 0, 0);


	// List built. Test by inserting & deleting data
	do
	    {
	    action = getAction ();
	    switch (action)
	       {
	        case 'I':
	           dataPtr = (int*)malloc(sizeof (int*));
	           if (!dataPtr)
	               printf("Out of memory on insert\n"), exit(200);
	           printf("Enter an integer: ");
	           scanf ("%d", dataPtr);
	           result = heapInsert (heap, dataPtr);
	           if (result)
	               printf("%d inserted\n", *dataPtr);
	           else
	               printf("Heap full on insert\a\n"), exit(201);
	           break; // case I

	         case 'D':
	            result = heapDelete (heap, (void*)&dataPtr);
	            if (result)
	                printf("%d deleted.\n", *dataPtr);
	            else
	                  printf("Heap Empty. No delete\a\n");
	            break;  // case D
	        case 'P':
	            DEBUGprintHeap (heap, 0, 0);
	            break;
	       	case 'U':
	       	    printf("Number of elements in heap: %3d\n",
	       	            heapCount (heap));
	       	    if (heapFull(heap))
	       	        printf("Heap is FULL\n");
	       	    else
	       	        printf("Head is NOT full\n");
	       	    if (heapEmpty(heap))
	       	        printf("Heap is EMPTY\n");
	       	    else
	       	        printf("Head is NOT emtpy\n");
	       	    break;
	        case 'Q': break;
	        default :
	            printf ("Impossible error 100.\a\a\n");
	           exit   (100);
	       } // switch
	} while (action != 'Q');
    //heapDestroy (heap);
	printf("End of Heap Test\n");
	return 0;
}	// main

/*	================== compare =================
	This function compares two integers identified
	by pointers to integers.
	   Pre    arguPtr and listPtr are pointers to DATA
	   Return -1: arg1 value <  arg2
	          -0: arg1 value == arg2
	          +1: arg1 value >  arg2
*/
int compare (void* arg1, void* arg2)
{
//	Local Declarations
	int arguOne;
	int arguTwo;

//	Statements
	arguOne = *(int*)arg1;
	arguTwo = *(int*)arg2;

	if (arguOne < arguTwo)
	    return -1;
	else if (arguOne == arguTwo)
	    return  0;
	else
	    return +1;
}	// compare

/*	================== getAction ==================
	Get and return a valid action from keyboard.
	   Pre  nothing
	   Post valid action read and returned
*/
char getAction (void)
{
//	Local Definitions
	char action;

	int  OK = 0;

//	Statements
	do
	   {
	    printf("\nPlease enter action <P, I, D, U, Q>: ");
	    scanf (" %c", &action);
	    action = toupper(action);
	    switch (action)
	       {
	        case 'P':
	        case 'I':
	        case 'D':
	       	case 'U':
	        case 'Q': OK = 1;
	                  break;
	        default:
	          printf("< %c> action invalid: ", action);
	          printf("Please re-enter\a\a\n");
	          break;
	       } // switch
	   } while (!OK);
	return action;
}	// getAction

/*************************************************************
  Special function to print heap for debugging
*/
/*	=================== DEBUGprintHeap ==================
	Print the heap. It is used only to verify that
	the heap is valid.

	   Pre  heap is pointer to a valid heap structure
	        root is top of a tree or subtree
	        heapLast is index to last node in tree
	        level is level number of current root
	   Post contents of heap array printed
*/
void DEBUGprintHeap (HEAP* heap, int  root, int  level)
{
//	Local Definitions
	int child;
	int i;

//	Statements
	if (root <= heap->last)
	  {
	   child = (root * 2 + 1);
	   DEBUGprintHeap (heap, child + 1, level + 1);

	   for (i = 0; i < level; i ++)
	       printf("    ");
	   printf("%4d\n", *(int*)heap->heapAry[root]);

	   DEBUGprintHeap (heap, child, level + 1);
	  }
}	// printHeap


/*	Results: (After heap automatically generated)

Begin Heap Test
array size is 15
End of heap creation

          34
     633
         124
 855
          83
     764
         533

Please enter action <P, I, D, U, Q>: u
Number of elements in heap:   7
Head is NOT full
Head is NOT emtpy

Please enter action <P, I, D, U, Q>: */
