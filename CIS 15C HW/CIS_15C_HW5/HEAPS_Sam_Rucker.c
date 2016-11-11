/********************************************************************************
Homework 5 - Heaps

Project 33:	An airline company uses the formula shown below to determine the
			priority of passengers on the wating list for overbooked flights.

				priority number = A / 1000 + B - C

				where
				A is the customer's total mileage in the past year
				B is the number of years in his or her frequent flier program
				C is a sequence number representing the customer's arrival
					position when he or she booked the flight

			Given a file of overbooked customers "overbooked_customers.txt",
			write a program that reads the file and determines each
			customer's priority number. The program then builds a priority
			queue using the priority number and prints a list of waiting
			customers in priority sequence.

Written by: Sam Rucker
Date......: 6/6/13
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heapADT.h"

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

#define FLUSH while( getchar() != '\n' )

typedef struct
{
    char* name;
    long int mileageA;
    int yearsB;
    int sequenceC;
    int priority;
} CUSTOMER;

//	Function Declarations
void greet();
FILE* openInput();
CUSTOMER* getData(FILE* , char* );
int findSize(FILE* );
int getpriority(CUSTOMER* );
int prioritycmp(void* , void* );
void printPriQue(HEAP* );
void freeData(void* );

int main (void)
{
//	Local Declarations
    FILE* fpInpt;
    CUSTOMER* ptrCust;
    char tempData[100];
    HEAP* ptrHeap;
    int size;
    int success;

//	Statements
    greet();
    fpInpt = openInput();
    size = findSize(fpInpt);
    ptrHeap = heapCreate(size, prioritycmp);
    while(fgets(tempData, 100, fpInpt) != NULL)
    {
        ptrCust = getData(fpInpt, tempData);
        success = heapInsert(ptrHeap, ptrCust);
        if(!success)
        {
            printf("Insert has failed!");
            exit(103);
        }
    }
    printPriQue(ptrHeap);
    heapDestroy(ptrHeap, freeData);

#ifdef _MSC_VER
    printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
#endif

	fclose(fpInpt);

	printf("The program has finished, have a nice day!\n");

    system ("pause");

    return 0;
}
/*********************************************************************************
TASK:   Greets user
PRE:    N/A
POST:   N/A
*********************************************************************************/
void greet ()
{
//  Local Declarations

//  Statements
    printf("CIS 15C Homework 5\n");
    printf("This program is for practice with Heaps\n");
    printf("Written By: Sam Rucker\n");
    printf("Date: 6/6/13\n\n");

    return;
}// greet
/*********************************************************************************
TASK:   Opens and checks input file
PRE:    N/A
POST:   File is opened and returns pointer to file.
*********************************************************************************/
FILE* openInput()
{
//  Local Declarations
    FILE*   fpInpt;

//  Statements
    fpInpt = fopen("overbooked_customers.txt", "r");
    if(!fpInpt)
    {
        printf("Input file could not be read!\n");
        exit(100);
    }

    return fpInpt;
}// openInput
/*********************************************************************************
TASK:   gets data from file and places it into structure
PRE:    fpInpt is a pointer to the input file
        tempData[] is the data from file ready to be parsed
POST:   returns a pointer to the most resently processed customer
*********************************************************************************/

CUSTOMER* getData(FILE* fpInpt, char tempData[])
{
//  Local Declarations
    CUSTOMER* newCust;
    char tempNam[100];

//  Statements
    newCust = (CUSTOMER*)malloc(sizeof(CUSTOMER));
    if(!newCust)
    {
        printf("ptrCust failed to allocate!");
        exit(101);
    }
    sscanf(tempData,"%[^;]%*c %ld %d %d",
           tempNam, &newCust->mileageA,
           &newCust->yearsB, &newCust->sequenceC);
    newCust->name = (char*)malloc(strlen(tempNam) + 1);
    if(!newCust->name)
    {
        printf("name failed to allocate!");
        exit(102);
    }
    strcpy(newCust->name, tempNam);
    newCust->priority = getpriority(newCust);

    return newCust;
}// getData

/*********************************************************************************
TASK:   calculates a customers priority number
PRE:    newCust is a pointer to a CUSTOMER structure
POST:   returns a customers priority
*********************************************************************************/
int getpriority(CUSTOMER* newCust)
{
//  Local Declarations

//  Statements
    return (((newCust->mileageA) / 1000) + newCust->yearsB - newCust->sequenceC);
}// getpriority
/*********************************************************************************
TASK:   Compares priority numbers of customers to see who has higher priority
PRE:    cust1 pointer to one CUSTOMER structure
        cust2 pointer to a different CUSTOMER structure
POST:   if cust1 >  cust2 return +1
        if cust1 == cust2 return 0
        if cust1 <  cust2 return -1
*********************************************************************************/
int prioritycmp(void* cust1, void* cust2)
{
//  Local Declarations
    CUSTOMER c1;
    CUSTOMER c2;

//  Statements
    c1 = *(CUSTOMER*)cust1;
    c2 = *(CUSTOMER*)cust2;

    if ( c1.priority < c2.priority)
        return -1;

    if ( c1.priority == c2.priority)
        return 0;

    return +1;
}// prioritycmp

/*********************************************************************************
TASK:   Finds the size of the Priority Queue
PRE:    fpInpt is a pointer to the input file
POST:   returns size of queue
*********************************************************************************/
int findSize(FILE* fpInpt)
{
//  Local Declarations
    int size = 0;
    char temp[100];

//  Statements
    while(fgets(temp, 100 , fpInpt) != NULL)
    {
        size++;
    }
    rewind (fpInpt); // places file pointer at begininng of file

    return size;
}// findsize
/*********************************************************************************
TASK:   print the priority Queue
PRE:    ptrHeap is a pointer to the heap
POST:   N/A
*********************************************************************************/
void printPriQue(HEAP* ptrHeap)
{
//  Local Declarations
    CUSTOMER* c1;
    int count = heapCount(ptrHeap);
    int i = 0;

//  Statements
    printf("================ ====== ====== ========== ==========\n");
    printf("       NAME       MILE   YEAR   SEQUENCE   PRIORITY\n");
    printf("================ ====== ====== ========== ==========\n");
    while(i < count)
    {
        heapDelete(ptrHeap, (void**)&c1);
        printf("%-15s   %ld   %2d       %2d         %d\n", c1->name, c1->mileageA, c1->yearsB,
               c1->sequenceC, c1->priority);
		//free(c1->name);
		//free(c1);
		freeData(c1);
        i++;
    }

    return;
}// printPriQue
/*********************************************************************************
TASK:   print the priority Queue
PRE:    ptrHeap is a pointer to the heap
POST:   N/A
*********************************************************************************/
void freeData(void* dCust)
{
//	Local Declarations
	CUSTOMER* delCust = (CUSTOMER*)dCust;

//	Statements
	free(delCust->name);
	free(delCust);

	return;
}

/**********************************************************************************
Results
***********************************************************************************
CIS 15C Homework 5
This program is for practice with Heaps
Written By: Sam Rucker
Date: 6/6/13

================ ====== ====== ========== ==========
       NAME       MILE   YEAR   SEQUENCE   PRIORITY
================ ====== ====== ========== ==========
John Marcus       93000    3        3         93
Amanda Trapp      89000    3        2         90
Warren Rexroad    72000    7        5         74
Jorge Gonzales    65000    2        6         61
Bryan Devaux      53000    5        1         57
Robert D. White   63000    3       10         56
Steve Chu         42000    4        9         37
Paula Hung        34000    3        7         30
Joanne Brown      33000    2       11         24
Lou Mason         21000    6        8         19
Sarah Gilley      17000    1        4         14
No Memory Leak
The program has finished, have a nice day!

**********************************************************************************/
