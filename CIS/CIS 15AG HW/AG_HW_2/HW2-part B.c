/********************************************
    This program will declare the nine numbers of type double.
        Written by: Sam Rucker
        Date: 10/10/12
*/
#include <stdio.h>

int main ( void )
{
//  Local Declarations
    double a;
    double b;
    double c;
    double d;
    double e;
    double f;
    double g;
    double h;
    double i;

//  Statements
    printf  ("\nEnter nine numbers separated with a space in the format \nnnn nnn nnn nnn nnn nnn nnn nnn nnn:");
    scanf   ("%lf %lf %lf %lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f, &g, &h, &i);
    printf  ("\n********************************************************");

    a   =   a;
    b   =   b;
    c   =   c;
    d   =   d;
    e   =   e;
    f   =   f;
    g   =   g;
    h   =   h;
    i   =   i;

    printf  ("\na is :      %6.2f\n",   a);
    printf  ("\nb is :      %6.2f\n",   b);
    printf  ("\nc is :      %6.2f\n",   c);
    printf  ("\nd is :      %6.2f\n",   d);
    printf  ("\ne is :      %6.2f\n",   e);
    printf  ("\nf is :      %6.2f\n",   f);
    printf  ("\ng is :      %6.2f\n",   g);
    printf  ("\nh is :      %6.2f\n",   h);
    printf  ("\ni is :      %6.2f\n",   i);

    return  0;
}   //main
/*******************************************************
Results:

Enter nine numbers separated with a space in the format
nnn nnn nnn nnn nnn nnn nnn nnn nnn:1 43 345 6789 12348 23.4567 234.546 578.45 9
8

********************************************************
a is :        1.00

b is :       43.00

c is :      345.00

d is :      6789.00

e is :      12348.00

f is :       23.46

g is :      234.55

h is :      578.45

i is :       98.00

Process returned 0 (0x0)   execution time : 53.034 s
Press any key to continue.
*/
