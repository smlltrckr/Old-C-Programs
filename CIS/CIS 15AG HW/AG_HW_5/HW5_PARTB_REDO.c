/**
============================================~*~~

SCORE:  50 / 100
Please resubmit. Come and talk to me if you have
any questions.

============================================~*~~
*/

/*********************************************************
PART B:  Write a documented program to calculate the
amount a customer should be charged at a gas station
(see instructions on the next pages). Run the program
six times (see instructions). Save each output at the
end of the source file as a comment.

PROBLEM: Calculate the amount a customer should be charged
at a gas station.

Each customer is identified by a five-digit number.
That number should appear on the bill. Fees for the
car wash are $4.25 with gasoline purchase of $35.00 or
more and $10.00 otherwise. Three kinds of gasoline are
available: regular at 3.39, unleaded at 3.55 and premium
at 3.65 per gallon. Input consists of the customer number,
number of gallons purchased, kind of gasoline purchased
(R, U, P, or, for no purchase, N), and car wash desired
(Y or N).

Use memory constants or defined constants for
gasoline prices and car wash fees.

Use random numbers to generate the customer number
and the date: month, day, and year
(all integers: 11/8/2013).


Written by: Sam Rucker
Date: 11/8/12
*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>


#define CWH 4.25
#define CWL 10.00
#define GPR 3.39
#define GPU 3.55
#define GPP 3.65

//  Function Declarations
void getInput (char option, char option2, double* gal, double* cw, double* gp);
int getCustID (int *cid);
int getDate (int month, int day31, int day30, int day28, int day29, int year);
double getCharges (double* gal, double* tgc, double* tad, double* cw, double* gp);
void printheader (int month, int day31, int day30, int day28, int day29, int year);
int printMonthName (int month, int day31, int day30, int day28, int day29, int year);
void printResults (char option2, int cid, double* gal, double* tgc, double* cw, double* tad, double* gp);
int printfooter (void);

int main (void)
{
//  TASK:
//  Local Declarations
    char option;
    char option2;
    double gal;
    double tgc;
    double tad;
    double cw;
    double gp;
    int cid;
    int month;
    int day31;
    int day30;
    int day28;
    int day29;
    int year = 2012;

//  PRE:
    srand(time(NULL));
    month = 1 + (rand () % 12);
    day31 = 1 + (rand () % 31);
    day30 = 1 + (rand () % 30);
    day28 = 1 + (rand () % 28);
    day29 = 1 + (rand () % 29);
/**
============================================~*~~

call a getDate function here:
    getDate(&month, &day, &year);

-2Points
============================================~*~~
*/



//  Statements
    getInput (option, option2, &gal, &cw, &gp);
    getCustID (&cid);
    getDate (month, day31, day30, day28, day29, year);
    getCharges (&gal, &tgc, &tad, &cw, &gp);
    printheader (month, day31, day30, day28, day29, year);
    printMonthName (month, day31, day30, day28, day29, year);
    printResults (option2, cid, &gal, &tgc, &cw, &tad, &gp);
    printfooter ();
    return 0;


}// POST:
 // Main

/**
============================================~*~~
DOCUMENTATION:
must be written for each sub-function
    TASK:
    PRE:
    POST:

-3Points
============================================~*~~
*/
//  TASK:
void getInput (char option, char option2, double* gal, double* cw, double* gp)
{
//  PRE:
    printf ("Gas Type (R, U, P, N): ");
    scanf (" %c", &option);
    switch(option)

    {
        case 'r':
        case 'R':
                    *gp = GPR;
                    printf  ("Number of gallons: ");
                    scanf   ("%lf", &*gal);
                    printf  ("Car wash (Y/N): ");
                    scanf   (" %c", &option2);
                    switch(option2)
                        {
                            case 'y':
                            case 'Y': if ((*gal*GPR)>=35.00)
                                        *cw = CWH;
                                      else
                                        *cw = CWL;
                                        break;
                            case 'n':
                            case 'N':   *cw = 0;
                                        break;
                        }
                    break;
        case 'u':
        case 'U':   *gp = GPU;
                    printf  ("Number of gallons: ");
                    scanf   ("%lf", &*gal);
                    printf  ("Car wash (Y/N): ");
                    scanf   (" %c", &option2);
                    switch(option2)
                        {
                            case 'y':
                            case 'Y': if (*gal*GPR>=35.00)
                                        *cw = CWH;
                                      else
                                        *cw = CWL;
                                        break;
                            case 'n':
                            case 'N':   *cw = 0;
                                        break;
                        }
                    break;
        case 'p':
        case 'P':   *gp = GPP;
                    printf  ("Number of gallons: ");
                    scanf   ("%lf", &*gal);
                    printf  ("Car wash (Y/N): ");
                    scanf   (" %c", &option2);
                    switch(option2)
                        {
                            case 'y':
                            case 'Y': if (*gal*GPR>=35.00)
                                        *cw = CWH;
                                      else
                                        *cw = CWL;
                                        break;
                            case 'n':
                            case 'N':   *cw = 0;
                                        break;
                        }
                    break;
        case 'n':
        case 'N':   *gp = *gal = 0;
                    printf  ("Car wash (Y/N): ");
                    scanf   (" %c", &option2);
                    switch(option2)
                        {
                            case 'y':
                            case 'Y': if (*gal*GPR>=35.00)
                                        *cw = CWH;
                                      else
                                        *cw = CWL;
                                        break;
                            case 'n':
                            case 'N':   *cw = 0;
                                        break;
                        }
                    break;

        default :   printf ("You have entered an invalid option!");
                    break;
    }
    return;

}
//  POST:
/**
============================================~*~~
DOCUMENTATION:
must be written for each sub-function
    TASK:
    PRE:
    POST:
============================================~*~~
*/
//  TASK:
int getCustID (int* cid)
{
//  PRE:
    srand(time(NULL));
    *cid = 10000 + rand () % 90000;

    return;
}
//  POST:

/**
============================================~*~~
DOCUMENTATION:
must be written for each sub-function
    TASK:
    PRE:
    POST:
============================================~*~~
*/
//  TASK
int getDate (int month, int day31, int day30, int day28, int day29, int year)
{
//  PRE:
    switch(month)
    {


        case    1:
        case    3:
        case    5:
        case    7:
        case    8:
        case   10:
        case   12:      day31;
                    break;

        case    2:
                    if  (year == 2012)
                        day29;

                    else
                        day28;
                    break;

        case    4:
        case    6:
        case    9:
        case   11:      day30;
                    break;
    }

    return;
}
//  POST:
/**
============================================~*~~
DOCUMENTATION:
must be written for each sub-function
    TASK:
    PRE:
    POST:
============================================~*~~
*/
//  TASK
double getCharges (double* gal, double* tgc, double* tad, double* cw, double* gp)
{
//  PRE:
    *tgc = *gp * *gal;

    *tad = *tgc + *cw;

    return;
}
//  POST:

//  TASK:
void printheader (int month, int day31, int day30, int day28, int day29, int year)
{
//  PRE:
    printf  ("*************************************\n");
    printf  ("* Best Gas and Wash Service Station *\n");
    printf  ("*                                   *\n");

    return;
}
//  POST:
/**
============================================~*~~
DOCUMENTATION:
must be written for each sub-function
    TASK:
    PRE:
    POST:
============================================~*~~
*/
//  TASK:
int printMonthName (int month, int day31, int day30, int day28, int day29, int year)
{
//  PRE:

    switch (month)
    {
        case 1:     printf  ("*         January %2d, %d          *\n", day31, year);
                    printf  ("*************************************\n");
                    break;

        case 2:     printf  ("*         February %2d, %d         *\n", day28||day29, year);
                    printf  ("*************************************\n");
                    break;

        case 3:     printf  ("*         March %2d, %d            *\n", day31, year);
                    printf  ("*************************************\n");
                    break;

        case 4:     printf  ("*         April %2d, %d            *\n", day30, year);
                    printf  ("*************************************\n");
                    break;

        case 5:     printf  ("*         May %2d, %d              *\n", day31, year);
                    printf  ("*************************************\n");
                    break;

        case 6:     printf  ("*         June %2d, %d             *\n", day30, year);
                    printf  ("*************************************\n");
                    break;

        case 7:     printf  ("*         July %2d, %d             *\n", day31, year);
                    printf  ("*************************************\n");
                    break;

        case 8:     printf  ("*         August %2d, %d           *\n", day31, year);
                    printf  ("*************************************\n");
                    break;

        case 9:     printf  ("*         September %2d, %d        *\n", day30, year);
                    printf  ("*************************************\n");
                    break;

        case 10:    printf  ("*         October %2d, %d          *\n", day31, year);
                    printf  ("*************************************\n");
                    break;

        case 11:    printf  ("*         November %2d, %d         *\n", day30, year);
                    printf  ("*************************************\n");
                    break;

        case 12:    printf  ("*         December %2d, %d         *\n", day31, year);
                    printf  ("*************************************\n");
                    break;
    }

    return;
}
//  POST:
/**
============================================~*~~
UGLY switch
Avoid writing the same code multiple times
============================================~*~~
*/

/**
============================================~*~~
DOCUMENTATION:
must be written for each sub-function
    TASK:
    PRE:
    POST:
============================================~*~~
*/
//  TASK:
void printResults (char option2, int cid, double* gal, double* tgc, double* cw, double* tad, double* gp)
{
//  PRE:
    printf  ("       Customer number: %d           \n", cid);
    printf  ("                                     \n");
    printf  ("     Gallons purchased:  %6.2lf      \n", *gal);
    printf  ("     Price per gallon:   %6.2lf      \n", *gp);

if (option2=='y'||'Y')
    {   printf  ("                                     \n");
        printf  ("     Total gasoline cost:%6.2lf      \n", *tgc);
        printf  ("     Car wash cost:      %6.2lf      \n", *cw);
        printf  ("                         ------      \n");
        printf  ("            Total due:   %6.2lf      \n", *tad);
    }

else
    {
        printf  ("                         ------      \n");
        printf  ("            Total due:   %6.2lf      \n", *tad);
    }
    return;
}
//  POST:
/**
============================================~*~~
Use if statements when printing too!
============================================~*~~
*/

/**
============================================~*~~
DOCUMENTATION:
must be written for each sub-function
    TASK:
    PRE:
    POST:
============================================~*~~
*/
//  TASK:
int printfooter (void)
{
//  PRE:
    printf  ("*************************************\n");
    printf  ("  *    Thank you for stopping!    *  \n");
    printf  ("    *       Have a nice day     *    \n");
    printf  ("      *          and          *      \n");
    printf  ("        *     come again!   *        \n");
    printf  ("          ******************         \n");

    return;
}
//  Post

/*********************************************************************
Test 1:

Gas Type (R, U, P, N): P
Number of gallons: 10.02
Car wash (Y/N): Y
*************************************
* Best Gas and Wash Service Station *
*                                   *
*         April 23, 2012            *
*************************************
       Customer number: 28053

     Gallons purchased:   10.02
     Price per gallon:     3.65

     Total gasoline cost: 36.57
     Car wash cost:       10.00
                         ------
            Total due:    46.57
*************************************
  *    Thank you for stopping!    *
    *       Have a nice day     *
      *          and          *
        *     come again!   *
          ******************

Test 2:

Gas Type (R, U, P, N): r
Number of gallons: 15.50
Car wash (Y/N): N
*************************************
* Best Gas and Wash Service Station *
*                                   *
*         July 30, 2012             *
*************************************
       Customer number: 28207

     Gallons purchased:   15.50
     Price per gallon:     3.39

     Total gasoline cost: 52.55
     Car wash cost:        0.00
                         ------
            Total due:    52.55
*************************************
  *    Thank you for stopping!    *
    *       Have a nice day     *
      *          and          *
        *     come again!   *
          ******************

Test 3:

Gas Type (R, U, P, N): U
Number of gallons: 19.00
Car wash (Y/N): y
*************************************
* Best Gas and Wash Service Station *
*                                   *
*         April  4, 2012            *
*************************************
       Customer number: 28354

     Gallons purchased:   19.00
     Price per gallon:     3.55

     Total gasoline cost: 67.45
     Car wash cost:        4.25
                         ------
            Total due:    71.70
*************************************
  *    Thank you for stopping!    *
    *       Have a nice day     *
      *          and          *
        *     come again!   *
          ******************

Test 4:

Gas Type (R, U, P, N): R
Number of gallons: 6.50
Car wash (Y/N): y
*************************************
* Best Gas and Wash Service Station *
*                                   *
*         April 26, 2012            *
*************************************
       Customer number: 28514

     Gallons purchased:    6.50
     Price per gallon:     3.39

     Total gasoline cost: 22.04
     Car wash cost:       10.00
                         ------
            Total due:    32.03
*************************************
  *    Thank you for stopping!    *
    *       Have a nice day     *
      *          and          *
        *     come again!   *
          ******************

Test 5:

Gas Type (R, U, P, N): n
Car wash (Y/N): Y
*************************************
* Best Gas and Wash Service Station *
*                                   *
*         April 19, 2012            *
*************************************
       Customer number: 28605

     Gallons purchased:    0.00
     Price per gallon:     0.00

     Total gasoline cost:  0.00
     Car wash cost:       10.00
                         ------
            Total due:    10.00
*************************************
  *    Thank you for stopping!    *
    *       Have a nice day     *
      *          and          *
        *     come again!   *
          ******************

Test 6:

Gas Type (R, U, P, N): N
Car wash (Y/N): n
*************************************
* Best Gas and Wash Service Station *
*                                   *
*         September 11, 2012        *
*************************************
       Customer number: 28736

     Gallons purchased:    0.00
     Price per gallon:     0.00

     Total gasoline cost:  0.00
     Car wash cost:        0.00
                         ------
            Total due:     0.00
*************************************
  *    Thank you for stopping!    *
    *       Have a nice day     *
      *          and          *
        *     come again!   *
          ******************

*********************************************************************/

