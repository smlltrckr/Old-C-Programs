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
void getInput (char option, double gal, double cw);
int getCustID (int cid);
int getDate (int month, int day31, int day30, int day28, int day29, int year);
double getCharges (char option, double gal, double tgc, double tad, double cw);
void printheader (int month, int day31, int day30, int day28, int day29, int year);
int printMonthName (int month, int day31, int day30, int day28, int day29, int year);
void printResults (char option, int cid, double gal, double tgc, double cw, double tad);
int printfooter (void);

int main (void)
{
//  Local Declarations
    char option;
    double gal;
    double tgc;
    double tad;
    double cw;
    int cid;
    int month;
    int day31;
    int day30;
    int day28;
    int day29;
    int year = 2012;

    srand(time(NULL));
    month = 1 + (rand () % 12);
    day31 = 1 + (rand () % 31);
    day30 = 1 + (rand () % 30);
    day28 = 1 + (rand () % 28);
    day29 = 1 + (rand () % 29);

//  Statements
    getInput (option, gal, cw);
    getCustID (cid);
    getDate (month, day31, day30, day28, day29, year);
    getCharges (option, gal, tgc, tad, cw);
    printheader (month, day31, day30, day28, day29, year);
    printMonthName (month, day31, day30, day28, day29, year);
    printResults (option, cid, gal, tgc, cw, tad);
    printfooter ();
    return 0;


}// Main

void getInput (char option, double gal, double cw)
{
    printf ("Gas Type (R, U, P, N): ");
    scanf (" %c", &option);
    switch(option)

    {
        case 'r':
        case 'R':
                    option = GPR;
                    printf  ("Number of gallons: ");
                    scanf   ("%lf.2", &gal);
                    printf  ("Car wash (Y/N): ");
                    scanf   (" %c", &option);
                    switch(option)
                        {
                            case 'y':
                            case 'Y': if ((gal*GPR)>=35.00)
                                        cw = CWH;
                                      else
                                        cw = CWL;
                                        break;
                            case 'n':
                            case 'N':   cw = 0;
                                        break;
                        }
                    break;
        case 'u':
        case 'U':   option = GPU;
                    printf  ("Number of gallons: ");
                    scanf   ("%lf.2", &gal);
                    printf  ("Car wash (Y/N): ");
                    scanf   (" %c", &option);
                    switch(option)
                        {
                            case 'y':
                            case 'Y': if (gal*GPR>=35.00)
                                        cw = CWH;
                                      else
                                        cw = CWL;
                                        break;
                            case 'n':
                            case 'N':   cw = 0;
                                        break;
                        }
                    break;
        case 'p':
        case 'P':   option = GPP;
                    printf  ("Number of gallons: ");
                    scanf   ("%lf.2", &gal);
                    printf  ("Car wash (Y/N): ");
                    scanf   (" %c", &option);
                    switch(option)
                        {
                            case 'y':
                            case 'Y': if (gal*GPR>=35.00)
                                        cw = CWH;
                                      else
                                        cw = CWL;
                                        break;
                            case 'n':
                            case 'N':   cw = 0;
                                        break;
                        }
                    break;
        case 'n':
        case 'N':   option = gal = 0;
                    printf  ("Car wash (Y/N): ");
                    scanf   (" %c", &option);
                    switch(option)
                        {
                            case 'y':
                            case 'Y': if (gal*GPR>=35.00)
                                        cw = CWH;
                                      else
                                        cw = CWL;
                                        break;
                            case 'n':
                            case 'N':   cw = 0;
                                        break;
                        }
                    break;

        default :   printf ("You have entered an invalid option!");
                    break;
    }
    return;
}

int getCustID (int cid)
{
    srand(time(NULL));
    cid = rand ();

    return;
}

int getDate (int month, int day31, int day30, int day28, int day29, int year)
{

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

double getCharges (char option, double gal, double tgc, double tad, double cw)
{
    tgc = gal * option;

    tad = tgc + cw;

    return;
}

void printheader (int month, int day31, int day30, int day28, int day29, int year)
{
    printf  ("*************************************\n");
    printf  ("* Best Gas and Wash Service Station *\n");
    printf  ("*                                   *\n");

    return;
}

int printMonthName (int month, int day31, int day30, int day28, int day29, int year)
{

    switch (month)
    {
        case 1:     printf  ("*         January %d, %d          *\n", day31, year);
                    printf  ("*************************************\n");
                    break;

        case 2:     printf  ("*         February %d, %d         *\n", day28||day29, year);
                    printf  ("*************************************\n");
                    break;

        case 3:     printf  ("*         March %d, %d            *\n", day31, year);
                    printf  ("*************************************\n");
                    break;

        case 4:     printf  ("*         April %d, %d            *\n", day30, year);
                    printf  ("*************************************\n");
                    break;

        case 5:     printf  ("*         May %d, %d              *\n", day31, year);
                    printf  ("*************************************\n");
                    break;

        case 6:     printf  ("*         June %d, %d             *\n", day30, year);
                    printf  ("*************************************\n");
                    break;

        case 7:     printf  ("*         July %d, %d             *\n", day31, year);
                    printf  ("*************************************\n");
                    break;

        case 8:     printf  ("*         August %d, %d           *\n", day31, year);
                    printf  ("*************************************\n");
                    break;

        case 9:     printf  ("*         September %d, %d        *\n", day30, year);
                    printf  ("*************************************\n");
                    break;

        case 10:    printf  ("*         October %d, %d          *\n", day31, year);
                    printf  ("*************************************\n");
                    break;

        case 11:    printf  ("*         November %d, %d         *\n", day30, year);
                    printf  ("*************************************\n");
                    break;

        case 12:    printf  ("*         December %d, %d         *\n", day31, year);
                    printf  ("*************************************\n");
                    break;
    }

    return;
}

void printResults (char option, int cid, double gal, double tgc, double cw, double tad)
{


    printf  ("       Customer number: %d           \n", cid);
    printf  ("                                     \n");
    printf  ("     Gallons purchased:    %.2lf     \n", gal);
    printf  ("     Price per gallon:               \n");
    printf  ("                                     \n");
    printf  ("     Total gasoline cost:  %.2lf     \n", tgc);
    printf  ("     Car wash cost:        %.2lf     \n", cw);
    printf  ("                         ------      \n");
    printf  ("            Total due:     %.2lf     \n", tad);

    return;
}

int printfooter (void)
{
    printf  ("*************************************\n");
    printf  ("  *    Thank you for stopping!    *  \n");
    printf  ("    *       Have a nice day     *    \n");
    printf  ("      *          and          *      \n");
    printf  ("        *     come again!   *        \n");
    printf  ("          ******************         \n");

    return;
}
