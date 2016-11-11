/**********************************************************
This program will read one file (EMPLOYMENTREPORT.txt)
calculate base pay and write to another file.

WRITTEN BY: SAM RUCKER
DATE......: 11/28/12
**********************************************************/

#include <stdio.h>

//  Function Declarations
int getEmp (FILE* spEmp,
            int* empN, int* empD, double* empR, char* ex, int* empH);

void calcBp (double empR, int empH, double* empBp);

double wrtEmp (FILE* spBp,
               int empN, int empD, double empR, char ex, int empH,
               double empBp);

int main ( void )
{
//  Local Declarations
    FILE* spEmp;
    FILE* spBp;

    int empN;
    int empD;
    int empH;

    double empR;
    double empBp;

    char ex;

//  Statements
    printf ("Welcome to base pay calculator! Let us begin.\n");

    if (!(spEmp = fopen ("EMPLOYMENTREPORT.TXT", "r")))
        {
            printf ("\aError opening employment file\n");
            return 100;
        } // if open input

    if (!(spBp = fopen ("BASEPAY.TXT", "w")))
        {
            printf ("\aError opening base pay file\n");
            return 102;
        } // if open output

    while (getEmp ( spEmp, &empN, &empD, &empR, &ex, &empH ))
        {
         calcBp( empR, empH, &empBp );
         wrtEmp( spBp, empN, empD, empR, ex, empH, empBp );
        } // while

    fclose (spEmp);
    fclose (spBp);

    printf ("End of base pay calculation check BASEPAY.\n");

    return 0;
}   //  main

/**===================getEmp=================================
    Task: Reads data from employment file.
    Pre.: spEmp is an open file.
          empN, empD, empR, ex, empH pass by address
    Post: if data read   --returns 1
          if EOF or error--returns 0
===========================================================**/

int getEmp (FILE* spEmp, int* empN, int* empD, double* empR, char* ex, int* empH)
{
//  Local Declarations
    int ioRes;

//  Statements
    ioRes = fscanf (spEmp, "%d%d%lf %c %d", empN, empD, empR, ex, empH);

    if (ioRes == EOF)
        return 0;
    else if (ioRes != 5)
        {
            printf("\aError reading data\n");
            return 0;
        } // if
    else
        return 1;
} // getEmp

/**====================caclBp===================================
    Task: Determines base pay for an employee.
    Pre.: empR, empH contain rate and hours.
          empBp address of variable
    Post: empBp copied to address
=============================================================**/

void calcBp (double empR, int empH, double* empBp)

{
//  Statements
    *empBp = empR * empH;

    return;
} // calcBp

/**====================wrtEmp===================================
    Task: Writes Employee data with calculated base pay
    Pre.: spBp is an open file
          empN, empD, empR, ex, empH, empBp have values to write
    Post: Data written to file
=============================================================**/

double wrtEmp (FILE* spBp,
               int empN, int empD, double empR, char ex, int empH,
               double empBp)
{
//  Statements
    fprintf (spBp, "%04d %d %.2lf %c %d %.2lf\n",
                    empN, empD, empR, ex, empH, empBp);

    return 0;
} // writeStu


