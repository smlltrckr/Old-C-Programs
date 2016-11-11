/*	This program builds and prints a BST.
	   Written by: 
	   Date:       
*/
#include <stdio.h>
#include <stdlib.h>
#include "bstADT.h"

//	Prototype Declarations 
int  compareInt (void* num1, void* num2);
void printBST   (void* num1);
	
int main (void)
{
//	Local Definitions 
	BST_TREE* BSTRoot;
	int*      dataPtr;
	int       dataIn = +1;
	
//	Statements 
	printf("Begin BST Demonstation\n");

	BSTRoot = BST_Create (compareInt);

//	Build Tree 
	printf("Enter a list of positive integers;\n");
	printf("Enter a negative number to stop.\n");

	do 
	   {
	    printf("Enter a number: ");
	    scanf ("%d", &dataIn);
	    if (dataIn > -1)
	       {
	        dataPtr = (int*) malloc (sizeof (int));
	        if (!dataPtr)
	            {
	             printf("Memory Overflow in add\n"), 
	             exit(100);
	            } // if overflow 
	        *dataPtr = dataIn;
	        BST_Insert (BSTRoot, dataPtr);
	       } // valid data 
	   } while (dataIn > -1);

	printf("\nBST contains:\n");
	BST_Traverse (BSTRoot, printBST);

	printf("\nEnd BST Demonstration\n");
	return 0;
}	// main 

/*	==================== compareInt ====================  
	Compare two integers and return low, equal, high.
	    Pre  num1 and num2 are valid pointers to integers
	    Post return low (-1), equal (0), or high (+1)
*/
int compareInt (void* num1, void* num2)
{
//	Local Definitions 
    int key1 = *((int*)num1);
	int key2 = *((int*)num2);

//	Statements 
	if (key1 < key2)
	    return -1;
	if (key1 == key2)
	    return 0;
	return +1;
}	// compareInt 

/*	====================== printBST ======================  
	Print one integer from BST.
	    Pre  num1 is a pointer to an intger
	    Post integer printed and line advanced
*/
void printBST (void* num1)
{
//	Statements 
	printf("%4d\n", *((int*)num1));
	return;
}	// printBST 

/*	Results:
Begin BST Demonstation
Enter a list of positive integers;
Enter a negative number to stop.
Enter a number: 18
Enter a number: 33
Enter a number: 7
Enter a number: 24
Enter a number: 19
Enter a number: -1

BST contains:
   7
  18
  19
  24
  33

End BST Demonstration
*/