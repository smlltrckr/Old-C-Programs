/*********************************************************************************
** CIS 15C															  Spring, 2013
** Data Structures
******************
**
** Homework 3: Review
**        Doubly linked multilinked list - census data
**
**********************************************************************************

   Project 36, page 258

   Advanced Assignment:
        Project 36 & 37, page 258

   Save the output as a comment at the end of the program!
**********************************************************
**
**  Written By: Sam Rucker
**
**
**  Date: 5/7/13
*********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

#define FLUSH while( getchar() != '\n' )

typedef struct
{
    char *location;
    long int p1990;
    long int p2000;

}CENSUS;

typedef struct nodeTag
{
    CENSUS *ptrCensus;
    struct nodeTag *f90;
    struct nodeTag *r90;
    struct nodeTag *f00;
    struct nodeTag *r00;
}NODE;

typedef struct
{
    NODE *head;
    NODE *tail;
    int  count;
}HEADER;

//  Function Declarations
void    greet();
FILE*   openInputFile();
HEADER* AllocHeader();
void    dummyNodes(HEADER* ptrHeader);
void	readFile(FILE* fpInpt, HEADER* ptrHeader);
char*	processData(char* temp, long int* year00, long int* year90);
NODE*   buildNode();
void    insert00(HEADER* ptrHeader, NODE* ptrNode);
NODE*   search00(HEADER* ptrHeader, NODE* ptrNode);
void    insert90(HEADER* ptrHeader, NODE* ptrNode);
NODE*   search90(HEADER* ptrHeader, NODE* ptrNode);
void    printList(HEADER* ptrHeader);
void    recycle(HEADER* ptrHeader);
void	printDone();

int main( void )
{
//  Local Definitions
    FILE*    fpInpt;
    HEADER*  ptrHeader;
    long int year00, year90;
    char*    nameInpt;

//  Statements
    greet();

    fpInpt = openInputFile();
    ptrHeader = AllocHeader(); // createList()
    dummyNodes(ptrHeader);
	readFile(fpInpt, ptrHeader);
    printList(ptrHeader);
    recycle(ptrHeader);
	printDone();

    #ifdef _MSC_VER
    printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
    #endif

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
    printf("CIS 15C Homework 3\n");
    printf("This program is for practice with doubly linked multilinked lists.\n");
    printf("Written By: Sam Rucker\n");
    printf("Date: 5/7/13\n");

    return;
}// greet

/*********************************************************************************
TASK:   Opens and checks input file
PRE:    N/A
POST:   File is opened and returns pointer to file.
*********************************************************************************/
FILE* openInputFile()
{
//  Local Declarations
    FILE*   fpInpt;

//  Statements
    fpInpt = fopen("census.txt", "r");
    if(!fpInpt)
    {
        printf("Input file could not be read!\n");
        exit(100);
    }

    return fpInpt;
}// openInputFile

/*********************************************************************************
TASK:   Creates Header structure
PRE:    N/A
POST:   returns pointer to header
*********************************************************************************/
HEADER* AllocHeader()
{
//  Local Declarations
    HEADER*     pointer;

//  Statements
    pointer = (HEADER*)malloc(sizeof(HEADER));
    if(!pointer)
    {
        printf("Memory Allocation of Header failed!\n");
        exit(101);
    }
    else
    {
        pointer->head = NULL;
        pointer->tail = NULL;
		pointer->count = 0;
    }

    return pointer;
}// AllocHeader

/*********************************************************************************
TASK:   Creates two dummy nodes
PRE:    ptrHeader: pointer to header
POST:   two dummy nodes created
*********************************************************************************/
void dummyNodes(HEADER* ptrHeader)
{
//  Local Declarations

//  Statements
    ptrHeader->head = (NODE*)malloc(sizeof(NODE));
    if(!ptrHeader->head)
    {
        printf("Creation of head00 failed!\n");
        exit(102);
    }

    ptrHeader->tail = (NODE*)malloc(sizeof(NODE));
    if(!ptrHeader->tail)
    {
        printf("Creation of tail00 failed!\n");
        exit(103);
    }
	ptrHeader->tail->ptrCensus = NULL;
	ptrHeader->head->ptrCensus = NULL;
    ptrHeader->tail->f90 = NULL;
    ptrHeader->head->r90 = NULL;
    ptrHeader->tail->f00 = NULL;
    ptrHeader->head->r00 = NULL;

    ptrHeader->head->f00 = ptrHeader->tail; // correct
    ptrHeader->tail->r00 = ptrHeader->head;

    ptrHeader->head->f90 = ptrHeader->tail;
    ptrHeader->tail->r90 = ptrHeader->head;

    return;
}
/*********************************************************************************
TASK:   reads file
PRE:    fpInpt...: pointer to input file
        ptrHeader: pointer to header structure
POST:   N/A
*********************************************************************************/
void readFile(FILE* fpInpt, HEADER* ptrHeader)
{
//  Local Declarations
	CENSUS census;
	char    temp[100];
    char    remove[100];
    int     i;
	NODE *newNode;

//  Statements
    fgets(remove, 100, fpInpt);

	while (fgets(temp, 100, fpInpt) != NULL)
    {
		// insertMultiLL
		// build node
		newNode =  buildNode();
		census.location = processData(temp, &census.p2000, &census.p1990); // 
		*(newNode->ptrCensus) = census; // copys data into the node
		// insert90
		insert90(ptrHeader, newNode);
		// insert00
		insert00(ptrHeader, newNode);

		ptrHeader->count++;
    }

    return;
}
/*********************************************************************************
TASK:   processes data
PRE:    year00: population for 2000
        year90: population for 1990
		temp..: String Data from file
POST:   returns name
*********************************************************************************/
char* processData(char* temp, long int* year00, long int* year90)
{
//  Local Declarations
	CENSUS census;
    char*   name;
    char   tempNam[75];

//  Statements
 
    sscanf(temp, "%[^;]%*c %ld %ld", tempNam, year00, year90);
    name = (char*)malloc(strlen(tempNam) + 1);
    strcpy(name, tempNam);

    return name; // return census
}
/*********************************************************************************
TASK:   Allocates Memory for Node
PRE:    N/A
POST:   returns ptr to NODE
*********************************************************************************/
NODE*   buildNode(void)
{
//  Local Declarations
    NODE*   ptr;

//  Statements
    ptr = (NODE*)malloc(sizeof(NODE));
    if(!ptr)
    {
        printf("Node allocation failed!\n");
        exit(106);
    }
	// allocate here copy name and population from string to structure
	ptr->ptrCensus = (CENSUS*)malloc(sizeof(CENSUS));
	if (!(ptr->ptrCensus))
	{
		printf("Census failed to allocate");
		exit(107);
	}


    return ptr;
}
/*********************************************************************************
TASK:   inserts the node and adjusts links accordingly for 1990
PRE:    ptrNode is a pointer to Node being inserted
POST:   Node has been inserted
*********************************************************************************/
void insert90(HEADER* ptrHeader, NODE* ptrNode)
{
//  Local Declarations
    NODE* target90;

//  Statements
		target90 = search90(ptrHeader, ptrNode);
		target90->f90->r90 = ptrNode;
		ptrNode->f90 = target90->f90;
		target90->f90 = ptrNode;
		ptrNode->r90 = target90;
	
    return;
}
/*********************************************************************************
TASK:   finds where to place each node for 1990
PRE:    ptrNode is a pointer to the Node before the one we want inserted
POST:   returns pointer to node before the current one.
*********************************************************************************/
NODE* search90(HEADER* ptrHeader, NODE* ptrNode)
{
//  Local Declarations
	NODE* pCur90;

//  Statements
	pCur90 = ptrHeader->head->f90;
	while(pCur90->ptrCensus != NULL && pCur90->ptrCensus->p1990 > ptrNode->ptrCensus->p1990)
    {
        pCur90 = pCur90->f90;
    }

	return pCur90->r90;
}
/*********************************************************************************
TASK:   inserts the node and adjusts links accordingly for 2000
PRE:    ptrNode is a pointer to Node being inserted
POST:   Node has been inserted
*********************************************************************************/
void insert00(HEADER* ptrHeader, NODE* ptrNode)
{
//  Local Declarations
    NODE* target00;

//  Statements
	target00 = search00(ptrHeader, ptrNode);
	target00->f00->r00 = ptrNode;
	ptrNode->f00 = target00->f00;
	target00->f00 = ptrNode;
	ptrNode->r00 = target00;
	
    return;
}
/*********************************************************************************
TASK:   finds where to place each node for 2000
PRE:    ptrNode is a pointer to the Node before the one we want inserted
POST:   Place to insert node found
*********************************************************************************/
NODE* search00(HEADER* ptrHeader, NODE* ptrNode)
{
//  Local Declarations
    NODE* pCur00;

//  Statements
	pCur00 = ptrHeader->head->f00;
    while(pCur00->ptrCensus != NULL && pCur00->ptrCensus->p2000 > ptrNode->ptrCensus->p2000)
    {
        pCur00 = pCur00->f00;

    }

    return pCur00->r00;
}

/*********************************************************************************
TASK:   prints the multilink list forward and backward
PRE:    ptrHeader points to header structure
POST:   list printed
*********************************************************************************/
void    printList(HEADER* ptrHeader)
{
//  Local Declarations
    int count = 0;
    NODE *pForw, *pBack;
	int i;

//  Statements
    pForw = ptrHeader->head->f90;
    pBack = ptrHeader->tail->r90;
	
	for(i = 0; i < 5; i++)
	{
		printf("=");
	}

	printf("Census data for 1990");

	for(i = 0; i < 5; i++)
	{
		printf("=");
	}

	printf(" =Population= ");

	for(i = 0; i < 5; i++)
	{
		printf("=");
	}

	printf("Census data for 2000");

	for(i = 0; i < 5; i++)
	{
		printf("=");
	}

	printf(" =Population=");
	printf("\n");

	while(count < ptrHeader->count)
	{
		printf("%-31s %-12ld%-31s %-12ld\n", 
			pForw->ptrCensus->location, pForw->ptrCensus->p1990, 
			pForw->ptrCensus->location, pForw->ptrCensus->p2000);
		pForw = pForw->f90;
		count++;
	}

	for(i = 0; i < 80; i++)
	{
		printf("=");
	}

	printf("\n\n");

	while(count > 0)
	{
		printf("%-31s %-12ld%-31s %-12ld\n", 
			pBack->ptrCensus->location, pBack->ptrCensus->p1990, 
			pBack->ptrCensus->location, pBack->ptrCensus->p2000);
		pBack = pBack->r90;
		count--;
	}

    return;
}
/*********************************************************************************
TASK:   free memory
PRE:	ptrHeader : pointer to the header structure
POST:	memory is freed
*********************************************************************************/

void recycle(HEADER* ptrHeader)
{
//  Local Declarations
	int t = 0;
	NODE* pCur;
	NODE* pPre;

//  Statements
	pCur = ptrHeader->tail->r90;
	pPre = pCur;
	while(t < ptrHeader->count)
	{
		free(pCur->ptrCensus->location);
		free(pCur->ptrCensus);
		pCur = pCur->r90;
		free(pPre);
		pPre = pCur;
		t++;
	}
	free(ptrHeader->head);
	free(ptrHeader->tail);
	free (ptrHeader);

	return;
}
/*********************************************************************************
TASK:   Print done
PRE:	N/A
POST:	N/A
*********************************************************************************/
void printDone()
{
//	Local Declarations

//	Statements
	printf("\nThe program has finished, have a nice day.\n");

	return;
}
/*
Results:
printing both census data for 1990 and 2000 in parallel doesn't fit in screen
output so i fixedd that after copying results.

CIS 15C Homework 3
This program is for practice with doubly linked multilinked lists.
Written By: Sam Rucker
Date: 5/7/13
=====Census data for 1990===== =Population= =====Census data for 2000===== =Population=
New York-No. NJ                 19549649    New York-No. NJ                 21199865
Los Angeles area                14531629    Los Angeles area                16373645
Chicago area                    8239820     Chicago area                    9157540
Washington-Baltimore            6727050     Washington-Baltimore            7608070
San Francisco area              6253311     San Francisco area              7039362
Philadelphia-Atlantic City area 5892937     Philadelphia-Atlantic City area 6188463
Boston area                     5455403     Boston area                     5819100
Detroit area                    5187171     Detroit area                    5456428
Dallas-Fort Worth               4037282     Dallas-Fort Worth               5221801
Houston-Galveston area          3731131     Houston-Galveston area          4669571
Miami-Fort Lauderdale           3192582     Miami-Fort Lauderdale           3876380
Seattle area                    2970328     Seattle area                    3554760
Atlanta area                    2959950     Atlanta area                    4112198
Cleveland area                  2859644     Cleveland area                  2945831
Minneapolis-St. Paul            2538834     Minneapolis-St. Paul            2968806
San Diego area                  2498016     San Diego area                  2813833
St. Louis area                  2492525     St. Louis area                  2603607
San Juan, PR, area              2270808     San Juan, PR, area              2450292
Phoenix area                    2238480     Phoenix area                    3251876
Denver area                     1980140     Denver area                     2581506
================================================================================


Denver area                     1980140     Denver area                     2581506
Phoenix area                    2238480     Phoenix area                    3251876
San Juan, PR, area              2270808     San Juan, PR, area              2450292
St. Louis area                  2492525     St. Louis area                  2603607
San Diego area                  2498016     San Diego area                  2813833
Minneapolis-St. Paul            2538834     Minneapolis-St. Paul            2968806
Cleveland area                  2859644     Cleveland area                  2945831
Atlanta area                    2959950     Atlanta area                    4112198
Seattle area                    2970328     Seattle area                    3554760
Miami-Fort Lauderdale           3192582     Miami-Fort Lauderdale           3876380
Houston-Galveston area          3731131     Houston-Galveston area          4669571
Dallas-Fort Worth               4037282     Dallas-Fort Worth               5221801
Detroit area                    5187171     Detroit area                    5456428
Boston area                     5455403     Boston area                     5819100
Philadelphia-Atlantic City area 5892937     Philadelphia-Atlantic City area 6188463
San Francisco area              6253311     San Francisco area              7039362
Washington-Baltimore            6727050     Washington-Baltimore            7608070
Chicago area                    8239820     Chicago area                    9157540
Los Angeles area                14531629    Los Angeles area                16373645
New York-No. NJ                 19549649    New York-No. NJ                 21199865

The program has finished, have a nice day.
No Memory Leak
Press any key to continue . . .


un edited version of output

CIS 15C Homework 3
This program is for practice with doubly linked multilinked lists.
Written By: Sam Rucker
Date: 5/7/13
=====Census data for 1990===== =Population= =====Census data for 2000===== =Popu
lation=
New York-No. NJ                 19549649    New York-No. NJ                 2119
9865
Los Angeles area                14531629    Los Angeles area                1637
3645
Chicago area                    8239820     Chicago area                    9157
540
Washington-Baltimore            6727050     Washington-Baltimore            7608
070
San Francisco area              6253311     San Francisco area              7039
362
Philadelphia-Atlantic City area 5892937     Philadelphia-Atlantic City area 6188
463
Boston area                     5455403     Boston area                     5819
100
Detroit area                    5187171     Detroit area                    5456
428
Dallas-Fort Worth               4037282     Dallas-Fort Worth               5221
801
Houston-Galveston area          3731131     Houston-Galveston area          4669
571
Miami-Fort Lauderdale           3192582     Miami-Fort Lauderdale           3876
380
Seattle area                    2970328     Seattle area                    3554
760
Atlanta area                    2959950     Atlanta area                    4112
198
Cleveland area                  2859644     Cleveland area                  2945
831
Minneapolis-St. Paul            2538834     Minneapolis-St. Paul            2968
806
San Diego area                  2498016     San Diego area                  2813
833
St. Louis area                  2492525     St. Louis area                  2603
607
San Juan, PR, area              2270808     San Juan, PR, area              2450
292
Phoenix area                    2238480     Phoenix area                    3251
876
Denver area                     1980140     Denver area                     2581
506
================================================================================


Denver area                     1980140     Denver area                     2581
506
Phoenix area                    2238480     Phoenix area                    3251
876
San Juan, PR, area              2270808     San Juan, PR, area              2450
292
St. Louis area                  2492525     St. Louis area                  2603
607
San Diego area                  2498016     San Diego area                  2813
833
Minneapolis-St. Paul            2538834     Minneapolis-St. Paul            2968
806
Cleveland area                  2859644     Cleveland area                  2945
831
Atlanta area                    2959950     Atlanta area                    4112
198
Seattle area                    2970328     Seattle area                    3554
760
Miami-Fort Lauderdale           3192582     Miami-Fort Lauderdale           3876
380
Houston-Galveston area          3731131     Houston-Galveston area          4669
571
Dallas-Fort Worth               4037282     Dallas-Fort Worth               5221
801
Detroit area                    5187171     Detroit area                    5456
428
Boston area                     5455403     Boston area                     5819
100
Philadelphia-Atlantic City area 5892937     Philadelphia-Atlantic City area 6188
463
San Francisco area              6253311     San Francisco area              7039
362
Washington-Baltimore            6727050     Washington-Baltimore            7608
070
Chicago area                    8239820     Chicago area                    9157
540
Los Angeles area                14531629    Los Angeles area                1637
3645
New York-No. NJ                 19549649    New York-No. NJ                 2119
9865

The program has finished, have a nice day.
No Memory Leak
Press any key to continue . . .

*/