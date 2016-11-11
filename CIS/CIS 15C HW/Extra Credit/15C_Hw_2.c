/*********************************************************************************
** CIS 15C															  Spring, 2013
** Data Structures
******************
**
** Homework 2: QUEUE & STACK ADT
**
**********************************************************************************

   Your program will consist of three source files and two header files:
        15C_Hw_2.c
        queueADT.c // given
        queueADT.h // given
        stackADT.c // given
        queueADT.h // given

   Basic Assignment:
   Write a function to compare two stacks
   Write an ADT function that compares two stacks


   Save the output as a comment at the end of the program!
**********************************************************
**
**  Written By: Sam Rucker
**                        
**
**  Date: 5/24/13
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "stackADT.h"
#include "queueADT.h"

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

typedef struct
{
    double num;
    // more fields could be added here
}DATA;

DATA* getData();

int main( void )
{
	DATA* test;
	

	do{
	test = getData();
	printf("%lf", test->num);
	}while(test->num != 00.00);

    #ifdef _MSC_VER
    printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
    #endif

    return 0;
}

DATA* getData()
{
	DATA* pInsrt;
	
	pInsrt = (DATA*)malloc(sizeof(DATA));
	if(!pInsrt)
	{
		printf("pInsrt did not allocate correctly!");
		exit(100);
	}
	printf("please type in a number in the form [nnn.nnn]: ");
	scanf("%lf", &(pInsrt->num));

	return pInsrt;
}
