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
    NODE *head00;
    NODE *tail00;
    NODE *head90;
    NODE *tail90;
    int  count;
}HEADER;

//  Function Declarations
void    greet();
FILE*   openInputFile();
HEADER* AllocHeader();
void    dummyNodes(HEADER* ptrHeader);
char**  readFile(FILE* fpInpt, HEADER* ptrHeader);
char*   processData(char** table, long int* year00, long int* year90, int i);
NODE*   buildNode();
CENSUS* allocCensus();
void    insert00(HEADER* ptrHeader, NODE* ptrNode);
NODE*   search00(HEADER* ptrHeader, NODE* ptrNode);
void    insert90(HEADER* ptrHeader, NODE* ptrNode);
NODE*   search90(HEADER* ptrHeader, NODE* ptrNode);
void    printList(HEADER* ptrHeader);
void    recycle(HEADER* prtHeader, NODE* ptrNODE, char** table);

int main( void )
{
//  Local Definitions
    FILE*    fpInpt;
    HEADER*  ptrHeader;
    char**   table;
    int      i = 0;
    long int year00, year90;
    char*    nameInpt;
    NODE*    ptrNode;

//  Statements
    greet();

    fpInpt = openInputFile();
    ptrHeader = AllocHeader(); // createList()
    dummyNodes(ptrHeader);
    table = readFile(fpInpt, ptrHeader);
    while(i < ptrHeader->count)
    {
        nameInpt = processData(table, &year00, &year90, i);
        ptrNode = buildNode();
        ptrNode->ptrCensus = allocCensus();
        ptrNode->ptrCensus->location = nameInpt;
        ptrNode->ptrCensus->p1990 = year90;
        ptrNode->ptrCensus->p2000 = year00;

        insert90(ptrHeader, ptrNode);
        insert00(ptrHeader, ptrNode);
            //printf("%-31s", ptrNode->ptrCensus->location);
            //printf(" %-10ld %-10ld\n", ptrNode->ptrCensus->p1990, ptrNode->ptrCensus->p2000);

        i++;
    }
    printList(ptrHeader);
    //recycle(prtHeader, ptrNODE, table);

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
        printf("Input file could not be read");
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
        printf("Memory Allocation of Header failed!");
        exit(101);
    }
    else
    {
        pointer->head00 = NULL;
        pointer->tail00 = NULL;
        pointer->head90 = NULL;
        pointer->tail90 = NULL;
    }

    return pointer;
}// AllocHeader

/*********************************************************************************
TASK:   Creates two dummy nodes
PRE:    N/A
POST:   two dummy nodes created
*********************************************************************************/
void dummyNodes(HEADER* ptrHeader)
{
//  Local Declarations

//  Statements
    ptrHeader->count = 0;

    ptrHeader->head00 = (NODE*)malloc(sizeof(NODE));
    if(!ptrHeader->head00)
    {
        printf("Creation of head00 failed!");
        exit(102);
    }

    ptrHeader->tail00 = (NODE*)malloc(sizeof(NODE));
    if(!ptrHeader->tail00)
    {
        printf("Creation of tail00 failed!");
        exit(103);
    }

    ptrHeader->tail00->f00 = NULL;
    ptrHeader->head00->r00 = NULL;
    ptrHeader->tail00->f90 = NULL;
    ptrHeader->head00->r90 = NULL;

    ptrHeader->head00->f00 = ptrHeader->tail00; // correct
    ptrHeader->tail00->r00 = ptrHeader->head00;

    ptrHeader->tail90 = ptrHeader->tail00;
    ptrHeader->head90 = ptrHeader->head00;

    ptrHeader->head90->f90 = ptrHeader->tail90;
    ptrHeader->tail90->r90 = ptrHeader->head90;

    return;
}
/*********************************************************************************
TASK:   reads file
PRE:    fpInpt...: pointer to input file
        ptrHeader: pointer to header structure
POST:   returns table
*********************************************************************************/
char** readFile(FILE* fpInpt, HEADER* ptrHeader)
{
//  Local Declarations
    char**  table;
    char    temp[1000][1000];
    char    remove[100];
    int     j = 0;
    int     i;

//  Statements
    fgets(remove, 100, fpInpt);

    while (fgets(temp[j], 1000, fpInpt) != NULL)
    {
        j++;
    }
    ptrHeader->count += j;

    table = (char**)malloc((ptrHeader->count + 1) * sizeof(char*));
    if(!table)
    {
        printf("table Allocation Failed!");
        exit(104);
    }

    for(i = 0; i < (ptrHeader->count); i++)
    {
        table[i] = (char*)malloc( (strlen(temp[i]) * sizeof(char)) + 1 );
        if(!table[i])
        {
            printf("table[i] Allocation Failed!");
            exit(105);
        }
        strcpy(table[i], temp[i]);
    }
    table[ptrHeader->count] = NULL;

    return table;
}
/*********************************************************************************
TASK:   processes data
PRE:    table.: Array of Strings
        year00: population for 2000
        year90: population for 1990
        i.....: index for table
POST:   returns name
*********************************************************************************/
char* processData(char** table, long int* year00, long int* year90, int i)
{
//  Local Declarations
    char*   name;
    char*   tempNam;

//  Statements
    tempNam = (char*)malloc(strlen(table[i]) + 1);
    sscanf(table[i], "%[^;]%*c %ld %ld", tempNam, year00, year90);
    name = (char*)malloc(strlen(tempNam) + 1);
    strcpy(name, tempNam);
    free(tempNam);

    return name;
}
/*********************************************************************************
TASK:   Allocates Memory for Node
PRE:    N/A
POST:   returns ptr to NODE
*********************************************************************************/
NODE*   buildNode()
{
//  Local Declarations
    NODE*   ptr;

//  Statements
    ptr = (NODE*)malloc(sizeof(NODE));
    if(!ptr)
    {
        printf("Node allocation failed!");
        exit(106);
    }

    return ptr;
}
/*********************************************************************************
TASK:   Allocates Memory for CENSUS
PRE:    N/A
POST:   returns pointer to CENSUS
*********************************************************************************/
CENSUS* allocCensus()
{
//  Local Declarations
    CENSUS* ptr;

//  Statements
    ptr = (CENSUS*)malloc(sizeof(CENSUS));
    if(!ptr)
    {
        printf("Census allocation failed!");
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

    target90->f90 = ptrNode->f90;
    ptrNode->r90 = target90->r90;
    ptrHeader->tail90->r90 = target90->r90;
    target90->f90 = ptrHeader->tail90->f90;

    return;
}
/*********************************************************************************
TASK:   finds where to place each node for 1990
PRE:    ptrNode is a pointer to the Node before the one we want inserted
POST:   Place to insert node found
*********************************************************************************/
NODE* search90(HEADER* ptrHeader, NODE* ptrNode)
{
//  Local Declarations
    NODE* pPre90;

//  Statements
    pPre90 = ptrHeader->head90;
    while(pPre90->ptrCensus->p1990 > ptrNode->ptrCensus->p1990)
    {
        pPre90 = pPre90->f90;
    }

    return pPre90;
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

    target00->f00 = ptrNode->f00;
    ptrNode->r00 = target00->r00;
    ptrHeader->tail00->r00 = target00->r00;
    target00->f00 = ptrHeader->tail00->r00;

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
    NODE* pPre00;

//  Statements
    pPre00 = ptrHeader->head00;
    while(pPre00->ptrCensus->p2000 > ptrNode->ptrCensus->p2000)
    {
        pPre00 = pPre00->f00;
    }

    return pPre00;
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
    int i;
    NODE *pForw90, *pBack90, *pForw00, *pBack00;

//  Statements
    pForw90 = ptrHeader->head90->f90;
    pBack90 = ptrHeader->tail90->r90;
    pForw00 = ptrHeader->head00->f00;
    pBack00 = ptrHeader->tail00->r00;

    while(count <= ptrHeader->count)
    {
        printf("%s\n", pForw90->ptrCensus->location);
        pForw90 = pForw90->f90;
        count++;
    }

    return;
}
/*********************************************************************************
TASK:   free memory
PRE:
POST:
*********************************************************************************/
void recycle(HEADER* prtHeader, NODE* ptrNODE, char** table)
{
//  Local Declarations

//  Statements

}
