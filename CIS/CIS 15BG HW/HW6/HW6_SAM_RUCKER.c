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
#include <stdbool.h>

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

#define MEM_ERROR fprintf(stdout, "Not enough memory\n")
#define FLUSH while( getchar() != '\n' )

//  Global Declarations
typedef struct
{
    char pin[4];
    char* name;
    float gpa;
} STU;

typedef struct nodeTag
{

    STU stu;
    struct nodeTag* link;
} NODE;

//  Function Declarations
NODE* buildList  (char*  fileID, float* highestGPA);
NODE* insertNode (NODE*  pList, NODE*  pPre, STU  item);

char*  getData    (FILE*  fpData, STU* pStu);

double averageList (NODE* pList);

int   searchList (NODE*  pList, NODE** pPre,
                  NODE** pCur,  char* target);

void validateRange(float tarLow, float tarHigh);
void greet();
void printList  (NODE*  pList);
void requestedGPA (NODE* pList, float tarLow, float tarHigh);
void prntHGPAfile (NODE* pList, float highestGPA);
void recycleList (NODE* pList, STU* pStu);
void done ();


int main ( void )
{
//  Local Declarations
    NODE*  pList;
    NODE*  pPre;
    NODE*  pCur;
    STU* pStu;
    STU   stu;
    double avrg;
    char   more;
    float highestGPA;
    float tarLow, tarHigh;


//  Statements
    greet();
    fprintf(stdout, "Begin list test driver\n\n");

    //	Build List
    pList = buildList("gpaDS.TXT", &highestGPA);

    if (!pList)
    {
        fprintf(stdout, "Error building chron file\a\n");
        exit  (100);
    } // if

    printList (pList);
    prntHGPAfile(pList, highestGPA);
    avrg = averageList(pList);
    fprintf(stdout, "\nGPA average: %.1f\n", avrg);

    while(pList != NULL)
    {
        fprintf(stdout, "Enter GPA range or -1.0-1.0 to stop.");
        fprintf(stdout, "\nRange is from 0.0-4.0: ");
        scanf("%f-%f", &tarLow, &tarHigh);
        FLUSH;

        if(tarLow == -1.0 && tarHigh ==1.0)
        {
            break;
        }
        else
        {
            validateRange(tarLow, tarHigh);
            requestedGPA (pList, tarLow, tarHigh);
        }

    }

    recycleList(pList, pStu);
    fprintf(stdout, "\nTests complete.\n");
    done();

#ifdef _MSC_VER
    fprintf(stdout,  _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
#endif

    return 0;
}
/********************************************************************************
TASK: Prints basic info.
PRE.: N/A
POST: N/A
********************************************************************************/
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
}// greet

/********************************************************************************
TASK: This function inserts a single node into a linear list.
PRE.: pList is pointer to the list; may be null
      pPre points to new node’s predecessor
      item contains data to be inserted
POST: returns the head pointer
********************************************************************************/
NODE* insertNode (NODE* pList, NODE* pPre, STU item)
{
//	Local Declarations
    NODE* pNew;

//	Statements

    if (!(pNew  = (NODE*)malloc(sizeof(NODE))))
        fprintf(stdout,"\aMemory overflow in insert\n"), exit (100);

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
}// insertNode

/********************************************************************************
TASK: Given key value, finds the location of a node
PRE.: pList points to a head node
	         pPre points to variable to receive pred
	         pCur points to variable for current node
	         target is key being sought
POST: pCur points to first node with >= key
	         -or- null if target > key of last node
	         pPre points to largest node < than key
	         -or- null if target < key of first node
	         function returns true if found
	                          false if not found
********************************************************************************/
int searchList (NODE*  pList, NODE**   pPre,
                NODE** pCur,  char* target)
{
//	Local Declarations
    int found = false;

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
        found = true;

    return found;
}// searchList

/********************************************************************************
TASK: Traverse and Prints a linear list
PRE.: pList is a valid linear list
POST: List has been printed
********************************************************************************/
void printList (NODE* pList)
{
//	Local Declarations
    NODE* pWalker;

//	Statements
    pWalker = pList;
    fprintf(stdout, "List contains\n");
    fprintf(stdout, "=======  ===================   =======\n");
    fprintf(stdout, "* PIN *  *       Name      *   * GPA *\n");
    fprintf(stdout, "=======  ===================   =======\n");
    while (pWalker)
    {
        fprintf(stdout, "  %s    %-19s     %.1f\n", pWalker->stu.pin,
                pWalker->stu.name, pWalker->stu.gpa);
        pWalker = pWalker->link;
    } // while
    fprintf(stdout, "=======  ===================   =======\n");
    fprintf(stdout, "\n");

    return;
} // printList

/********************************************************************************
TASK: This function averages the values in a linear list.
PRE.: pList is a pointer to a linear list
POST: list average is returned
********************************************************************************/
double averageList (NODE* pList)
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
        total += (int)pWalker->stu.gpa;
        count++;
        pWalker = pWalker->link;
    } // while
    return (double)total / count;
} // averageList

/********************************************************************************
TASK: Traverse and Prints a linear list
PRE.: pList is a valid linear list
POST: List has been printed
********************************************************************************/
void prntHGPAfile (NODE* pList, float highestGPA)
{
//Local Declarations
    NODE* pWalker;
    FILE* fpHGPA;

//Statements
    pWalker = pList;

    fpHGPA = fopen("HIGHEST_GPA.TXT", "w");
    if(!fpHGPA)
    {
        fprintf(stdout, "Error opening file\n");
        exit (210);
    }

    fprintf(fpHGPA, "Highest GPA\n");
    fprintf(fpHGPA, "=======  ===================   =======\n");
    fprintf(fpHGPA, "* PIN *  *       Name      *   * GPA *\n");
    fprintf(fpHGPA, "=======  ===================   =======\n");
    while (pWalker)
    {
        if(pWalker->stu.gpa == highestGPA)
        {
            fprintf(fpHGPA, "  %s    %-19s     %.1f\n",
                    pWalker->stu.pin, pWalker->stu.name, pWalker->stu.gpa);
        }
        pWalker = pWalker->link;
    } // while
    fprintf(fpHGPA, "=======  ===================   =======\n");
    fprintf(stdout, "\nStudent(s) with highest GPA saved to HIGHEST_GPA.TXT\n");

    fclose(fpHGPA);

    return;
} //prntHGPAfile

/********************************************************************************
TASK: validate range entered by user
PRE.: N/A
POST: range has been validated
********************************************************************************/
void validateRange(float tarLow, float tarHigh)
{
//  Local Declarations
    int valid = 0;

//  Statements
    do
    {

        if(tarLow < tarHigh
           && (tarLow >= 0.0 && tarLow <= 4.0)
           && (tarHigh >= 0.0 && tarHigh <=4.0))
        {
            valid = 1;
        }
        else
        {
            fprintf(stdout, "Invalid GPA range!");
            fprintf(stdout, "\nMake sure format is L.L-H.H\nand range is valid: ");
            scanf("%f-%f", &tarLow, &tarHigh);
        }
    }
    while(valid != 1);

    return;
}// validateRange

/********************************************************************************
TASK: Traverse and Prints a linear list
PRE.: pList is a valid linear list
POST: List has been printed
********************************************************************************/
void requestedGPA (NODE* pList, float tarLow, float tarHigh)
{
//  Local Declarations
    NODE* pWalker;

//  Statements
    pWalker = pList;

    fprintf(stdout, "\nList of GPA's between <%.1f - %.1f>\n", tarLow, tarHigh);
    fprintf(stdout, "=======  ===================   =======\n");
    fprintf(stdout, "* PIN *  *       Name      *   * GPA *\n");
    fprintf(stdout, "=======  ===================   =======\n");
    while (pWalker)
    {
        if(pWalker->stu.gpa >= tarLow && pWalker->stu.gpa <= tarHigh)
        {
            fprintf(stdout, "  %s    %-19s     %.1f\n", pWalker->stu.pin,
                    pWalker->stu.name, pWalker->stu.gpa);

        }
        pWalker = pWalker->link;
    } // while
    fprintf(stdout, "=======  ===================   =======\n");
    fprintf(stdout, "\n");
    return;
} // requestedGPA

/********************************************************************************
TASK: This program builds a key-sequenced linear list.
PRE.: fileID is file that contains data for list
POST: list built
      returns pointer to head of list
********************************************************************************/
NODE* buildList (char* fileID, float* highestGPA)
{
//	Local Declarations
    STU  stu;
    NODE* pList;
    NODE* pPre;
    NODE* pCur;
    float tempGpa = 0.0;
    FILE* fpData;

//	Statements
    pList = NULL;

    fpData = fopen(fileID, "r");
    if (!fpData)
    {
        fprintf(stdout, "Error opening file %s\a\n", fileID);
        exit (378);
    } // if open fail

    while (getData (fpData, &stu))
    {
        if(tempGpa == 0.0)
        {
            tempGpa = stu.gpa;
        }
        else
        {
            if(tempGpa < stu.gpa)
            {
                tempGpa = stu.gpa;
            }
        }
        // Determine insert position
        searchList (pList, &pPre, &pCur, stu.pin);
        pList = insertNode(pList, pPre, stu);
    } // while
    *highestGPA = tempGpa;

    return pList;
} // buildList

/********************************************************************************
TASK: Reads from data file
PRE.: fpData is an open file
      pData is pointer to input structure
POST: data read
      returns success/failure
********************************************************************************/
char* getData (FILE* fpData, STU* pStu)
{
//	Local Definitions
    char* ioResult;
    char tempString[100];
    char tempName[25];
    char* temp;
    char* strcur;
    int i;
    int count = 0;
    int largestName;

//	Statements
    ioResult = fgets(tempString, sizeof(tempString), fpData );

    pStu->name = malloc(sizeof(char) * 25);
    if(pStu->name == NULL)
    {
        fprintf(stdout,"MEM_ERROR in getData");
    }

    if(ioResult)
    {
        sscanf(tempString,"%s %[^;]%*c %f", &(pStu->pin), pStu->name, &(pStu->gpa));
        count++;
    }

    return ioResult;
}	// getData

/********************************************************************************
TASK: Frees memory
PRE.: N/A
POST: memory has been freed
********************************************************************************/
void recycleList (NODE* pList, STU* pStu)
{
    free(pStu->name);
    free(pList);
}// recycleList

/********************************************************************************
TASK: Ending statements
PRE.: N/A
POST: N/A
********************************************************************************/
void done ()
{
    fprintf(stdout,"\nThanks you for using my program!");
    fprintf(stdout,"\nHave a great day!\n");
}// done
/********************************************************************************
RESULTS:
*********************************************************************************
***************************
* CIS 15BG Homework 5     *
* Written By: Sam Rucker  *
* 3/14/13                 *
***************************

Begin list test driver

List contains
=======  ===================   =======
* PIN *  *       Name      *   * GPA *
=======  ===================   =======
  15M    Marcus, John            3.8
  12W    White, D. Robert        3.5
  42B    Brown, Joanne           3.8
  11M    Marcus, John            3.8
  28B    Brown, Joanne           2.6
  50L    Lee, Lucy Marie         3.4
  39B    Brown, Joanne           3.5
  21A    Andrews, Dennis         2.9
  19W    Walljasper, Bryan       3.8
  35M    Marcus, John            3.2
  13S    South, Frankie          2.6
  30B    Brown, Joanne           3.8
  38L    Lee, Victor             2.6
=======  ===================   =======


Student(s) with highest GPA saved to HIGHEST_GPA.TXT

GPA average: 2.7
Enter GPA range or -1.0-1.0 to stop.
Range is from 0.0-4.0: 0-4

List of GPA's between <0.0 - 4.0>
=======  ===================   =======
* PIN *  *       Name      *   * GPA *
=======  ===================   =======
  15M    Marcus, John            3.8
  12W    White, D. Robert        3.5
  42B    Brown, Joanne           3.8
  11M    Marcus, John            3.8
  28B    Brown, Joanne           2.6
  50L    Lee, Lucy Marie         3.4
  39B    Brown, Joanne           3.5
  21A    Andrews, Dennis         2.9
  19W    Walljasper, Bryan       3.8
  35M    Marcus, John            3.2
  13S    South, Frankie          2.6
  30B    Brown, Joanne           3.8
  38L    Lee, Victor             2.6
=======  ===================   =======

Enter GPA range or -1.0-1.0 to stop.
Range is from 0.0-4.0: -1-4
Invalid GPA range!
Make sure format is L.L-H.H
and range is valid: 0-5
Invalid GPA range!
Make sure format is L.L-H.H
and range is valid: 2-3

List of GPA's between <-1.0 - 4.0>
=======  ===================   =======
* PIN *  *       Name      *   * GPA *
=======  ===================   =======
  15M    Marcus, John            3.8
  12W    White, D. Robert        3.5
  42B    Brown, Joanne           3.8
  11M    Marcus, John            3.8
  28B    Brown, Joanne           2.6
  50L    Lee, Lucy Marie         3.4
  39B    Brown, Joanne           3.5
  21A    Andrews, Dennis         2.9
  19W    Walljasper, Bryan       3.8
  35M    Marcus, John            3.2
  13S    South, Frankie          2.6
  30B    Brown, Joanne           3.8
  38L    Lee, Victor             2.6
=======  ===================   =======

Enter GPA range or -1.0-1.0 to stop.
Range is from 0.0-4.0: -1-1.0

Tests complete.

Thanks you for using my program!
Have a great day!

********************************************************************************/
