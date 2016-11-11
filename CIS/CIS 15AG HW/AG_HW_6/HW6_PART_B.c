/*******************************************************
The purpose of this program is to practice loops
and calculate PI
*******************************************************/

#include <stdio.h>
#include <math.h>

void    printinfo ();
int     getlimit (void);

double  calcPI (int lmt);
void    printPI (double pie, int lmt);
void    printdone ();


//  Task
int main ( void )
{
//  Pre
//  Local Declarations
    printinfo   ();
    int lmt = getlimit();

    double pie;
    pie = calcPI(lmt);

    printPI     (pie, lmt);
    printdone   ();
//  Post
return 0;
}

//Task
void    printinfo ()
{
//  Pre
    printf("FALL 2012\n");
    printf("CIS 15AG\n");
    printf("Homework 5 - loops: calculate PI\n");
    printf("Sam Rucker\n");
//  Post
    return;
}

//  Task
int getlimit (void)
{
//  Pre
    int lmt;
    char valid = 0;
    while (!valid)
    {
        printf  ("Please enter a number between 1 and 10000: ");
        scanf   ("%d", &lmt);
        if (lmt > 0 && lmt <= 10000)
        {
            valid = 1;
        }
    }
//  Post
    return lmt;
}

// Task
double calcPI (int lmt)
{
//  Pre
    double sum = 0;
    int x;

    for(x=1; x<=lmt; x++)
    {
        sum += 1 / pow(x, 2);
    }
//  Post
    return sqrt(6*sum);
}

//  Task
void printPI (double pie, int lmt)
{
//  Pre
    printf("With limit of: %d\n", lmt);
    printf("PI is about..: %lf\n", pie);
//  Post
    return;
}

//  Task
void printdone ()
{
//  Pre
    printf("Done, I hope you like Pie!\n");
//  Post
    return;
}
