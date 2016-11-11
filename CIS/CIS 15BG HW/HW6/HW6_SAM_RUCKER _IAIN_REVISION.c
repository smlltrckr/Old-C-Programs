/************************************************************************
Homework 6
Linked Lists

Written By: Sam Rucker
Date......: 3/20/13
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

#define MEM_ERROR fprintf(stdout, "Not enough memory\n")
#define FLUSH while( getchar() != '\n' )

//  Global Declarations
enum{FALSE, TRUE};

typedef struct
{
    char pin[3];
    char* name;
    float gpa;
}STU;

typedef struct nodeTag
{
    STU stu;
    struct nodeTag* link;
}NODE;

//  Function Declarations
void greet();
NODE* insertNode (NODE*  pList, NODE*  pPre, STU  item);
NODE* deleteNode (NODE*  List,  NODE*  pPre, NODE* pCur);
int   searchList (NODE*  pList, NODE** pPre,
                  NODE** pCur,  char* target);
void  printList  (NODE*  pList);
NODE* buildList  (char*  fileID);
NODE* deleteKey  (NODE*  pList);
int   getData    (FILE*  fpData, STU* pStu);

float averageList (NODE* pList);

int main ( void )
{
//  Local Declarations
	NODE*  pList;
	NODE*  pPre;
	NODE*  pCur;
	STU   stu;
	double avrg;
	char   more;


//  Statements
    greet();
    printf("Begin list test driver\n\n");

	//	Build List
	pList = buildList("gpaDS.TXT");
	if (!pList)
    {
	    printf("Error building chron file\a\n");
	    exit  (100);
	} // if
	printList (pList);

	printf("\nInsert data tests.\n");
	printf("Enter pin:              ");
	scanf ("%s", &stu.pin);
	do
	{
	    if (searchList (pList, &pPre, &pCur, stu.pin))
	        printf("Key already in list. Not inserted\n");
	    else
	        pList = insertNode(pList, pPre, stu);
	    printf("Enter key <-1> to stop: ");
	    scanf ("%s", &stu.pin);
	} while (stu.pin != "-1");
	printList (pList);

	avrg = averageList(pList);
	printf("\nData average: %.1f\n", avrg);

	printf("\nDelete data tests.\n");
	do
	{
	    pList = deleteKey (pList);
	    printf("Delete another <Y/N>: ");
	    scanf (" %c", &more);
	} while (more == 'Y' || more == 'y');

	printList (pList);
	printf("\nTests complete.\n");

    #ifdef _MSC_VER
        printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
    #endif

    return 0;
}
void greet(void)
{
//  Local Declarations

//  Statements
    fprintf(stdout, "***************************\n");
    fprintf(stdout, "* CIS 15BG Homework 5     *\n");
    fprintf(stdout, "* Written By: Sam Rucker  *\n");
    fprintf(stdout, "* 3/14/13                 *\n");
    fprintf(stdout, "***************************\n\n");

    return;
}

/*	==================== insertNode ====================
	This function inserts a single node into a linear list.
	   Pre   pList is pointer to the list; may be null
	         pPre points to new node’s predecessor
	         item contains data to be inserted
	   Post  returns the head pointer
*/
NODE* insertNode (NODE* pList, NODE* pPre, STU item)
{
//	Local Declarations
	NODE* pNew;

//	Statements

	if (!(pNew  = (NODE*)malloc(sizeof(NODE))))
	    printf("\aMemory overflow in insert\n"), exit (100);

	pNew->stu = item;
	if (pPre == NULL)
    {
	    // Inserting before first node or to empty list
	    pNew->link  = pList;
	    pList       = pNew;
	} // if pPre
	else
	{
	    // Inserting in middle or at end
	    pNew->link = pPre->link;
	    pPre->link = pNew;
	} // else
	return pList;
}	// insertNode

/*	==================== deleteNode ====================
	This function deletes a single node from the link list.
	   Pre   pList is a pointer to the head of the list
	         pPre points to node before the delete node
	         pCur points to the node to be deleted
	   Post  deletes and recycles pCur
	         returns the head pointer
*/
NODE* deleteNode (NODE* pList, NODE* pPre, NODE* pCur)
{
//	Statements
	if (pPre == NULL)
	   // Deleting first node
	   pList = pCur->link;
	else
	   // Deleting other nodes
	   pPre->link = pCur->link;
	free  (pCur);
	return pList;
}	// deleteNode

/*	==================== searchList ====================
	Given key value, finds the location of a node
	   Pre   pList points to a head node
	         pPre points to variable to receive pred
	         pCur points to variable for current node
	         target is key being sought
	   Post  pCur points to first node with >= key
	         -or- null if target > key of last node
	         pPre points to largest node < than key
	         -or- null if target < key of first node
	         function returns true if found
	                          false if not found
*/
int searchList (NODE*  pList, NODE**   pPre,
                 NODE** pCur,  char* target)
{
//	Local Declarations
	int found = FALSE;

//	Statements
	*pPre = NULL;
	*pCur = pList;

	// start the search from beginning
	while (*pCur != NULL && target > (*pCur)->stu.pin)
	{
	    *pPre = *pCur;
	    *pCur = (*pCur)->link;
	} // while

	if (*pCur != NULL && target == (*pCur)->stu.pin)
	   found = TRUE;
	return found;
}	// searchList

/*	Traverse and print a linear list.
	   Pre   pList is a valid linear list
	   Post  List has been printed
*/
void printList (NODE* pList)
{
//	Local Declarations
	NODE* pWalker;

//	Statements
	pWalker = pList;
	printf("List contains:\n");

	while (pWalker)
	{
	    printf("%s %.1f\n", pWalker->stu.pin, pWalker->stu.pin);
	    pWalker = pWalker->link;
	} // while
	printf("\n");
	return;
} // printList

/*	This function averages the values in a linear list.
	   Pre   pList is a pointer to a linear list
	   Post  list average is returned
*/
float averageList (NODE* pList)
{
//	Local Declarations
	NODE* pWalker;
	int   total;
	int   count;

//	Statements
	total   = count = 0;
	pWalker = pList;
	while (pWalker)
	{
	    total += (int)pWalker->stu.pin;
	    count++;
	    pWalker = pWalker->link;
	} // while
	return (float)total / count;
} // averageList

/*	==================== buildList ====================
	This program builds a key-sequenced linear list.
	   Pre   fileID is file that contains data for list
	   Post  list built
	         returns pointer to head of list
*/
NODE* buildList (char* fileID)
{
//	Local Declarations
	STU  stu;
	NODE* pList;
	NODE* pPre;
	NODE* pCur;
	FILE* fpData;

//	Statements
	pList = NULL;

	fpData = fopen(fileID, "r");
	if (!fpData)
	{
	    printf("Error opening file %s\a\n", fileID);
	    exit (210);
	} // if open fail

	while (getData (fpData, &stu))
	{
	    // Determine insert position
	    searchList (pList, &pPre, &pCur, stu.pin);
	    pList = insertNode(pList, pPre, stu);
	} // while
	return pList;
} // buildList

/*	==================== deleteKey ====================
	Delete node from a linear list.
	   Pre   list is a pointer to the head of the list
	   Post  node has been deleted
	         -or- a warning message printed if not found
	         returns pointer to first node (pList)
*/

NODE* deleteKey (NODE* pList)
{
//	Local Declarations
	char*  pin;
	NODE* pCur;
	NODE* pPre;

//	Statements
	printf("Enter key of node to be deleted: ");
	scanf ("%s", &pin);

	if (!searchList(pList, &pPre, &pCur, pin))
	    printf("%s is an invalid pin\a\n", pin);
	else
	    pList = deleteNode (pList, pPre, pCur);

	return pList;
} // deleteKey

/*	==================== getData ====================
	Reads data from file.
	   Pre   fpData is an open file
	         pData is pointer to input structure
	   Post  data read
             returns success/failure
*/

int getData (FILE* fpData, STU* pStu)
{
//	Local Definitions
	int ioResult;
	char tempString[100];
    char tempName[25];
//	Statements
    pStu = (STU*)malloc(sizeof(STU));
    if(fgets(tempString, strlen(tempString) + 1, fpData ))
    {
        ioResult = 1;
    }
    //fprintf(stdout, "%s", tempString);
        sscanf(tempString,"%s %25[^;]%*s %f", &(pStu->pin), tempName, &(pStu->gpa));
        //fprintf(stdout, "%s %s %.1f",pStu->pin, pStu->name, pStu->gpa );


    //fprintf(stdout, "WORKS UP TO THIS POINT\n");

	//ioResult = fscanf (fpData, "%d", &(pData->pin));
	return ioResult == 1;
}	// getData
