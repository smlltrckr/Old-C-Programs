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
        printf      ("Would you like to run the program again Y/N?: ");
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
            //printf(" %d", table[ro][co + 1]);
        }// inner for
        //printf("\n");
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
/*    printf("\n");
    for(a=0; a < rows; a++)
    {
        for(b = 0; b < table[a][0]; b++)
        {
            printf(" %d", table [a][b + 1]);
        }
        printf("\n");
    }
*/
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

//    int a, b;


/*    printf("\n");
    for(a=0; a < rows; a++)
    {
        for(b = 0; b < table[a][0]; b++)
        {
            printf(" %d", table [a][b + 1]);
        }
        printf("\n");
    }
*/
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
    printf("No memory leak");
    return;
}

/********************************************************************************
Screen Display:
CIS 15BG Homework 3
Written by: Sam Rucker
Date......: 2/12/13

Please enter a number 1-10 for the number of rows you want: 6

Enter number of entries you want (1-15) in row 1: 3
Enter number of entries you want (1-15) in row 2: 9
Enter number of entries you want (1-15) in row 3: 23

Invalid enter new number between 1-15 for row 3: 12
Enter number of entries you want (1-15) in row 4: 7
Enter number of entries you want (1-15) in row 5: 5
Enter number of entries you want (1-15) in row 6: 4
 73 -51 91
 46 -44 -77 -44 67 -71 -61 -11 79
 32 -5 -41 -48 0 -66 25 -42 33 21 38 -16
 89 -63 35 -36 95 -78 -29
 -64 90 -11 66 48
 56 -37 84 -77

 91 73 -51
 79 67 46 -11 -44 -44 -61 -71 -77
 38 33 32 25 21 0 -5 -16 -41 -42 -48 -66
 95 89 35 -29 -36 -63 -78
 90 66 48 -11 -64
 84 56 -37 -77

 38 33 32 25 21 0 -5 -16 -41 -42 -48 -66
 79 67 46 -11 -44 -44 -61 -71 -77
 95 89 35 -29 -36 -63 -78
 90 66 48 -11 -64
 84 56 -37 -77
 91 73 -51
Would you like to run the program again Y/N?: y

Please enter a number 1-10 for the number of rows you want: 10

Enter number of entries you want (1-15) in row 1: 12
Enter number of entries you want (1-15) in row 2: 5
Enter number of entries you want (1-15) in row 3: 8
Enter number of entries you want (1-15) in row 4: 3
Enter number of entries you want (1-15) in row 5: 9
Enter number of entries you want (1-15) in row 6: 32

Invalid enter new number between 1-15 for row 6: 12
Enter number of entries you want (1-15) in row 7: 7
Enter number of entries you want (1-15) in row 8: 0

Invalid enter new number between 1-15 for row 8: 3
Enter number of entries you want (1-15) in row 9: 4
Enter number of entries you want (1-15) in row 10: 7
 -25 97 9 -93 -12 -67 -71 64 -30 54 -19 51
 1 -14 -13 77 86
 -69 -69 36 33 84 -21 1 -1
 22 65 -46
 -92 -19 69 14 -2 -96 6 -81 39
 86 16 -27 63 -7 -45 -63 14 -95 -31 -56 -7
 -99 -72 -93 65 28 -19 -78
 -14 25 87
 -80 18 -3 51
 -70 -68 1 74 -40 9 6

 97 64 54 51 9 -12 -19 -25 -30 -67 -71 -93
 86 77 1 -13 -14
 84 36 33 1 -1 -21 -69 -69
 65 22 -46
 69 39 14 6 -2 -19 -81 -92 -96
 86 63 16 14 -7 -7 -27 -31 -45 -56 -63 -95
 65 28 -19 -72 -78 -93 -99
 87 25 -14
 51 18 -3 -80
 74 9 6 1 -40 -68 -70

 97 64 54 51 9 -12 -19 -25 -30 -67 -71 -93
 86 63 16 14 -7 -7 -27 -31 -45 -56 -63 -95
 69 39 14 6 -2 -19 -81 -92 -96
 84 36 33 1 -1 -21 -69 -69
 65 28 -19 -72 -78 -93 -99
 74 9 6 1 -40 -68 -70
 86 77 1 -13 -14
 51 18 -3 -80
 65 22 -46
 87 25 -14
Would you like to run the program again Y/N?: y

Please enter a number 1-10 for the number of rows you want: 12

Invalid number of rows. Please enter a number 1-10: 7
Enter number of entries you want (1-15) in row 1: 6
Enter number of entries you want (1-15) in row 2: 11
Enter number of entries you want (1-15) in row 3: 14
Enter number of entries you want (1-15) in row 4: 7
Enter number of entries you want (1-15) in row 5: 0

Invalid enter new number between 1-15 for row 5: 4
Enter number of entries you want (1-15) in row 6: 5
Enter number of entries you want (1-15) in row 7: 7
 40 -50 28 1 -13 63
 25 89 -65 5 8 -63 -54 49 4 55 19
 94 -4 36 -38 -67 -9 66 -67 -19 53 -3 -25 -61 -75
 81 25 -52 -69 30 95 24
 59 -43 -7 22
 -3 64 3 29 -12
 -19 34 -87 34 63 -12 2

 63 40 28 1 -13 -50
 89 55 49 25 19 8 5 4 -54 -63 -65
 94 66 53 36 -3 -4 -9 -19 -25 -38 -61 -67 -67 -75
 95 81 30 25 24 -52 -69
 59 22 -7 -43
 64 29 3 -3 -12
 63 34 34 2 -12 -19 -87

 94 66 53 36 -3 -4 -9 -19 -25 -38 -61 -67 -67 -75
 89 55 49 25 19 8 5 4 -54 -63 -65
 95 81 30 25 24 -52 -69
 63 34 34 2 -12 -19 -87
 63 40 28 1 -13 -50
 64 29 3 -3 -12
 59 22 -7 -43
Would you like to run the program again Y/N?: y

Please enter a number 1-10 for the number of rows you want: 4

Enter number of entries you want (1-15) in row 1: 12
Enter number of entries you want (1-15) in row 2: 8
Enter number of entries you want (1-15) in row 3: 5
Enter number of entries you want (1-15) in row 4: 4
 83 -82 -99 2 20 35 -42 -23 -64 76 75 -87
 -64 -96 -42 54 -54 97 -18 0
 46 0 -31 -83 -70
 -63 -4 61 5

 83 76 75 35 20 2 -23 -42 -64 -82 -87 -99
 97 54 0 -18 -42 -54 -64 -96
 46 0 -31 -70 -83
 61 5 -4 -63

 83 76 75 35 20 2 -23 -42 -64 -82 -87 -99
 97 54 0 -18 -42 -54 -64 -96
 46 0 -31 -70 -83
 61 5 -4 -63
Would you like to run the program again Y/N?: n

The program is done have a good day!No memory leak

********************************************************************************/
