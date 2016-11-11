/**
	Complex Structures 6 Points

  Define pHead, a pointer to a structure called HEADER.
  This structure contains two fields: a counter (type int)
  and a pointer to an array of structures, called pAry.

  The base type of the pAry array is another structure called BOOK.

  This BOOK structure contains three fields: title (char *),
  author (30 characters), and date of type DATE (a structure with three integers:
  month, day, and year).

	Requirements:
	1.	Type Definitions
	2.	In main(), define an array of 5 books and initialize it (see below).
	3.	Write printBook(), a function that prints a book:
	          void printBook( const BOOK *p );
	4.	Write a function named printBookList that prints the array of books
	    using the printBook() function in a loop.
	5.  Write a function named specialPrint that receives the address of a book and prints
			- the title,
			- the first letter of the author's name, and
			- the year of that book.
    6. In main() call the following functions:
            -> printBookList
            -> specialPrint - to print the required data for the third book in the list

!!!NOTE: The only variable that you may use when calling these
         functions is pHead!!!


	Save the output as a comment then upload the program.

  Written by: Sam Rucker
  Date: 3/7/13

/* ====================================================== */
#include <stdio.h>
#include <string.h>

typedef struct
{
    int month;
    int day;
    int year;
} DATE;

typedef struct
{
    char* title;
    char* author;
    DATE *date;

} BOOK;

typedef struct
{
    int counter;
    BOOK *pAry;

} HEADER;



void printBook (const BOOK *pAry);
void printBookList (const BOOK *pAry);
void specialPrint();


int main( void )
{
//  Local definitions
    BOOK list[5] =
    {

        {"Title1", "Author1", {10, 22, 2012}},
        {"Title2", "Author2", {11, 21, 2012}},
        {"Title3", "Author3", {12, 25, 2012}},
        {"Title4", "Author4", {1, 14, 2013}},
        {"Title5", "Author5", {2, 25, 2013}}

    };
    HEADER header = {5, list};
    HEADER *pHead = &header;



//  Statements
    printBook(BOOK *pAry);
    printBookList(BOOK *pAry);
    specialPrint();

    return 0;
}

void printBook (const BOOK *pAry)
{
    printf ("%c, %c, %d, %d, %d", title, author, month, day, year);
}

void printBookList ()
{
    int i;

    while(BOOK list[i] != NULL)
    {
        printf("%c, %c, %d, %d, %d", list[i]);
        i++;
    }
}

void specialPrint()
{

}
