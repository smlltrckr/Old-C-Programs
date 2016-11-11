/********************************************************
	This program calculates the area and circumference
	of a circle using PI as a defined constant.
	   Written by:Sam Rucker
	   Date:10/10/12

	REQUIREMENTS:
	- Write more code to calculate and display the
	      Sphere Surface Area = 4 * PI * r*r
          Sphere Volume       = PI * r*r*r * 4 / 3
	- Save the new output
*/
#include <stdio.h>
#define PI  3.1416

int main ( void )
{
//	Local Declarations
	float circ;
	float area;
	float radius;
	float surfacearea;
	float volume;

//	Statements
	printf("\nPlease enter the value of the radius: ");
	scanf("%f", &radius);

	circ        = 2  * PI     * radius;
	area        = PI * radius * radius;
	surfacearea = 4 * PI * radius * radius;
	volume      = PI * radius * radius * radius * 4 / 3;

	printf("\nRadius is :        %10.2f", radius);
	printf("\nCircumference is : %10.2f", circ);
	printf("\nArea is :          %10.2f", area);
	printf("\nSurface Area is :  %10.2f", surfacearea);
	printf("\nVolume is :        %10.2f", volume);

	return 0;
}	// main

/********************************************************
	Results:
Please enter the value of the radius: 23

Radius is :             23.00
Circumference is :     144.51
Area is :             1661.91

*********************************************************
    New Results
Please enter the value of the radius: 23

Radius is :             23.00
Circumference is :     144.51
Area is :             1661.91
Surface Area is :     6647.63
Volume is :          50965.13
*/
