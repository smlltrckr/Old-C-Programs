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
   A variation of Problem 24, page 199: Write a stack and queue test driver.
   As data, use the DATA structure defined below.


   Save the output as a comment at the end of the program!
**********************************************************
**
**  Written By: Instructor
**              Sam Rucker          // <-- write your name here
**
**  Date:       4/24/13           // <-- write the date here
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "stackADT.h"
#include "queueADT.h"

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

#define MEM_ERROR fprintf(stdout, "Not enough memory\n")
#define FLUSH while( getchar() != '\n' )

typedef struct
{
    double num;
    // more fields could be added here
}DATA;

//  Function Declarations
    void  greet(void);
    int   selection(void);
    void  validation(char answer, int* option);
    double *getData(void);
    DATA* allocData(void);
    void  printStack(STACK **stackOut);
    void  printQueue(QUEUE **queueOut);
    void  done(void);

int main( void )
{
//  Local Declarations
    STACK *stackIn, *stackOut;
    QUEUE *queueIn, *queueOut;
	DATA* pInsrt;
    int choice = 0;
    int full, empty, success;
    double* target;

//  Statements
    greet();

    stackIn = createStack();
    stackOut = createStack();
    queueIn = createQueue();
    queueOut = createQueue();

    do
    {
        choice = selection();// Selection to delete or instert data
        if(choice)
        {
            target = getData();
            full = fullStack(stackIn);//  Checks if stackIn is full
            if(!full)
            {
                success = pushStack(stackIn, target);
                full = fullQueue(queueIn);//  Checks if queueIn is full
                if(!full)
                {
                    success = enqueue(queueIn, target);
                }
                else
                    printf("queueIn is full!\n");
            }
            else
                printf("stackIn is full!\n");
        }
        else
        {
            empty = emptyStack(stackIn);// checks if stackIn is empty
            full = fullStack(stackIn);// checks if stackIn is full
            if(!empty && !full)
            {
                target = popStack(stackIn);
                success = enqueue(queueOut, target);
                success = dequeue(queueIn, &target);
                if(success)
                {
                    success = pushStack(stackOut, target);
                }
                else
                    printf("queueIn failed to delete!");
            }
            else if(full)
            {
                printf("stackOut is full!\n");
            }
            else if(empty)
            {
                printf("stackOut is empty!\n");
            }
        }
        empty = emptyStack(stackIn);
    }
    while(!empty);

    printStack(&stackOut);
    printQueue(&queueOut);
    done();

    stackIn = destroyStack(stackIn);
    stackOut = destroyStack(stackOut);
    queueIn = destroyQueue(queueIn);
    queueOut = destroyQueue(queueOut);
	
    #ifdef _MSC_VER
    printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
    #endif
	system("pause");
    return 0;
}
/***************************************************************
TASK:   Prints basic info to screen.
PRE.:   N/A
POST:   N/A
***************************************************************/
void greet(void)
{
//  Local Declarations

//  Statements
    fprintf(stdout, "\n***************************");
    fprintf(stdout, "\n* CIS 15C Homework 2      *");
    fprintf(stdout, "\n* Written By: Sam Rucker  *");
    fprintf(stdout, "\n* 4/24/13                 *");
    fprintf(stdout, "\n***************************\n\n");

    return;
}// greet

/***************************************************************
TASK:   Ask user to delete or insert
PRE.:   N/A
POST:   return 1 - Insert
        return 0 - Delete
***************************************************************/
int selection( void )
{
//  Local Declarations
    int option = 0;
    char answer;

//  Statements
    do
    {
        printf("\nOption: [I] to Insert or [D] to Delete: ");
        scanf(" %c", &answer);
		FLUSH;
		
        answer = toupper(answer);

        validation(answer, &option);
    }
    while(option != 1);

    if(answer == 'I')
    {
        return 1;
    }
    if(answer == 'D')
    {
        return 0;
    }

}// selection

/***************************************************************
TASK:   Checks if user input is valid
PRE.:   answer - passed by value
        option - passed by address
POST:   answer is validated
***************************************************************/
void validation(char answer, int* option)
{

    if(answer != 'I' && answer != 'D')
    {
            printf("\nInvalid input, please try again.\n");
    }
    else
    {
        *option = 1;
    }

    return;
}// validation

/***************************************************************
TASK:   Gets user data
PRE.:   N/A
POST:   returns target pointer to double
***************************************************************/
double* getData( void )
{
//  Local Declarations
    DATA* pInsrt;
    double* target;

//  Statements
    printf("\nPlease enter a number in the form nn.nnn: ");
    pInsrt = allocData();
    scanf("%lf", &(pInsrt->num));
    target = &(pInsrt->num);

    return target;
}// getData

/***************************************************************
TASK:   Allocates memory for DATA
PRE.:   pInsrt - pointer to struct DATA
POST:   returns pInsrt - address of Allocated Memory
***************************************************************/
DATA* allocData( void )
{
//  Local Declarations
    DATA* pInsrt;

//  Statements
    pInsrt = (DATA*)malloc(sizeof(DATA));
	if(pInsrt == NULL)
	{
		MEM_ERROR;
	}

    return pInsrt;
}// allocDATA

/***************************************************************
TASK:   Prints the Stack
PRE.:   stackOut - passed by reference
POST:   stack printed and emptyied
***************************************************************/
void printStack(STACK** stackOut)
{
//  Local Declarations
    int empty;
    double* target;

//  Statements
    empty = emptyStack(*stackOut);
    printf("\nStack Out contains: ");
    while(!empty)
    {
        target = stackTop(*stackOut);
        printf(" %lf", *target);
        target = popStack(*stackOut);
        empty = emptyStack(*stackOut);
    }
	
    return;
}// printStack

/***************************************************************
TASK:   Prints the Queue
PRE.:   queueOut - passed by reference
POST:   queue printed and emptied
***************************************************************/
void printQueue(QUEUE** queueOut)
{
//  Local Declarations
    int empty;
    int success = 0;
    double *target;

//  Statements
    empty = emptyQueue(*queueOut);
    printf("\nQueue Out contains: ");
    while(!empty)
    {
        success = dequeue(*queueOut, &target);
        if(success)
        {
			printf(" %lf", *target);
        }
        empty = emptyQueue(*queueOut);
    }
	
    return;
}// printQueue

/***************************************************************
TASK:   Says farewells
PRE.:   N/A
POST:   N/A
***************************************************************/
void done( void )
{
//  Local Declarations

//  Statements
    printf("\n\nThank you for the use of my program.\n");
    printf("Have a nice day!\n\n");

    return;
}// done
