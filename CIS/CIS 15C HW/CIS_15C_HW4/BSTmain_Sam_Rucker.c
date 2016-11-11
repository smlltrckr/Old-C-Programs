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
/*
typedef struct
{
    DATA* pTree;
    DATA* nTree;
}TREE;
*/

void greet ();
BST_TREE* getData ();
void createTrees();
void printPhone(void*);
void printName();
void searchPhone(BST_TREE* );
void searchName();
void printIndentTrees();
int comparePhone(void*, void*);

int main(void)
{
//  Local Declarations
    BST_TREE* treeP;

//  Statements

    greet();
    treeP = getData();
    searchPhone(treeP);// pass in pointer to PhoneTree
    searchName(); //pass in pointer to nameTree

    #ifdef _MSC_VER
    printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
    #endif

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
BST_TREE* getData ()
{
//  Local Declarations
    FILE* fpInpt;
    char tempData[100];
    char tempName[75];
    char area[6];
    char num[9];
    DATA* ptrData;

    BST_TREE* phoneTree;

//  Statements
    fpInpt = fopen("agenda.txt", "r");
    if(!fpInpt)
    {
        printf("agenda.txt failed to open!");
        exit(100);
    }

    phoneTree = BST_Create(comparePhone);
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
        //insert
        BST_Insert(phoneTree, ptrData);
    }

    BST_Traverse(phoneTree, printPhone);


    return phoneTree;
}
/****************************************************************************************
TASK:   compares phone numbers to determine placement within tree
PRE :   data1 - one phone number
        data2 - another phone number
POST:   returns an integer that determines placement
****************************************************************************************/
int comparePhone(void* data1, void* data2)
{
    return strcmp(((DATA*)data1)->phone, ((DATA*)data2)->phone);
}
/****************************************************************************************
TASK:   prints the tree
PRE :   ptrPhone - pointer to node in tree
POST:   N/A
****************************************************************************************/
void printPhone(void* ptrPhone)
{
    DATA* data = (DATA*)ptrPhone;

    printf("%-16s %-40s\n", data->phone, data->name);

    return;
}
/****************************************************************************************
TASK:   searchs the tree for the requested phonenumber and prints it along with
        the name that goes with it
PRE :
POST:   N/A
****************************************************************************************/
void searchPhone(BST_TREE* treeP)
{
//  Local Declarations
    DATA* search;
    char sPhone[15];
    char* check = "(000) 000-0000";

//  Statements
    do
    {
        printf("\nPlease enter Phone number\nyou wish to search for in the form (nnn) nnn-nnnn: ");
        scanf(" %[^\n]s", sPhone);

        search = BST_Retrieve(treeP, sPhone); // returns pointer to node with requested data

        if(search == NULL)
        {
            printf("\nPhone number not found please try again.\n");
        }
        else
        {
            printf("\n%s %s\n", search->phone, search->name);
        }
    }
    while( strcmp(sPhone, check) != 0);


    return;
}
/****************************************************************************************
TASK:   searches the name tree for the requested name and prints it along with
        the phone number
PRE :
POST:   N/A
****************************************************************************************/
void searchName()
{
//  Local Declarations

//  Statements

    return;
}

