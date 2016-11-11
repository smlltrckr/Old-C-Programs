/***************************************************************
CIS 15BG Homework 5:
Structures, Strings,
Dynamic Allocation of Memory,
and Binary Search

Write a program that permits the input of the data and writes
to a file a table showing the sales for each individual during
each week along with his or her total sales. Also it prints the
total sales, the lowest and the highest value for each week,
and the total sales for the company. Write a search manager
that allows the user to enter a person’s ID, such as KEV9,
searches for the person with that ID: if found, it displays the
name and the sales in a label format (see below); if not found,
displays a message. Repeat the search until the user enters
EXIT (as an ID). Assume the input file is sorted by ID (this
means you have to use binary search)

Written By: Sam Rucker
Date......: 3/14/13
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

#define MEM_ERROR fprintf(stdout, "Not enough memory\n")
#define FLUSH while( getchar() != '\n' )

typedef struct
{
    char id[5];
    char *name;
    int *sales;
    int personTotal;
    int personLow;
    int personHigh;
} PERSON;

typedef struct
{
    int worker;
    int weeks;
    PERSON *person;
    int grandTotal;
    int *weekLow;
    int *weekHigh;
    int *weekTotal;
} HEADER;

//  Function Declarations
FILE*   openReadFile(char nameFile[]);
FILE*   openWriteFile(char nameFile[]);

HEADER* pHeadAlloc(void);
HEADER* freeHEADER(HEADER **pHead);

PERSON* personAlloc(int workers);

char*   nameAlloc(HEADER *pHead, int strCount);

int*    weekAlloc(HEADER *pHead);
int*    callocAlloc(HEADER *pHead);

void    greet(void);
void    verification(char nameFile[]);
void    getWorkerAndWeeks(FILE* fpFile, HEADER *pHead);
void    readFile(FILE* fpFile, HEADER *pHead);
void    findLowHigh(HEADER *pHead);
void    calculation(HEADER *pHead);
void    writeFile(HEADER *pHead, char nameFile[], FILE* fpOut);
void    findLongest(HEADER *pHead, int *sizeLong);
void    printScreen(HEADER *pHead);
void    searchManager(HEADER *pHead);
void    binarySearch(char iD[], HEADER *pHead);
void    printSearch(HEADER *pHead, int index);
void    sequentialSearch(char iD[], HEADER *pHead);
void    printOutputName(char nameFile[]);
void    offerReDo(char nameFile[]);
void    done(void);


int main ( void )
{
//  Local Declarations
    FILE* fpFile;
    FILE* fpOut;

    char  nameFile[25];
    char *endCheck = "END";

    HEADER *pHead;

//  Statements
    greet();

    fprintf(stdout, "Please select file to to open.\nsales or sales_2: ");
    scanf("%s", nameFile);
    FLUSH;

    do
    {
        verification(nameFile);
        fpFile = openReadFile(nameFile);
        pHead = pHeadAlloc();
        getWorkerAndWeeks(fpFile, pHead);
        readFile(fpFile, pHead);
        findLowHigh(pHead);
        calculation(pHead);
        fpOut = openWriteFile(nameFile);
        writeFile(pHead, nameFile, fpOut);
        printScreen(pHead);
        searchManager(pHead);
        pHead = freeHEADER(&pHead);
        printOutputName(nameFile);
        offerReDo(nameFile);
    }
    while(strcmp(nameFile, endCheck) != 0);

    done();

    return 0;
}// main

/***************************************************************
TASK:   Prints info to screen.
PRE.:   N/A
POST:   N/A
***************************************************************/
void greet(void)
{
//  Local Declarations

//  Statements
    fprintf(stdout, "\n***************************");
    fprintf(stdout, "\n* CIS 15BG Homework 5     *");
    fprintf(stdout, "\n* Written By: Sam Rucker  *");
    fprintf(stdout, "\n* 3/14/13                 *");
    fprintf(stdout, "\n***************************\n\n");

    return;
}// greet

/***************************************************************
TASK:   Validates file names.
PRE.:   nameFile is an array of char.
POST:   Verifies the file(s) name.
***************************************************************/
void verification(char nameFile[])
{
//  Local Declarations
    char *file = "sales";
    char *file2 = "sales_2";
    int i;
    int verif = 0;

//  Statements
    do
    {
        for(i = 0; nameFile[i]; i++)
        {
            nameFile[i] = tolower(nameFile[i]);
        }// for

        if(strcmp(file, nameFile) != 0)
        {
            if(strcmp(file2, nameFile) != 0)
            {
                fprintf(stdout, "\nPlease enter a valid file.\n");
                fprintf(stdout, "sales or sales_2: ");
                scanf("%s", nameFile);
                FLUSH;
            }// inner if
            else
            {
                verif = 1;
            }// inner else
        }// outer if
        else
        {
            verif = 1;
        }// outer else
    }// do while
    while(verif != 1)
        ;

    return;
}// verification

/***************************************************************
TASK:   Opens requested file.
PRE.:   nameFile is an array of char.
POST:   returns fpFile which is a file pointer.
***************************************************************/
FILE* openReadFile(char nameFile[])
{
//  Local Declarationss
    FILE* fpFile;
    char *strSale = "sales";

//  Statements
    if(strcmp(strSale, nameFile) == 0)
    {
        fpFile = fopen("sales.txt", "r");
        if(fpFile == NULL)
        {
            fprintf(stdout, "File could not be read.\n");
            exit(100);
        }// inner if
    }// outer if
    else
    {
        fpFile = fopen("sales_2.txt", "r");
        if(fpFile == NULL)
        {
            fprintf(stdout, "File could not be read.\n");
            exit(100);
        }// inner if
    }// outer else

    return fpFile;
}// openReadFile

/***************************************************************
TASK:   Allocates memory to pHead
PRE.:   N/A
POST:   returns pHead which is a pointer to HEADER Structure.
***************************************************************/
HEADER* pHeadAlloc(void)
{
//  Local Declarations
    HEADER *pHead;

//  Statements
    pHead = (HEADER*)calloc(1, sizeof(HEADER));
    if(pHead == NULL)
    {
        MEM_ERROR, exit(100.5);
    }// if


    return pHead;
}// pHeadAlloc

/***************************************************************
TASK:   Scans info for header
PRE.:   fpFile is a pointer to requested file
        pHead is a pointer to HEADER structure
POST:   N/A
***************************************************************/
void getWorkerAndWeeks(FILE* fpFile, HEADER *pHead)
{
//  Local Declarations
    int worker, salesWeek, i;
    PERSON *list;

//  Statements
    fscanf(fpFile, "%d %d", &worker, &salesWeek);

    list = personAlloc(worker);
    HEADER header = {worker, salesWeek, list};
    *pHead = header;

    return;
}// getWorkerAndWeeks
/***************************************************************
TASK:   Allocates memory for list
PRE.:   worker is passed by value
POST:   returns list which is a pointer to PERSON structure
***************************************************************/
PERSON* personAlloc(int worker)
{
//  Local Declarations
    PERSON *list;

//  Statements
    list =(PERSON*)calloc(worker, sizeof(PERSON));
    if(list == NULL)
    {
        MEM_ERROR, exit(103);
    }// if

    return list;
}// personAlloc

/***************************************************************
TASK:   Reads requested file
PRE.:   fpFile is a pointer to requested file
        pHead is a pointer to HEADER structure
POST:   Assigns all information from file to the structure
***************************************************************/
void readFile(FILE* fpFile, HEADER *pHead)
{
//  Local Declarations
    char temp[50];
    char weekTemp[50];
    int count = 0;
    char *loc;
    char *ptr;
    int i, j;

//  Statements
    fscanf(fpFile, "%*d %*d");

    for(i = 0; i < pHead->worker; i++)
    {
        fgets(temp, sizeof(temp), fpFile);

        ptr = temp;
        loc = strchr(temp, ' ');

        strncpy(pHead->person[i].id, temp, (loc - ptr));

        ptr += (loc - temp);
        *ptr++;
        loc = strchr(temp, ';');
        count = (loc - ptr);
    printf("%d ", count);
        pHead->person[i].name = nameAlloc(pHead, count);

        strncpy(pHead->person[i].name, ptr, (loc - ptr));

        ptr += (loc - ptr) + 2;

        pHead->person[i].sales = weekAlloc(pHead);

        for(j = 0; j < pHead->weeks; j++)
        {
            sscanf(ptr, "%d", &count);
            //printf(" count: %d", count);
            pHead->person[i].sales[j] = count;
            //printf("ptr: %c", *ptr);
            ptr += 3;
        }// inner for
    }// outer for

    return;
}// readFile
/***************************************************************
TASK:   Allocates memory for name
PRE.:   pHead is a pointer to HEADER structure
        strCount is an int
POST:   returns names which is a pointer a persons name.
***************************************************************/
char* nameAlloc(HEADER *pHead, int strCount)
{
//  Local Declarations
    char *names;

//  Statements;
    names = (char*)calloc(strCount + 1, sizeof(char));
    if(names == NULL)
    {
        MEM_ERROR, exit(101);
    }// if

    return names;
}// nameAlloc
/***************************************************************
TASK:   Allocates memory for weeks
PRE.:   pHead is a pointer to HEADER structure
POST:   returns weekSales which is a pointer to the
        sales for a week.
***************************************************************/
int* weekAlloc(HEADER *pHead)
{
//  Local Declarations
    int *weekSales;

//  Statements
    weekSales = (int*)calloc(pHead->weeks, sizeof(int));
    if(weekSales == NULL)
    {
        MEM_ERROR, exit(102);
    }// if

    return weekSales;
}// weekAlloc
/***************************************************************
TASK:   Finds the Hiest and Lowest for each week
PRE.:   pHead is a pointer to HEADER structure
POST:   N/A
***************************************************************/
void findLowHigh(HEADER *pHead)
{
//  Local Declarations
    int i, j, k;
    int tempHigh, tempLow;
    int tempWeekLow, tempWeekHigh;

//  Statements
    for(i = 0, k = 0; i < pHead->worker; i++)
    {
        tempLow = tempHigh = pHead->person[i].sales[k];
        for(j = 0; j < pHead->weeks; j++)
        {
            if(tempHigh < pHead->person[i].sales[j])
            {
                tempHigh = pHead->person[i].sales[j];
            }// inner if
            else if(tempLow > pHead->person[i].sales[j])
            {
                tempLow = pHead->person[i].sales[j];
            }// inner if
            else
            {
                ;
            }// inner else
        }// inner for
        pHead->person[i].personLow = tempLow;
        pHead->person[i].personHigh = tempHigh;
    }// outer for

    pHead->weekHigh = callocAlloc(pHead);
    pHead->weekLow = callocAlloc(pHead);

    for(i = 0, k = 0; i < pHead->weeks; i++)
    {
        tempWeekLow = tempWeekHigh = pHead->person[k].sales[k];

        for(j = 0; j < pHead->worker; j++)
        {
            if(tempWeekHigh < pHead->person[j].sales[i])
            {
                tempWeekHigh = pHead->person[j].sales[i];
            }// inner if
            else if(tempWeekLow > pHead->person[j].sales[i])
            {
                tempWeekLow = pHead->person[j].sales[i];
            }// inner if
            else
            {
                ;
            }
        }// inner for
        pHead->weekHigh[i] = tempWeekHigh;
        pHead->weekLow[i] = tempWeekLow;
    }// outer for

    return;
}// findLowHigh
/***************************************************************
TASK:   Does all calculations
PRE.:   pHead is a pointer to HEADER structure
POST:   All calculations done
***************************************************************/
void calculation(HEADER *pHead)
{
//  Local Declarations
    int i, j;
    int grandTotal = 0;
    int big, small;

//  Statements
    for(i = 0; i < pHead->worker; i++)
    {
        for(j = 0; j < pHead->weeks; j++)
        {
            pHead->person[i].personTotal += pHead->person[i].sales[j];
        }// inner for
        grandTotal += pHead->person[i].personTotal;
    }// outer for
    pHead->grandTotal = grandTotal;

    pHead->weekTotal = callocAlloc(pHead);

    for(i = 0; i < pHead->weeks; i++)
    {
        pHead->weekTotal[i] = 0;
        for(j = 0; j < pHead->worker; j++)
        {
            pHead->weekTotal[i] += pHead->person[j].sales[i];
        }// inner for
    }// outer for

    return;
}// calculation
/***************************************************************
TASK:   Allocates memory with a size of weeks.
PRE.:   pHead is a pointer to HEADER structure.
POST:   returns allocation which is a pointer to
        allocated memory.
***************************************************************/
int* callocAlloc(HEADER *pHead)
{
//  Local Declarations
    int* allocation;

//  Statements
    allocation = (int*)calloc(pHead->weeks, sizeof(int));
    if(allocation == NULL)
    {
        MEM_ERROR, exit(104);
    }// if

    return allocation;
}// callocAlloc
/***************************************************************
TASK:   Opens a file for writting.
PRE.:   nameFile is an array of char.
POST:   returns fpOut which is pointer to writting file.
***************************************************************/
FILE* openWriteFile(char nameFile[])
{
//  Local Declarations
    FILE* fpOut;
    char *temp = "_out.txt";
    char tempStr[50];

//  Statements
    strcpy(tempStr, nameFile);
    strcat(tempStr, temp);

    fpOut = fopen(tempStr, "w");
    if(fpOut == NULL)
    {
        fprintf(stdout, "Error, file was unable to write.\n");
        exit(105);
    }// if

    return fpOut;
}// openWriteFile
/***************************************************************
TASK:   Writes to writting file.
PRE.:   pHead is a pointer to HEADER structure.
        nameFile is an array of char.
        fpOut is a pointer to the Output file.
POST:   N/A
***************************************************************/
void writeFile(HEADER *pHead, char nameFile[], FILE* fpOut)
{
//  Local Declarations
    int sizeLong = 0;
    int i, j;

//  Statements
    findLongest(pHead, &sizeLong);

    fprintf(fpOut, "===========================\n");
    fprintf(fpOut, " ABC Manufacturing Company\n");
    fprintf(fpOut, "===========================\n\n");
    fprintf(fpOut, "*** Sales Table *** \n\n");

    for(i = 0; i < sizeLong; i++)
    {
        fprintf(fpOut, "=");
    }// for

    for(i = 0; i < pHead->weeks; i++)
    {
        fprintf(fpOut, " ======");
    }// for

    fprintf(fpOut, " ============\n");
    fprintf(fpOut, " %-*s", sizeLong, "Sales Person");

    for(i = 0; i < pHead->weeks; i++)
    {
        fprintf(fpOut, "Week %d ", i + 1);
    }// for
    fprintf(fpOut, "Total/Person\n");

    for(i = 0; i < sizeLong; i++)
    {
        fprintf(fpOut, "=");
    }// for

    for(i = 0; i < pHead->weeks; i++)
    {
        fprintf(fpOut, " ======");
    }// for

    fprintf(fpOut, "\n");

    for(i = 0; i < pHead->worker; i++)
    {
        fprintf(fpOut, "%-*s   ", sizeLong, pHead->person[i].name);
        for(j = 0; j < pHead->weeks; j++)
        {
            fprintf(fpOut, "%d     ", pHead->person[i].sales[j]);
        }// inner for
        fprintf(fpOut, "  %3d\n", pHead->person[i].personTotal);
    }// outer for

    for(i = 0; i < sizeLong; i++)
    {
        fprintf(fpOut, "=");
    }// for

    for(i = 0; i < pHead->weeks; i++)
    {
        fprintf(fpOut, " ======");
    }// for

    fprintf(fpOut, "\n");

    fprintf(fpOut, "%*s", sizeLong, "Total / Week:");

    for(i = 0; i < pHead->weeks; i++)
    {
        fprintf(fpOut, "   %d ", pHead->weekTotal[i]);
    }// for

    fprintf(fpOut, "\n\n%*s", sizeLong, "Low:");

    for(i = 0; i < pHead->weeks; i++)
    {
        fprintf(fpOut, "   %3d ", pHead->weekLow[i]);
    }// for

    fprintf(fpOut, "\n\n%*s", sizeLong, "High:");

    for(i = 0; i < pHead->weeks; i++)
    {
        fprintf(fpOut, "   %3d ", pHead->weekHigh[i]);
    }// for

    fprintf(fpOut, "\n\n\n\n");
    fprintf(fpOut, " *** Total Sales for company:    %d ***\n",
            pHead->grandTotal);
    fprintf(fpOut, "\n=============\n");
    fprintf(fpOut, "End of Report\n");
    fprintf(fpOut, "=============");

    return;
}// writeFile

/***************************************************************
TASK:   Finds the longest string (name).
PRE.:   pHead is a pointer to HEADER structure.
        sizeLong is passed by address.
POST:   Finds the longest string (name).
***************************************************************/
void findLongest(HEADER *pHead, int *sizeLong)
{
//  Local Declarations
    int i;
    char *temp;
    char *strCur;

//  Statements
    strCur = pHead->person[0].name;
    for(i = 1; i < pHead->worker; i++)
    {
        temp = pHead->person[i].name;
        if(strlen(strCur) < strlen(temp))
        {
            strCur = temp;
        }// inner if
    }// outer for

    *sizeLong = strlen(strCur);

    return;
}// findLongest

/***************************************************************
TASK:   Prints info to screen
PRE.:   pHead is a pointer to HEADER structure.
POST:   Prints to the screen
***************************************************************/
void printScreen(HEADER *pHead)
{
//  Local Declarations
    int sizeLong = 0;
    int i, j;

//  Statements
    findLongest(pHead, &sizeLong);
    sizeLong += 5;

    fprintf(stdout, "\n");
    for(i = 0; i < sizeLong; i++)
    {
        fprintf(stdout, "=");
    }// for

    fprintf(stdout, "\n %-*s\n", sizeLong, "Sales Person");

    for(i = 0; i < sizeLong; i++)
    {
        fprintf(stdout, "=");
    }// for

    fprintf(stdout, "\n");

    for(i = 0; i < pHead->worker; i++)
    {
        fprintf(stdout, "%s %-*s   \n", pHead->person[i].id,
                sizeLong, pHead->person[i].name);
    }// for

    for(i = 0; i < sizeLong; i++)
    {
        fprintf(stdout, "=");
    }// for

    fprintf(stdout, "\n");

    return;
}// printScreen

/***************************************************************
TASK:   Search Manager
PRE.:   pHead is a pointer to HEADER structure
POST:   N/A
***************************************************************/
void searchManager(HEADER *pHead)
{
//  Local Declarations
    int i;
    char *searchType;
    char *binary = "binary";
    char iD[5];
    char *exit = "EXIT";

//  Statements
    for(i = 0; i < (pHead->worker) - 1; i++)
    {
        if(strcmp(pHead->person[i].id, pHead->person[i + 1].id) < 0)
        {
            searchType = "binary";
        }// inner if
        else
        {
            searchType = "sequential";
            break;
        }// inner else
    }// outer for

    fprintf(stdout, "\nEnter worker ID you wish to see or EXIT to stop searching: ");
    scanf("%4s", iD);
    FLUSH;

    for(i = 0; i < 4; i++)
    {
        iD[i] = toupper(iD[i]);
    }// for

    while(strcmp(iD, exit) != 0)
    {
        if(strcmp(searchType, binary) == 0)
        {
            binarySearch(iD, pHead);
        }// inner if
        else
        {
            sequentialSearch(iD, pHead);
        }// inner else

        fprintf(stdout, "\nEnter worker ID you wish to see or EXIT to stop searching: ");
        scanf("%4s", iD);
        FLUSH;

        for(i = 0; i < 5; i++)
        {
            iD[i] = toupper(iD[i]);
        }// inner for
    }// outer while

    return;
}// searchManager

/***************************************************************
TASK:   Binary Search
PRE.:   enterId is an array of char.
        pHead is a pointer to HEADER structure
POST:   Finds the requested ID.
***************************************************************/
void binarySearch(char iD[], HEADER *pHead)
{
//  Local Declarations
    int i;
    int first = 0;
    int last = (pHead->worker) - 1;
    int mid;

//  Statements
    while(first <= last)
    {
        mid = (first + last) / 2;
        if(strcmp(iD, pHead->person[mid].id) > 0)
        {
            first = mid + 1;
        }// inner if
        else if(strcmp(iD, pHead->person[mid].id) < 0)
        {
            last = mid - 1;
        }// inner if
        else
        {
            first = last + 1;
        }// inner else
    }// outer while

    if(strcmp(iD, pHead->person[mid].id) == 0)
    {
        printSearch(pHead, mid);
    }// if
    else
    {
        fprintf(stdout, "Error, not a valid ID.\n");
    }// else

    return;
}// binarySearch

/***************************************************************
TASK:   Prints the info related to requested ID.
PRE.:   pHead is a pointer to HEADER structure.
        index is passed by value.
POST:   prints to the screen.
***************************************************************/
void printSearch(HEADER *pHead, int index)
{
//  Local Declarations
    int i;
    int weekLow[pHead->weeks];
    int weekHigh[pHead->weeks];
    int countLo, countHi;

//  Statements
    fprintf(stdout, "\nID...: %s\n", pHead->person[index].id);
    fprintf(stdout, "Name.: %s\n", pHead->person[index].name);
    fprintf(stdout, "Sales:");

    for(i = 0, countLo = 0, countHi = 0; i < pHead->weeks; i++)
    {
        fprintf(stdout, " %d", pHead->person[index].sales[i]);
        if(pHead->person[index].sales[i] == pHead->person[index].personLow)
        {
            weekLow[countLo] = i + 1;
            countLo++;
        }// inner if
        else if(pHead->person[index].sales[i] == pHead->person[index].personHigh)
        {
            weekHigh[countHi] = i + 1;
            countHi++;
        }// inner if
        else
        {
            ;
        }// inner else
    }
    fprintf(stdout, "\nLow..: %d, Weeks:", pHead->person[index].personLow);
    for(i = 0; i < countLo; i++)
    {
        fprintf(stdout, " %d", weekLow[i]);
    }// for

    fprintf(stdout, "\nHigh.: %d, Weeks:", pHead->person[index].personHigh);
    for(i = 0; i < countHi; i++)
    {
        fprintf(stdout, " %d", weekHigh[i]);
    }// for
    fprintf(stdout, "\n");

    return;
}// printSearch

/***************************************************************
TASK:   Sequential search
PRE.:   enterId is an array of char
        pHead is a pointer to HEADER structure
POST:   validates ID
***************************************************************/
void sequentialSearch(char iD[], HEADER *pHead)
{
//  Local Declarations
    int i;
    int last = (pHead->worker) - 1;

//  Statements
    i = 0;
    while(i < last && strcmp(iD, pHead->person[i].id) != 0)
    {
        i++;
    }// while

    if(strcmp(iD, pHead->person[i].id) == 0)
    {
        printSearch(pHead, i);
    }// if
    else
    {
        fprintf(stdout, "Error, not a valid ID.\n");
    }// else

    return;
}// sequentialSearch

/***************************************************************
TASK:   Free mamory from HEADER structure
PRE.:   pHead is a pointer to HEADER structure
POST:   returns NULL
***************************************************************/
HEADER* freeHEADER(HEADER **pHead)
{
//  Local Declarations
    int i, j;

//  Statements
    for(i = 0; i < (*pHead)->worker; i++)
    {
        for(j = 0; j < (*pHead)->weeks; j++)
        {
            free((*pHead)->person[i].sales + j);
            free((*pHead)->weekTotal + j);
            free((*pHead)->weekLow + j);
            free((*pHead)->weekHigh + j);
        }// inner for
        free((*pHead)->person[i].name);
        free((*pHead)->person + i);
    }// outer for
    free(pHead);


    return NULL;
}// freeHEADER

/***************************************************************
TASK:   Prints the file name that data was saved to.
PRE.:   nameFile is an array of char.
POST:   N/A
***************************************************************/
void printOutputName(char nameFile[])
{
//  Local Declarations

//  Statements
    fprintf(stdout, "\n\t\tFile saved as %s_out.txt\n", nameFile);

    return;
}// printOutputName

/***************************************************************
TASK:   Allow program to be run again.
PRE.:   nameFile is an array of char.
POST:   Program repeats or ends.
***************************************************************/
void offerReDo(char nameFile[])
{
//  Local Declarations
    int i;

//  Statements
    fprintf(stdout, "\nEnter sales or sales_2 to continue or END to quit: ");
    scanf("%s", nameFile);

    for(i = 0; i < nameFile[i]; i++)
    {
        nameFile[i] = toupper(nameFile[i]);
    }// for

    return;
}// offerReDo

/***************************************************************
TASK:   Lets user know program is done running
PRE.:   N/A
POST:   N/A
***************************************************************/
void done(void)
{
//  Local Declarations

//  Statements
    fprintf(stdout, "\nThank you for using my program!\n");
    fprintf(stdout, "Have a nice day!\n");

    return;
}// done

/***************************************************************
Results:
****************************************************************

***************************
* CIS 15BG Homework 5     *
* Written By: Sam Rucker  *
* 3/14/13                 *
***************************

Please select file to to open.
sales or sales_2: afgf

Please enter a valid file.
sales or sales_2: sales

======================
 Sales Person
======================
JOM2 Johnson, Mary
KEV9 Kelly, Victor
LAG9 Lam, Gary
NAD2 Nagasake, David
NGJ3 Nguyen, Jeff
NGM8 Nguyen, Michael
SIS7 Sinn, Scott
SMJ0 Smith, Jacob
SOT9 Son, Thai
TAM4 Tavares, Maribel
TRD2 Tran, Diane
TSA3 Tsukamoto, Andrew
WAM8 Wang, Mary
YOD6 Young, Daniel
WES9 Wells, Steve
WOS7 Wong, Justin
======================

Enter worker ID you wish to see or EXIT to stop searching: wfr4
Error, not a valid ID.

Enter worker ID you wish to see or EXIT to stop searching: wos7

ID...: WOS7
Name.: Wong, Justin
Sales: 10 15 12 16
Low..: 10, Weeks: 1
High.: 16, Weeks: 4

Enter worker ID you wish to see or EXIT to stop searching: exit

                File saved as sales_out.txt

Enter sales or sales_2 to continue or END to quit: SALES_2

======================
 Sales Person
======================
KEV9 Kelly, Victor
NAD2 Nagasake, David
SOT9 Son, Thai
NGJ3 Nguyen, Jeff
SMJ0 Smith, Jacob
TAM4 Tavares, Maribel
TRD2 Tran, Diane
NGM8 Nguyen, Michael
TSA3 Tsukamoto, Andrew
WES9 Wells, Steve
======================

Enter worker ID you wish to see or EXIT to stop searching: trd2

ID...: TRD2
Name.: Tran, Diane
Sales: 31 30 10 35 32
Low..: 10, Weeks: 3
High.: 35, Weeks: 4

Enter worker ID you wish to see or EXIT to stop searching: exit

                File saved in sales_2_out.txt

Enter sales or sales_2 to continue or END to quit: end

Thank you for using my program!
Have a nice day!

***************************************************************/
