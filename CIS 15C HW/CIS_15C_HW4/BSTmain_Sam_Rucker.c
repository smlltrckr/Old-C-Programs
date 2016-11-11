/************************************************************************
BST  ADT: For this assignment you are required to use some of the
existing BST ADT functions, create other BST ADT functions(i.e. make
changes to both bstADT.c and bstADT.h), and also create application
specific functions.

Written By: Sam Rucker
Date:       5/24/13
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "bstADT.h"

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

#define FLUSH while( getchar() != '\n' )

typedef struct
{
    char phone[15];
    char* name;
} DATA;

void greet ();
void getData (BST_TREE* , BST_TREE*);
void createTrees();
void printPhone(void*);
void printName(void*);
void searchPhone(BST_TREE*);
void searchName(BST_TREE*);
void printIndentTrees();
void IndentTree();
int comparePhone(void*, void*);
int compareName(void*, void*);
void freenothing (void* dNot);
void freeData (void* dNam);

int main(void)
{
//  Local Declarations
BST_TREE* phoneTree;
    BST_TREE* nameTree;
//  Statements

    greet();
	phoneTree = BST_Create(comparePhone);
    nameTree = BST_Create(compareName);

    getData(phoneTree, nameTree);

	BST_Traverse(phoneTree, printPhone);
    searchPhone(phoneTree);

    printf("\n\n");

    BST_Traverse(nameTree, printName);
    searchName(nameTree);

	printf("\n\n");

    BST_TraverseRLN(phoneTree, IndentTree);

	BST_Destroy(nameTree, freeData);
	BST_Destroy(phoneTree, freenothing);

    #ifdef _MSC_VER
    printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
    #endif

	printf("\nThe program has ended, have a nice day!\n");

	system ("pause");

    return 0;
}

void greet()
{
//  Local Declarations

//  Statements
    printf("CIS 15C Homework 4\n");
    printf("This program is for practice Binary Search Trees.\n");
    printf("Written By: Sam Rucker\n");
    printf("Date: 5/24/13\n\n");

    return;
}
/****************************************************************************************
TASK:   reads from file and places them into a tree
PRE :   N/A
POST:   N/A
****************************************************************************************/
void getData (BST_TREE* phoneTree, BST_TREE* nameTree)
{
//  Local Declarations
    FILE* fpInpt;
    char tempData[100];
    char tempName[75];
    char area[6];
    char num[9];
    DATA* ptrData;

//  Statements
    fpInpt = fopen("agenda.txt", "r");
    if(!fpInpt)
    {
        printf("agenda.txt failed to open!");
        exit(100);
    }
    while(fgets(tempData, 100, fpInpt) != NULL)
    {
        ptrData = (DATA*)malloc(sizeof(DATA));
        if(!ptrData)
        {
            printf("ptrData failed to allocate!");
        }
        sscanf(tempData, "%s %s %[^\n]%*c",area ,num, tempName);
        strcpy(ptrData->phone, area);
        strncat(ptrData->phone, " ", 1);
        strncat(ptrData->phone, num, 8);
        ptrData->name = (char*)malloc(strlen(tempName) + 1);
        strcpy(ptrData->name, tempName);
        BST_Insert(phoneTree, ptrData);
        BST_Insert(nameTree, ptrData);
    }
	fclose(fpInpt);
    
    return;
}
/****************************************************************************************
TASK:   compares phone numbers to determine placement within tree
PRE :   data1 - one phone number
        data2 - another phone number
POST:   returns an integer that determines placement
****************************************************************************************/
int comparePhone(void* phone1, void* phone2)
{
//  Local Declarations

//  Statements
    return stricmp(((DATA*)phone1)->phone, ((DATA*)phone2)->phone);
}
/****************************************************************************************
TASK:   prints the tree
PRE :   ptrPhone - pointer to node in tree
POST:   N/A
****************************************************************************************/
int compareName(void* name1, void* name2)
{
//  Local Declarations

//  Statements
    return stricmp(((DATA*)name1)->name, ((DATA*)name2)->name);
}
/****************************************************************************************
TASK:   prints the phone tree
PRE :   ptrPhone is a pointer to the Phone tree
POST:   N/A
****************************************************************************************/
void printPhone(void* ptrPhone)
{
//  Local Declarations
    DATA* data = (DATA*)ptrPhone;

//  Statements
    printf("%-16s %-18s\n", data->phone, data->name);

    return;
}
/****************************************************************************************
TASK:   prints the name tree
PRE :   ptrPhone is a pointer to the Phone tree
POST:   N/A
****************************************************************************************/
void printName(void* ptrName)
{
//  Local Declarations
    DATA* datNam = (DATA*)ptrName;

//  Statements
    printf("%-18s %-16s\n", datNam->name, datNam->phone);

    return;
}
/****************************************************************************************
TASK:   prints indented tree
PRE :   g is pointer to DATA in heap
        lev is a counter to the level
POST:   N/A
****************************************************************************************/
void IndentTree(void* g, int lev)
{
//  Local Declarations
    DATA* iTree = (DATA*)g;
    int i;

//  Statements
    for(i = 1; i <= lev; i++)
    {
        printf("  ");
    }
    printf("%d. %-16s %-18s\n",lev , iTree->phone, iTree->name);

    return;
}
/****************************************************************************************
TASK:   searchs the tree for the requested phonenumber and prints it along with
        the name that goes with it
PRE :
POST:   N/A
****************************************************************************************/
void searchPhone(BST_TREE* phoneTree)
{
//  Local Declarations
    DATA* search;
    DATA sPhone;
    char* check = "(000) 000-0000";

//  Statements
    do
    {
        printf("\nPhone number in the form (nnn) nnn-nnnn");
        printf("\nor [(000) 000-0000] to quit: ");
        scanf(" %[^\n]%*c", sPhone.phone);

        search = BST_Retrieve(phoneTree, &sPhone); // returns pointer to node with requested data

        if(search == NULL)
        {
            printf("\nPhone number not found please try again.\n");
            printf("Make sure you use the proper format.");
        }
        else
        {
            printf("\n%s %s\n", search->phone, search->name);
        }
    }
    while( stricmp(sPhone.phone, check) != 0);

    return;
}
/****************************************************************************************
TASK:   searches the name tree for the requested name and prints it along with
        the phone number
PRE :
POST:   N/A
****************************************************************************************/
void searchName(BST_TREE* nameTree)
{
//  Local Declarations
    char temp[100];
    DATA sName;
	int exit = 1;
    char* check = "#";

//  Statements
    do
    {
        printf("\nPlease enter the Name you wish to search for");
        printf("\nor [#] to stop: ");
        scanf(" %[^\n]%*c", temp);
        sName.name = (char*)malloc(strlen(temp) + 1);
        strcpy(sName.name, temp);
		if(stricmp(sName.name, check) == 0)
				{
					exit = 0;
				}
        BST_RetrieveAll(nameTree, &sName, printName);
		
		free(sName.name);
    }
    while(exit != 0);

    return;
}
/****************************************************************************************
TASK:   frees the string and structure placed into BST
PRE :	pointer to structure
POST:   N/A
****************************************************************************************/
 void freeData(void* dNam)
 {
//	Local Declarations
	DATA* delNam = (DATA*) dNam;

//	Statements
	free(delNam->name);
	free(delNam);

	return;
 }
 /****************************************************************************************
TASK:   Fake free for BST_Destroy
PRE :	pointer to structure
POST:   N/A
****************************************************************************************/
 void freenothing (void* dNot)
 {
//	Local Declarations

//	Statements

	 return;
 }
 /****************************************************************************************
 Results
 *****************************************************************************************
 CIS 15C Homework 4
This program is for practice Binary Search Trees.
Written By: Sam Rucker
Date: 5/24/13

(408) 111-2222   Lee, Victoria
(408) 333-4444   South, Frankie
(408) 444-5555   Trapp, David
(408) 777-8888   Trapp, Ada Eve
(408) 863-0078   Brown, Joanne
(650) 222-3111   Brown, Joanne
(650) 555-6666   Marcus, Johnathan
(650) 666-7777   Walljasper, Bryan
(650) 888-9999   Andrews, Daniel
(650) 888-9999   Andrews, Daniel
(650) 999-0001   Brown, Joanne
(907) 123-4567   Lee, Marie
(907) 234-9009   White, D. Robert
(907) 543-9909   Trapp, Ada Eve

Phone number in the form (nnn) nnn-nnnn
or [(000) 000-0000] to quit: asdf

Phone number not found please try again.
Make sure you use the proper format.
Phone number in the form (nnn) nnn-nnnn
or [(000) 000-0000] to quit: (650) 555-6666

(650) 555-6666 Marcus, Johnathan

Phone number in the form (nnn) nnn-nnnn
or [(000) 000-0000] to quit: (000) 000-0000

Phone number not found please try again.
Make sure you use the proper format.

Andrews, Daniel    (650) 888-9999
Andrews, Daniel    (650) 888-9999
Brown, Joanne      (408) 863-0078
Brown, Joanne      (650) 222-3111
Brown, Joanne      (650) 999-0001
Lee, Marie         (907) 123-4567
Lee, Victoria      (408) 111-2222
Marcus, Johnathan  (650) 555-6666
South, Frankie     (408) 333-4444
Trapp, Ada Eve     (907) 543-9909
Trapp, Ada Eve     (408) 777-8888
Trapp, David       (408) 444-5555
Walljasper, Bryan  (650) 666-7777
White, D. Robert   (907) 234-9009

Please enter the Name you wish to search for
or [#] to stop: asdf

Please enter the Name you wish to search for
or [#] to stop: brown, joanne
Brown, Joanne      (408) 863-0078
Brown, Joanne      (650) 222-3111
Brown, Joanne      (650) 999-0001

Please enter the Name you wish to search for
or [#] to stop: #


      3. (907) 543-9909   Trapp, Ada Eve
        4. (907) 234-9009   White, D. Robert
    2. (907) 123-4567   Lee, Marie
            6. (650) 999-0001   Brown, Joanne
                8. (650) 888-9999   Andrews, Daniel
              7. (650) 888-9999   Andrews, Daniel
          5. (650) 666-7777   Walljasper, Bryan
        4. (650) 555-6666   Marcus, Johnathan
      3. (650) 222-3111   Brown, Joanne
  1. (408) 863-0078   Brown, Joanne
        4. (408) 777-8888   Trapp, Ada Eve
      3. (408) 444-5555   Trapp, David
    2. (408) 333-4444   South, Frankie
      3. (408) 111-2222   Lee, Victoria
No Memory Leak

The program has ended, have a nice day!

****************************************************************************************/