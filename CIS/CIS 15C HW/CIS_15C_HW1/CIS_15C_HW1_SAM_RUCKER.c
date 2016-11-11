/*********************************************************************************
** CIS 15C															  Spring, 2013
** Data Structures
******************
**
** Homework 1: Review
**        Pointers, Structures, Arrays, Linked Lists, and
**        Dynamic Allocation of Memory
**
**********************************************************************************

   This program builds and prints an array of linked list of random numbers.

   Basic Assignment:
   Write a function named split, that creates two linked list from an array made of
   linked lists:
    •	the first linked list is to contain the first node of each singly linked list
        in the array
    •	the second linked list is to contain the remaining nodes

   Advanced Assignment:
   Write a function named split, that creates two linked list from an array made of
   linked lists:
    •	the first linked list is to contain the first node of each singly linked list
        in the array
    •	the second linked list is to contain the remaining nodes

   Write (at least) two functions, including the standard documentation:
   split and freeList

   Save the output as a comment at the end of the program!
**********************************************************
**
**  Written By: Instructor
**              Sam Rucker    // <-- write your name here
**
**  Date: 4/16/13             // <-- write the date here
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SENTINEL 99999

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif
typedef struct node{
    int          data;
    struct node *link;
} NODE;

NODE **buildLkLstArray( int size );
void   printLkLstArray( NODE **list, int size );

NODE   *buildRandomList( int n );
void   printList( NODE *pList );

void split( NODE **list,int size, NODE **list1, NODE **list2 ); // must be changed
void freeList (NODE **list, NODE *list1, NODE *list2);

int main( void )
{
//  Local Definitions
    int sizeList[] = {6, 3, 2, 0, -10, 10, 5, 1, SENTINEL};
    int test = 0;
	NODE **list;
	NODE *list1;
	NODE *list2;

//  Statements
    srand( time(NULL) );
    while (sizeList[test] != SENTINEL)
    {
        list = buildLkLstArray( sizeList[test] );

        if( !list )
            printf("SIZE = %3d: Invalid!\n", sizeList[test]);
        else
        {
            printf("ORIGINAL ARRAY:\n");
            printLkLstArray( list, sizeList[test] );

            split(list, sizeList[test], &list1, &list2); // must be changed

            printf("NEW LISTS:\n\n");
            printList(list1);
            printf("\n");
            printList(list2);
        }
        freeList (list, list1, list2);
        test++;
    }

    #ifdef _MSC_VER
    printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
    #endif

    return 0;
}

/**=======================================================
   This function creates two linked list from a array made
   of linked list
     PRE:   list - to first element of the array of linked lists
            list1 - passed by address
            list2  - passed by address
            size - is the size of the array

     POST:  list1 is a pointer to a linked list made of
            the first nodes of the array of linked lists.
            list2 is a pointer to a linked list for the
            rest of the nodes
========================================================**/
void split( NODE **list, int size, NODE **list1, NODE **list2 ) // must be changed
{
    NODE *pCurr; // needed for first list
    NODE *pWalk; // needed for second list
    NODE *t1;
    NODE *t2;
    int count = 0;

        t1 = list[count];
        t2 = list[count]->link;
        pCurr = list[count];
        while(count < size - 1)
        {
            pWalk = pCurr->link;
            while(pWalk->link != NULL)
            {
                pWalk = pWalk->link;
            }
            pCurr->link = list[count  + 1];
            pCurr = pCurr->link;
            pWalk->link = pCurr->link; // appends next list
            count++;
        }
    pCurr->link = NULL; // last node in first list.
    *list1 = t1;
    *list2 = t2;
	return;
}
/*****************************************************************
This functions frees the memory of the lists
    PRE: list is a pointer to an array
         list1 is passed by address
         list2 is passed by address
*****************************************************************/
void freeList (NODE **list, NODE *list1, NODE *list2)
{
    NODE *temp;
    NODE *temp2;

    while(list1 != NULL)
    {
        temp = list1;
        list1 = list1->link;
        free(temp);
    }

    while(list2 != NULL)
    {
        temp2 = list2;
        list2 = list2->link;
        free(temp2);
    }

    free(list);
    list = NULL;

    return;
}

/** ********************************************************** */
/** INSTRUCTOR *********************************************** */
/** ********************************************************** */

/**======================================================
   This function builds an array of size linked lists,
   each containing at least 3 random numbers and not more than 12
     PRE: size - the number of linked lists

     POST: returns a pointer to first element of the array of linked lists
*/
NODE **buildLkLstArray( int size )
{
//  Local Definitions
	NODE **list = NULL;
	int    i;

//  Statements
    if ( size > 0 )
	{
	    list = (NODE **) calloc(size, sizeof(NODE *));
        if(!list)
            printf("Memory allocation error!"), exit(100);

		for( i = 0; i < size; i++ )
			list[i] = buildRandomList(3 + rand() % 10); // BASIC
			//list[i] = buildRandomList(rand() % 10); // HONORS
	}// if
	return list;
}


/* ======================================================
   This function prints an array of linked lists
     PRE:  list - to first element of the array of linked lists
     POST: lists printed
*/
void printLkLstArray( NODE **list, int size )
{
//  Local Definitions
	int i;

//  Statements
    printf("===============\nSIZE = %3d\n===================\n", size);
	for( i = 0; i < size; i++ )
	{
		printf( "LL#%2d: ", i + 1 );
		printList(list[i]);
	}
	printf("\n\n\n");

	return;
}

/* ======================================================
   This function builds a linked list of n random numbers
     PRE:  n - number of nodes
     POST: returns a pointer to the first node
*/
NODE *buildRandomList( int n )
{
//  Local Definitions
	NODE * pList;
	NODE * pNew;
    NODE * pPre;
	int    i;

//  Statements
	pList = NULL; //empty list
	if ( n > 0 )
	{
		// create the first node in the list
		pList = (NODE *) malloc(sizeof(NODE));
		if( pList == NULL )
		{
			printf( "Not enough memory\n" );
			exit(100);
		}
		pList->data = 1 + rand() % 99;
		// create the rest of the nodes
		pPre = pList;
		for( i = 1; i < n; i++ )
		{
			pNew = (NODE *) malloc(sizeof(NODE));
			if( pNew == NULL )
			{
				printf( "Not enough memory\n" );
				exit(100);
			}
			pNew->data = 1 + rand() % 99;
			pPre->link = pNew;
			pPre = pNew;
		}
		pPre->link = NULL; // set the last node's link to NULL
	}
	return pList;
}


/* ======================================================
   This function prints a linked list
     PRE:  pList - pointer to the first node in the list
     POST: list printed
*/
void printList( NODE *pList )
{
   NODE *pCurr;

   if(!pList)
      printf("Empty \n");
   else
   {
       pCurr = pList;
       while( pCurr != NULL )
       {
          printf( "%4d", pCurr->data );
          pCurr = pCurr->link;
       }
       printf("\n");
   }

   return;
}
/******************************************************************************************
RESULTS:

ORIGINAL ARRAY:
===============
SIZE =   6
===================
LL# 1:   67  21  82  59   2  16  18  21   6  77
LL# 2:   61  99  43  79  89   6  58  16
LL# 3:   38  46  12  80
LL# 4:   63   8  12  91   7  41   7  41
LL# 5:   74  83  50  60  68  52
LL# 6:   37  53  52  98  32  61  80  61  79  72



NEW LISTS:

  67  61  38  63  74  37

  21  82  59   2  16  18  21   6  77  99  43  79  89   6  58  16  46  12  80   8
  12  91   7  41   7  41  83  50  60  68  52  53  52  98  32  61  80  61  79  72

ORIGINAL ARRAY:
===============
SIZE =   3
===================
LL# 1:    1   7  44  77  38  38  76  42
LL# 2:   40  70  30  83  12  45  77  60   4  79  48
LL# 3:   71   1  69  32  68



NEW LISTS:

   1  40  71

   7  44  77  38  38  76  42  70  30  83  12  45  77  60   4  79  48   1  69  32
  68
ORIGINAL ARRAY:
===============
SIZE =   2
===================
LL# 1:   20  85  54  92  81
LL# 2:   29  30  99  30   4  81  30  55  60  68  47  46



NEW LISTS:

  20  29

  85  54  92  81  30  99  30   4  81  30  55  60  68  47  46
SIZE =   0: Invalid!
SIZE = -10: Invalid!
ORIGINAL ARRAY:
===============
SIZE =  10
===================
LL# 1:    6  88  67
LL# 2:   14  90   3
LL# 3:   38  20  59  48  24  32
LL# 4:   54  20  61  41  14  42  94
LL# 5:   28  97  22  20  45  77   1  75  68
LL# 6:   46  52  19  60  89  76  21  28  92  87  30  92
LL# 7:   38  70  73  59  83
LL# 8:   81  42  93  85  74  50  29
LL# 9:   66  66  19  91  91  68  45  11  27  94  28
LL#10:    3  61  68  28  80  48  56  95  42



NEW LISTS:

   6  14  38  54  28  46  38  81  66   3

  88  67  90   3  20  59  48  24  32  20  61  41  14  42  94  97  22  20  45  77
   1  75  68  52  19  60  89  76  21  28  92  87  30  92  70  73  59  83  42  93
  85  74  50  29  66  19  91  91  68  45  11  27  94  28  61  68  28  80  48  56
  95  42
ORIGINAL ARRAY:
===============
SIZE =   5
===================
LL# 1:   27  65  66  57  28  62  30
LL# 2:   13  18  23  56  16  75  95  54  22  35  47
LL# 3:   83  30  69  83   2  19
LL# 4:   73  23  34  85  32  72  29  39
LL# 5:   67  53  57



NEW LISTS:

  27  13  83  73  67

  65  66  57  28  62  30  18  23  56  16  75  95  54  22  35  47  30  69  83   2
  19  23  34  85  32  72  29  39  53  57
ORIGINAL ARRAY:
===============
SIZE =   1
===================
LL# 1:   41  54  56  16   6  79  45  86   4   2  70  88



NEW LISTS:

  41

  54  56  16   6  79  45  86   4   2  70  88
*******************************************************************************************/
