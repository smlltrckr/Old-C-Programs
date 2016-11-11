/*************************************************************
Project: Sales Tables

The following table shows the total sales for salespeople
of the ABC Manufacturing Company.
    Salesperson	     Week 1  Week 2	 Week 3  Week 4
    ===============  ======  ======  ======  ======
    Nguyen, Michael    25	   30	   45	   20
    Johnson, Mary      32	   30	   33	   29
       ...
The price of the product being sold is $1985.95
(define it as a constant). Write a program that permits the
input of the data, up to 25 salespersons and up to 6 weeks,
prints a replica of the original table to the screen, and
writes to a file a table showing the dollar value of sales
for each individual during each week along with his or her
total sales. Also it prints the total sales, the lowest and
the highest value for each week, and the total sales for the
company.

Input: There are two input files: NAMES.TXT and SALES.TXT.
A salesperson's name consists of exactly 20 characters,
including spaces. Read a name one character at a time
(Do not use strings). The first number in the input file
represents the number of salespersons:
              2
              Nguyen, Michael
              Johnson, Mary
The second input file also begins with a number representing
the number of weeks, followed by the weekly sales for the
salespeople listed in the first file, in that order:
              4
              25 30 45 20
              32 30 33 29

Output: See SAMPLE_OUTPUT.TXT Write a beginning message, an
ending message, and any other messages such as
" *** Error opening/closing files *** ",
" *** Warning: data file is to large *** ", or
" *** The output is in SALESRES.TXT *** ", and a replica
of the original table to the screen. Save the screen output
at the end of the source file as a comment.

Written by: Sam Rucker
Date......: 1/29/13

*************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define PRICE 1985.95
#define MAX_SP 25
#define MAX_WK 6

void greet ();

int rdnms (char name [][20], int row, int col);

int rdsls (int sales[][MAX_WK], int srow, int scol,
           int counter);

void calcInd (int sales [][MAX_WK], double personTotal [],
              int counter, int crw);

void calcWeek (int sales [][MAX_WK], double weekTotal [],
               int counter, int crw );

double calcTotal (double weekTotal [], int crw);

void calcHiLo (double hiLo [][MAX_WK], double totals[][MAX_WK],
               int sales [][MAX_WK], int counter, int crw);

void printResults (double hiLo [][MAX_WK], double totals[][MAX_WK],
                   int sales [][MAX_WK], double weekTotal [],
                   double fullTotal, double personTotal [],
                   int counter, int crw, char name [][20]);

int main ( void )
{
//  Local Declarations
    char name [MAX_SP][20];
    int row, col;
    int sales[MAX_SP][MAX_WK];
    int srow, scol, counter;
    int crw;
    double personTotal [MAX_SP], weekTotal [MAX_WK];
    int a, j, k;
    double aper [MAX_SP];
    double hiLo[2][MAX_WK], totals[MAX_SP][MAX_WK];
    double fullTotal;

//  Statements
    greet ();

    counter = rdnms(name, row, col);

    crw = rdsls (sales, srow, scol, counter);

    calcInd (sales, personTotal, counter, crw);

    calcWeek (sales, weekTotal, counter, crw);

    fullTotal = calcTotal (weekTotal, crw);

    calcHiLo (hiLo, totals, sales, counter, crw);

    printResults (hiLo, totals, sales, weekTotal,
                  fullTotal, personTotal, counter, crw, name);

    return 0;
}   // main

/*************************************************************
    TASK:   Greet user.
    PRE.:   N/A
    POST:   N/A
*************************************************************/

void greet ()
{
    // Statements
    printf ("CIS 15BG HW 2\nBy Sam Rucker\n");
    printf ("Let's check our sales numbers\n\n");

    return;
}// greet

/*************************************************************
    TASK:   Reads names from file one letter at a time.
    PRE.:   name is an array of characters
            row, col are ints
    POST:   Variable counter equals number of Sales Persons
*************************************************************/

int rdnms (char name [][20], int row, int col)
{
//  Local Declarations
    FILE* fpnam;
    char letter;
    int counter, newline = 0;


//  Statements
    fpnam = fopen ("NAMES.TXT", "r");

    if ( fpnam == NULL )
    {
        printf ("The file could  not be read/n");
        exit (100);
    }

    fscanf (fpnam, "%d", &counter);
    fscanf (fpnam, "%*d");

    if (counter > MAX_SP)
    {
        printf ("Those after the 25th person not included!\n");
    }

    for (row = 0; row < counter; row++)
    {
        for(col = 0, newline = 0; col  < 20; col++)
        {
            if (newline)
            {
                // pad columns with spaces
                name [row][col] = ' ';
                continue;
            }

            fscanf ( fpnam, "%c", &letter );

            if (letter != '\n')
            {
                name [row][col] = letter;
            }
            else
            {
                name [row][col] = ' ';
                newline = 1;
            }
        }
    }

    fclose (fpnam);

    return counter;
}   // rdnms

/*************************************************************
    TASK:   Scan SALES.TXT and assign values to 2-D array
    PRE.:   sales is an array of ints
            srow, scol, counter are ints
    POST:   returns crw
*************************************************************/

int rdsls (int sales[][MAX_WK], int srow, int scol, int counter)
{
    FILE* fpSales;
    int numsal, crw;

    fpSales = fopen ( "SALES.TXT.", "r" );

    if ( fpSales == NULL )
    {
        printf ("The file could  not be read/n");
        exit (100);
    }
    fscanf( fpSales, "%d", &crw );


    for ( srow = 0; srow < counter; srow++ )
    {
        for ( scol = 0; scol < crw; scol++ )
        {
            fscanf ( fpSales, "%d", &numsal );
            sales [srow][scol] = numsal;
        }
    }

    fclose (fpSales);

    return crw;
}// rdsls

/*************************************************************
    TASK:   Calculates the total amount earned for each person
    PRE.:   sales is an array of ints
            personTotal in an array of doubles
            counter and crw are ints passed by value
    POST:   assigns values to personTotal
*************************************************************/

void calcInd (int sales [][MAX_WK], double personTotal [],
              int counter, int crw)
{
//  Local Declarations
    int a, b;

//  Statements


    for ( a = 0; a < counter; a++ )
    {
        personTotal [a] = 0;
        for( b = 0; b < crw; b++ )
        {
            personTotal [a] += sales [a][b] * PRICE;
        }
    }

    return;
}// calcInd

/*************************************************************
    TASK:   Calculates the weekly totals
    PRE.:   sales is an array of ints
            weekTotal in an array of doubles
            counter, and crw are ints passed by value
    POST:   assigns values to weekTotal
*************************************************************/

void calcWeek (int sales [][MAX_WK], double weekTotal [],
               int counter, int crw )
{
//  Local Declarations
    int c,d;

//  Statements
    for (d = 0; d < crw; d++ )
    {
        weekTotal [d] = 0;
        for ( c = 0; c < counter; c++ )
        {
            weekTotal [d] += sales [c][d] * PRICE;
        }
    }

    return;
}// calcWeek

/*************************************************************
    TASK:   Calculates total amount earned for everyone
    PRE.:   weekTotal is an array of doubles
            crw is an int passed by value
    POST:   returns fullTotal
*************************************************************/

double calcTotal (double weekTotal [], int crw)
{
//  Local Declarations
    int j;

//  Statements
    double fullTotal = 0;

    for (j = 0; j < crw; j++)
    {
        fullTotal += weekTotal [j];
    }

    return fullTotal;
}// calcTotal

/*************************************************************
    TASK:   Calculates the highest and lowest values of each
            week
    PRE.:   hiLo, totals are arrays of doubles
            sales is an array of ints
            counter, crw are passed by value
    POST:   assigns values to hiLo
*************************************************************/

void calcHiLo (double hiLo [][MAX_WK], double totals[][MAX_WK],
               int sales [][MAX_WK], int counter, int crw)
{
//  Local Declarations

    int w, q;


//  Statements for Weekly Arrays
    for (w = 0; w < crw; w++)
    {
        for (q=0; q< counter; q++)
        {
            totals[q][w] = sales [q][w] * PRICE;
            if (q == 0)
            {
                hiLo[0][w] = totals[q][w];
                hiLo[1][w] = totals[q][w];

            }
            if (totals[q][w] < hiLo [0][w])
            {
                hiLo[0][w] = totals[q][w];
            }
            if (totals[q][w] > hiLo [1][w])
            {
                hiLo[1][w] = totals[q][w];
            }
        }
    }
    return;
}// calcHiLo

/*************************************************************
    TASK:   Prints Results to screen and to SALESRES.TXT
    PRE.:   hiLO, totals, weekTotal, personTotal are arrays of
            doubles
            sales is an array of ints
            name is an array of characters
            counter, crw passed by value
            fullTotal is passed by value
    POST:   Prints results to stdout and file SALESRES.TXT
*************************************************************/

void printResults (double hiLo [][MAX_WK], double totals[][MAX_WK],
                   int sales [][MAX_WK], double weekTotal [],
                   double fullTotal, double personTotal [],
                   int counter, int crw, char name [][20])
{
//  Local Declarations
    FILE* fpSalesResults;
    int i, j, k;

//  Statements
    fpSalesResults = fopen ("SALESRES.TXT", "w");

    if ( fpSalesResults == NULL )
    {
        printf ("The file could  not be read/n");
        exit (100);
    }

    fprintf (stdout,"		Homework 2: Two Dimensional Arrays\n\n");
    fprintf (stdout," *** Sales Table *** \n\n");
    fprintf (stdout,"==================== ======== ======== ======== ======== \n");
    fprintf (stdout," Sales Person         Week 1   Week 2   Week 3   Week 4  \n");
    fprintf (stdout,"==================== ======== ======== ======== ======== \n");
    for (i = 0; i < counter; i++)
    {
        for (j = 0; j < 20; j++)
        {
            fprintf (stdout,"%c", name[i][j]);
        }
        printf ("%7d %8d %8d %8d\n",
                sales[i][0], sales[i][1], sales[i][2], sales[i][3]);//for
    }//for
    fprintf (stdout,"\n*** The output is in SALESRES.TXT *** \n\n");
    fprintf (stdout,"		End of the program!\n");
    fprintf (stdout,"		Have a great day!");

//  File Output personTotal
    fprintf (fpSalesResults, "===========================\n");
    fprintf (fpSalesResults, " ABC Manufacturing Company\n");
    fprintf (fpSalesResults, "===========================\n");
    fprintf (fpSalesResults, "\n*** Dollar Values Table *** \n\n");
    fprintf (fpSalesResults, "==================== ========== ========== ========== ==========  =============");
    fprintf (fpSalesResults, "\n Sales Person          Week 1     Week 2     Week 3     Week 4     Total/Person");
    fprintf (fpSalesResults, "\n==================== ========== ========== ========== ==========  =============\n");
    for (i = 0; i < counter; i++)
    {
        for (j = 0; j < 20; j++)
        {
            fprintf (fpSalesResults,"%c", name[i][j]);
        }
        fprintf (fpSalesResults," %10.2lf %10.2lf %10.2lf %10.2lf",
                 totals[i][0], totals[i][1], totals[i][2], totals[i][3]);
        fprintf (fpSalesResults," %13.2lf\n", personTotal[i]);
    }//for
    fprintf (fpSalesResults, "==================== ========== ========== ========== ==========\n");
    fprintf(fpSalesResults,"       Total / Week:");
    for (i = 0; i < crw; i++)
    {
        fprintf(fpSalesResults," %10.2lf", weekTotal[i]);
    }

//  Hi Lo
    for (i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            fprintf (fpSalesResults,"\n\n               LOW : ");
        }
        else
        {
            fprintf (fpSalesResults,"\n               HIGH: ");
        }
        for (j=0; j < crw; j++)
        {
            fprintf(fpSalesResults,"%10.2lf ", hiLo[i][j]);
        }
        fprintf(fpSalesResults,"\n");
    }
    fprintf(fpSalesResults,"\n\n\n *** Total Sales for company:   %10.2lf ***",
            fullTotal);
    fprintf(fpSalesResults,"\n=============");
    fprintf(fpSalesResults,"\nEnd of Report");
    fprintf(fpSalesResults,"\n=============");

    fclose (fpSalesResults);
    return;
}
/********************************************************************************
Screen output

CIS 15BG HW 2
By Sam Rucker
Let's check our sales numbers

                Homework 2: Two Dimensional Arrays

 *** Sales Table ***

==================== ======== ======== ======== ========
 Sales Person         Week 1   Week 2   Week 3   Week 4
==================== ======== ======== ======== ========
Kelly, Victor            25       20       25       25
Lam, Gary                20       22       23       22
Nagasake, David          25       26       25       22
Nguyen, Jeff             30       28       25       26
Nguyen, Michael          25       30       45       20
Sinn, Scott              30       25       20       21
Smith, Jacob             27       25       24       26
Son, Thai                20       23       24       20
Tavares, Maribel         28       26       24       25
Tran, Diane              30       10       35       32
Tsukamoto, Andrew        28       29       30       35
Wang, Mary               15       16       15       14
Young, Daniel            12       15       12       19
Wells, Steve             20       24       20       18
Wong, Justin             10       15       12       16
Johnson, Mary            32       30       33       29

*** The output is in SALESRES.TXT ***

                End of the program!
                Have a great day!

********************************************************************************/


