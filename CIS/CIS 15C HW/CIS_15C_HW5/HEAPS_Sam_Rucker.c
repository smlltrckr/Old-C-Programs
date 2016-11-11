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
	long int mileage;
	int years;
	int sequence;
}CUSTOMER;

//	Function Declarations


int main (void)
{
//	Local Declarations

//	Statements
	#ifdef _MSC_VER
    printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
    #endif

	system ("pause");

	return 0;
}
