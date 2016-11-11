/******************************************************
This program reads from file MIDTERM.txt, calculates
average midterm scores for each student max 50 and
sorts them from higest to lowest.

Written by: Sam Rucker
Date......: 11/9/12
******************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

//  Function Declarations
int getData (FILE* midtermScores, int* studentID,
             int* midtermOne, int* midtermTwo, int current);

void calcAvg (int* midtermOne , int* midtermTwo ,
              double* midtermAvg , int current);

double calA (double* midtermAvg, int current);

void selectionSort (double midtermAvg [], int studentID [],
                    int size);

double writeAvg (FILE* midtermAverages, double midtermAvg [],
                 int studentID [], int size);

int main ( void )
{
// Local Declarations
    FILE* midtermScores;
    FILE* midtermAverages;
    int current = 0;
    int studentID [MAX_SIZE], midtermOne [MAX_SIZE],
        midtermTwo [MAX_SIZE];

    double midtermAvg [MAX_SIZE], avera;

//  Statements
    printf ("Welcome!\n\n");

    if (!(midtermScores = fopen ("AG_MIDTERM.txt", "r")))
        {
            printf ("\aProblem reading midterm file!\n");
            return 100;
        }// if open

    if (!(midtermAverages = fopen ("AG_SORTED.txt", "w")))
        {
            printf ("\aError opening average file!\n");
            return 102;
        }// if open

    while (getData (midtermScores, studentID, midtermOne ,
                    midtermTwo , current))
        {

            calcAvg (midtermOne , midtermTwo , midtermAvg ,
                     current);

            if (++current>MAX_SIZE)
                {
                    printf("Too much!");
                    exit (1);
                }
        }
    avera= calA(midtermAvg, current);

    selectionSort (midtermAvg , studentID, current);

    writeAvg (midtermAverages, midtermAvg, studentID, current);



    fclose (midtermScores);
    fclose (midtermAverages);

    printf ("Class Avg: %4.1lf\n", avera);
    printf ("Students.: %d\n", current-1);
    printf ("Highest..: %4.1lf\n", midtermAvg [0]);
    printf ("Lowest...: %4.1lf\n", midtermAvg [current-1]);

    printf ("\nDone!");

    return 0;
}
/**===================getData=================================
    Task: Reads data from midterm file.
    Pre.: midtermScores is an open file.
          current :number of elements in arrays
          studentID, midtermOne, midtermTwo pass by address
    Post: if data read   --returns 1
          if EOF or error--returns 0
===========================================================**/
int getData (FILE* midtermScores, int* studentID,
             int* midtermOne, int* midtermTwo , int current)
{
//  Local Declarations
    int ioRes;

//  Statements
    ioRes = fscanf(midtermScores, "%d%d%d", &studentID [current],
                   &midtermOne [current], &midtermTwo [current]);

    if (ioRes == EOF)
        {
            return 0;
        }
    else if (ioRes != 3)
        {
            printf ("\aError reading data!\n");
            return 0;
        }// if
    else
        return 1;
}// get data
/**===================calcAvg=================================
    Task: Calculates average score for each student.
    Pre.: current :number of elements in arrays
          midtermOne, midtermTwo, midtermAvg pass by address
    Post: midtermAvg copied to address.
===========================================================**/
void calcAvg (int *midtermOne , int *midtermTwo,
              double *midtermAvg , int current)
{
//  Statements
    midtermAvg [current] = (midtermOne [current] +
                            midtermTwo[current])/2.0;

    return;
}// calAvg
/**===================calA=================================
    Task: Calculates average score for class.
    Pre.: current :number of elements in array
          midtermAvg pass by address
    Post: returns average of class.
===========================================================**/
double calA (double* midtermAvg, int current)
{
    int sum = 0;

    int i;

    for (i=0; i<current; i++)
        {
            sum+=midtermAvg[i];
        }
    return (sum/(current-1));
}
/**===================selectionSort===========================
    Task: Sorts averages in decending order parallel
          with studentID
    Pre.: size :number of elements in arrays
          studentID, midtermAvg  contain ID and grade
    Post: midtermAvg decending parallel with IDs
===========================================================**/
void selectionSort (double midtermAvg [], int studentID [],
                    int size)
{
//  Local Declarations
    double temp;
    int id;
    int wall;
    int curr;
    int large;

//  Statements
    for (wall = 0; wall < size - 1; wall ++)
    {
        large = wall;
        for (curr = wall + 1; curr < size; curr++)
            if (midtermAvg [curr] > midtermAvg [large])
            {
                large = curr;
            }
        temp = midtermAvg [wall];
        midtermAvg [wall] = midtermAvg [large];
        midtermAvg [large] = temp;

        id = studentID [wall];
        studentID [wall] = studentID [large];
        studentID [large] = id;
    }// for

    return;
}// selectionSort
/**===================writeAvg=================================
    Task: writes ID and averages.
    Pre.: size :number of elements in arrays
          midtermAverages is an open file.
          studentID, midtermAvg contain ID and Average values.
    Post: Data written to file.
===========================================================**/
double writeAvg (FILE* midtermAverages, double midtermAvg [],
                 int studentID [], int size)
{
//  Local Declarations
    int i;
//  Statements
    for(i=0; i<size; i++)
    {
        fprintf (midtermAverages, "%d %4.1lf    ",
                 studentID[i], midtermAvg [i]);
        if ((i+1) % 4 == 0 && i != 0)
        fprintf (midtermAverages, "\n");
    }

    return 0;
}// writeAvg

/************************************************************
Results:

Welcome!

Class Avg: 79.0
Students.: 39
Highest..: 96.5
Lowest...: 44.5

Done!
************************************************************/
