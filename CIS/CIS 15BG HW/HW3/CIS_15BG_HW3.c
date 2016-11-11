/*********************************************************************************
** CIS 15BG															  Winter, 2013
***************
**
** Homework 3:
**        Pointers, Dynamic Allocation of Memory, Ragged Arrays, and Sorting
**
**********************************************************************************

  This program creates a dynamic table that can store a ragged 2D array
  of integers, sorts each row then rearranges them by length

****************************************
**
**  Written By: Sam Rucker
**
**  Date......: 2/12/13
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _MSC_VER
#include <crtdbg.h>
#endif

void greet      ();
int promptUser  ();
int** allocAry  (int rows);
void randGen    (int** table, int rows);
void bubbleSort (int** table, int rows);
void insertSort (int** table, int rows);
void saveTable  (int** table, int rows);
int **releaseTable(int **table);
void done       ();

int main (void)
{
    int rows;
    char yN;
    int** table;
    void* ptr;

    greet       ();

    do
    {
        rows    = promptUser  ();
        table   = allocAry    (rows);
        randGen     (table, rows);
        bubbleSort  (table, rows);
        insertSort  (table, rows);
        saveTable   (table, rows);
        releaseTable(table);
        printf      ("\nWould you like to run the program again Y/N?: ");
        scanf       (" %c", &yN);
        printf      ("\n");
    }
    while (toupper (yN) == 'Y');

    done        ();

    return 0;

}// main

/*********************************************************************************
TASK:   Displays name, date, and HW.
PRE.:
POST:
*********************************************************************************/

void greet    ()
{
//  Statements
    printf ("CIS 15BG Homework 3");
    printf ("\nWritten by: Sam Rucker");
    printf ("\nDate......: 2/12/13\n\n");

    return;
}

/*********************************************************************************
TASK:   Prompts user to enter number of rows (1-10)
PRE.:
POST:
*********************************************************************************/

int promptUser  ()
{
//  Local Declarations
    int rows;

//  Statements

    printf("Please enter a number 1-10 for the number of rows you want: ");
    scanf("%d", &rows);
    printf("\n");

    while (rows < 1 || rows > 10)
    {
        printf("Invalid number of rows. Please enter a number 1-10: ");
        scanf("%d", &rows);
    }// while

    return rows;
}

/*********************************************************************************
TASK:   Allocates memory to table.
PRE.:
POST:
*********************************************************************************/

int** allocAry    (int rows)  //calloc
{
//  Local Declarations
    int rowAry;
    int** table;
    int r;

//  Statements

    table = (int**) calloc(rows + 1, sizeof(int*));
    for(r = 0; r < rows; r++)
    {
        printf("Enter number of entries you want (1-15) in row %d: ", r + 1);
        scanf ("%d", &rowAry);
        while (rowAry < 1 || rowAry > 15)
        {
            printf ("\nInvalid enter new number between 1-15 for row %d: ",
                    r + 1);
            scanf ("%d", &rowAry);
        }// while
        table[r] = (int*)calloc(rowAry + 1, sizeof(int));
        table[r] [0] = rowAry;
    }// for

    table[r] = NULL;

    return table;
}

/*********************************************************************************
TASK:   Generates random numbers to be placed into table's memory slots.
PRE.:
POST:
*********************************************************************************/

void randGen     (int** table, int rows)
{
//  Local Declarations
    int rnd, ro, co;

//  Statements
    srand(time(NULL));

    for (ro = 0; ro < rows; ro++ )
    {
        for(co = 0; co < (table[ro][0]); co++)
        {
            rnd = (rand() % (199) - 99);
            table[ro][co + 1] = rnd;
        }// inner for
    }// for

    return;
}

/*********************************************************************************

TASK:   Sorts the random numbers inside the arrays of table.
PRE.:
POST:
*********************************************************************************/

void bubbleSort  (int** table, int rows)
{
//  Local Declarations
    int current, last, walk, temp;
    int a, b;

//  Statements
    for(a = 0; a < rows; a++)
    {
        last = table [a][0];
        for(current = 1; current < last; current++)
        {
            for(walk = last; walk > current; walk--)
            {
                if(table[a][walk] > table[a][walk - 1])
                {
                    temp = table[a][walk];
                    table[a][walk] = table[a][ walk - 1];
                    table[a][walk - 1] = temp;
                }// if
            }// inner inner for
        }// inner for
    }// for

    return;
}

/*********************************************************************************
TASK:   Sorts the pointers to arrays from one containing the most number to the
        one with the least.
PRE.:
POST:
*********************************************************************************/

void insertSort  (int** table, int rows)
{
//  Local Declarations
    int  *isTemp, isCurrent, isWalk;

//  Statement
    for(isCurrent = 1; isCurrent < rows; isCurrent++)
    {
        isTemp = table[isCurrent];
        isWalk = isCurrent - 1;
        while (isWalk >= 0 && *isTemp > *table[isWalk])
        {
            table[isWalk + 1] = table[isWalk];
            isWalk--;
        }// while
        table[isWalk + 1] = isTemp;
    }// for

    return;

}

/*********************************************************************************
TASK:   Prints sorted table to file RANDOM.TXT
PRE.:
POST:
*********************************************************************************/

void saveTable   (int** table, int rows)
{
//  Local Declarations
    FILE* fpRandomSort;
    int i, j;

//  Statements
    fpRandomSort = fopen("RANDOM.TXT", "a");

    fprintf(fpRandomSort, "%d\n", rows);
    for(i = 0; i < rows; i++)
    {
        fprintf(fpRandomSort, "%2d:", *table[i]);
        for(j = 0; j < table[i][0]; j++)
        {
            fprintf(fpRandomSort, " %d", table[i][j + 1]);
        }// inner for
        fprintf(fpRandomSort, "\n");
    }// for
    fprintf (fpRandomSort, "\n");

    fclose(fpRandomSort);

    return;
}

/*********************************************************************************
TASK:   Frees the memory.
PRE.:
POST:
*********************************************************************************/
int **releaseTable(int **table)
{
    int row;

    for( row = 0; table[row] != NULL; row++ )
    {
        free(table[row]);
    }
    free(table);
    return NULL;
}

/*********************************************************************************
TASK:   Farewell.
PRE.:
POST:
*********************************************************************************/

void done    ()
{
    printf("The program is done have a good day!");
    printf("\nTo view your results open file named RANDOM.TXT");
    printf("\nNo memory leak!");
    return;
}

/********************************************************************************
Screen Display:
CIS 15BG Homework 3
Written by: Sam Rucker
Date......: 2/12/13

Please enter a number 1-10 for the number of rows you want: 10

Enter number of entries you want (1-15) in row 1: 5
Enter number of entries you want (1-15) in row 2: 1
Enter number of entries you want (1-15) in row 3: 6
Enter number of entries you want (1-15) in row 4: 11
Enter number of entries you want (1-15) in row 5: 15
Enter number of entries you want (1-15) in row 6: 3
Enter number of entries you want (1-15) in row 7: 8
Enter number of entries you want (1-15) in row 8: 9
Enter number of entries you want (1-15) in row 9: 6
Enter number of entries you want (1-15) in row 10: 7

Would you like to run the program again Y/N?: y

Please enter a number 1-10 for the number of rows you want: 6

Enter number of entries you want (1-15) in row 1: 2
Enter number of entries you want (1-15) in row 2: 15
Enter number of entries you want (1-15) in row 3: 7
Enter number of entries you want (1-15) in row 4: 16

Invalid enter new number between 1-15 for row 4: 4
Enter number of entries you want (1-15) in row 5: 6
Enter number of entries you want (1-15) in row 6: 7

Would you like to run the program again Y/N?: y

Please enter a number 1-10 for the number of rows you want: 13

Invalid number of rows. Please enter a number 1-10: 14
Invalid number of rows. Please enter a number 1-10: 7
Enter number of entries you want (1-15) in row 1: 11
Enter number of entries you want (1-15) in row 2: 15
Enter number of entries you want (1-15) in row 3: 4
Enter number of entries you want (1-15) in row 4: 9
Enter number of entries you want (1-15) in row 5: 7
Enter number of entries you want (1-15) in row 6: 8
Enter number of entries you want (1-15) in row 7: 5

Would you like to run the program again Y/N?: y

Please enter a number 1-10 for the number of rows you want: 11

Invalid number of rows. Please enter a number 1-10: 4
Enter number of entries you want (1-15) in row 1: 19

Invalid enter new number between 1-15 for row 1: 3
Enter number of entries you want (1-15) in row 2: 7
Enter number of entries you want (1-15) in row 3: 15
Enter number of entries you want (1-15) in row 4: 9

Would you like to run the program again Y/N?: n

The program is done have a good day!
To view your results open file named RANDOM.TXT
No memory leak!

********************************************************************************/
