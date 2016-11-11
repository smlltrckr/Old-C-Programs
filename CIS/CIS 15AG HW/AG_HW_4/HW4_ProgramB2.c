/***********************************************
This Program will:
1.	Generate a random number and scale it to range MIN to MAX,
    where MIN = -11, and MAX = -3. // use defined constants
2.	Calculate the fourth and the fifth power of the number.
3.	Calculate the absolute value of the third power of the number
4.	Calculate the square root of the absolute value of
    the third power of the number
5.	Display all of the above as shown below:
     *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
     *                               * // could be any number in the
     *     Random number: -9         * // given range!
     *                               *
     * r^4 =   6561     r^5 =  59049 *
     *                               *
     *     Absolute value: 729       *
     *     Square root   : 27.00     *
     *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MIN -11
#define MAX -3

int main( void )
{
//  Local Definitions
int rnum1, rp4, rp5, rp3, abv, sr;

double xsr;
//  Statements
    srand(time(NULL));
    rnum1 = rand()% ((MAX - MIN) + 1) + MIN;

    //Calculations



        rp4 = pow (rnum1, 4);
        rp5 = pow (rnum1, 5);
        rp3 = pow (rnum1, 3);
        abv = abs (rp3);
        sr  = sqrt(abv);
        xsr = sr;

        printf  ("*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n");
        printf  ("*                               *\n");
        printf  ("*     Random number: %3d        *\n", rnum1);
        printf  ("*                               *\n");
        printf  ("* r^4 = %6d     r^5 = %7d*\n", rp4, rp5);
        printf  ("*     Absolute Value:%4d       *\n", abv);
        printf  ("*     Square Root   : %5.2lf     *\n", xsr);
        printf  ("*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*");



    return 0;
}
/*****************************************************************
Test 1:

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
*                               *
*     Random number:  -9        *
*                               *
* r^4 =   6561     r^5 =  -59049*
*     Absolute Value: 729       *
*     Square Root   : 27.00     *
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

Test 2:

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
*                               *
*     Random number:  -3        *
*                               *
* r^4 =     81     r^5 =    -243*
*     Absolute Value:  27       *
*     Square Root   :  5.00     *
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*


*****************************************************************/
