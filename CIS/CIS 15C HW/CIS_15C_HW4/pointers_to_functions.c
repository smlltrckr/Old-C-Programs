/*	
    To write generic code for Abstract Data Types we need two "tools":
        1.	void  pointers
        2.	pointers to functions
    Generic code allows us to write one set of functions and use it for any data type.

    A simple program that defines and uses pointers to functions

	   Written by: 
	   Date:       
*/
#include <stdio.h>
#include <string.h>

typedef struct
   {
    int   id;
    char  name[40];
    float gpa;
   } STUDENT;

//	Prototype Declarations 
int  compareInt   (void* num1, void* num2);
int  compareStu   (void* stu1, void* stu2);
int  compareNames (void* stu1, void* stu2);

int main (void)
{
//	Local Definitions 
    // compare: a pointer to a function with two arguments and int value - to use it in ADT
    int  (*compare) (void* argu1, void* argu2);  

    STUDENT s1 = { 1111, "Victor Lee", 4.0 };
    STUDENT s2 = { 2222, "Victor Lee", 3.5 };
    int cmpRes;
	
//	Statements 
    compare = compareInt; // compare points to compareInt
    cmpRes = compare( &s1.id, &s2.id );
    printf("%2d %p\n", cmpRes, compare);
    printf( "%d %d\n\n", s1.id, s2.id);

    compare = compareStu; // compare points to compareStu
    cmpRes = compare( &s2, &s1 );
    printf("%2d %p\n", cmpRes, compare);
    printf( "%d %d\n\n", s2.id, s1.id);

    compare = compareNames; // compare points to compareNames
    cmpRes = compare( &s1, &s2 );
    printf("%2d %p\n", cmpRes, compare);
    printf( "%s %s\n\n", s1.name, s2.name);

	return 0;
}	// main 

/*	==================== compareInt ====================  
	Compare two integers and return low, equal, high.
	    Pre  num1 and num2 are valid pointers to integers
	    Post return low (-1), equal (0), or high (+1)
*/
int compareInt (void* num1, void* num2)
{
//	Local Definitions 
    int key1 = *((int*)num1);
	int key2 = *((int*)num2);

//	Statements 
	if (key1 < key2)
	    return -1;
	if (key1 == key2)
	    return 0;
	return +1;
}	// compareInt 

/*	====================== compareStu ======================  
	Compare two student id's and return low, equal, high.
	    Pre  stu1 and stu2 are valid pointers to students
	    Post return low (-1), equal (0), or high (+1)
*/
int  compareStu   (void* stu1, void* stu2)
{
//	Local Definitions 
	STUDENT s1 = *((STUDENT*)stu1);
    STUDENT s2 = *((STUDENT*)stu2);;

//	Statements 
	if ( s1.id < s2.id)
	      return -1;
	     
	if ( s1.id == s2.id)
	      return 0;

	return +1;
    // return s1.id - s2.id 
}	// compareStu 


/*	====================== compareNames ======================  
	Compare two student id's and return low, equal, high.
	    Pre  stu1 and stu2 are valid pointers to students
	    Post return low (-1), equal (0), or high (+1)
*/
int  compareNames   (void* stu1, void* stu2)
{
//	Local Definitions 
	STUDENT s1 = *((STUDENT*)stu1);
    STUDENT s2 = *((STUDENT*)stu2);;

//	Statements 
	return strcmp(s1.name, s2.name);
}	// compareStu 

