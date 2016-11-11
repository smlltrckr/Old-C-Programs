/********************************************************************************
** CIS 15 BG
** Winter 2013
**************
  Homework 4: Strings and Pointers

  Counting and sorting words.

  Written By: Sam Rucker
  Date......: 2/28/13
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

#define MAX_SIZE 1000
#define MEM_ERROR printf("Not enough memory\n")
#define FLUSH while (getchar() != '\n')


// Prototype Declarations
void greet();
char verification (char file[]);
char **allocAry();
FILE* openDataFile(char file[]);
int readFile(char **listS, FILE *fpRead);
void clnListUp(char **listS, int wrdsz, char large[]);
char **reAllocAry(char **listS, int wrdsz);
int *allocfreq(int *frqcy, int wrdsz);
int seqSearch(char **listS, int *frqcy, int wrdsz);
void shiftString(char** listS, int wrdsz);
void alphSort(char **listS, int *frqcy);
void prntFile(char **listS, int *frqcy, int strgCnt,
              char file[], char large[]);
void freemem(int *frqcy, char **listS, int wrdsz);
char *stringToLower (char* inputString);
void printDone();

int main (void)
{
//  Local Definitions
    char file[25];
    char **listS;
    FILE* fpRead;
    int wrdsz;
    int strgCnt;
    int *frqcy;
    char large[50];
    char *quit = "quit";
    int quitloop = 0;
//  Statements
    greet();

    while(!quitloop)
    {
        printf("\nPlease enter name of file you wish to be read or quit to stop.");
        printf("\nChoose song_row or song_ten FILE: ");
        scanf("%s", file);
        FLUSH;


        if(strcmp(stringToLower(file), quit) == 0)
        {
            quitloop = 1;
            continue;
        }

        if (!verification (file))
        {
            continue;
        }
        listS = allocAry();
        fpRead = openDataFile(file);
        wrdsz = readFile(listS, fpRead);
        clnListUp(listS, wrdsz, large);
        listS = reAllocAry(listS, wrdsz);
        frqcy = allocfreq(frqcy, wrdsz);
        strgCnt = seqSearch(listS, frqcy, wrdsz);
        shiftString(listS, wrdsz);
        alphSort(listS, frqcy);
        prntFile(listS,  frqcy, strgCnt, file, large);
        freemem(frqcy, listS, wrdsz);

    }

    printDone();

#ifdef _MSC_VER
    printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
#endif

    printf("\n\t\tEnd of Program\n");
    printf("\n\t\tHave a great day!\n");
    return 0;

}
/********************************************************************************
TASK: Greet the user
PRE.: N/A
POST: N/A
********************************************************************************/
void greet()
{
    printf("\t\tHomework 4 - Strings and Pointers:\n");
    printf("\t\tBy..: Sam Rucker\n");
    printf("\t\tDate: 2/28/13\n");
    printf("\t\tLet us begin!\n");

    return;
}
/********************************************************************************
TASK:   verifies if file exists
PRE.:   file -> array of a string
POST:   return 1 if true and 0 if false.
********************************************************************************/
char verification (char file[])
{
//  Local Declarations

//  Statements
    if (strcmp("song_ten", file) == 0 ||
            strcmp("song_row", file) == 0)
    {
        return 1;
    }
    else
    {
        printf("Invalid file Name");
        return 0;
    }

}
/********************************************************************************
TASK: Allocates 1000 pointers.
PRE.: N/A
POST: Allocates 1000 pointers to listS
********************************************************************************/
char **allocAry()
{
//  Local Declarations
    char **listS;

//  Statements
    listS = (char**)calloc(MAX_SIZE + 1, sizeof(char));
    if(listS == NULL)
    {
        MEM_ERROR, exit(100);
    }// if

    return listS;
}
/********************************************************************************
TASK:   Opens requested file(s).
PRE.:   N/A
POST:   returns address of listS.
********************************************************************************/
FILE* openDataFile(char file[])
{
//  Local Declarations
    FILE* fpRead;
    char *verRow = "song_row";

//  Statements
    if(strcmp(verRow, file) == 0)
    {
        fpRead = fopen("song_row.txt", "r");
        if(fpRead == NULL)
        {
            printf("Sorry, file song_row.txt could not be read.\n");
            exit(101);
        }// inner if
    }
    else
    {
        fpRead = fopen("song_ten.txt", "r");
        if(fpRead == NULL)
        {
            printf("Sorry, file song_ten.txt could not be read.\n");
            exit(102);
        }// inner if
    }// outer else

    return fpRead;
}
/********************************************************************************
TASK:   Reads the file can allocates memory for each word and counts words
PRE.:   listS, tempstr, fpRead passed by address.
POST:   return's counter
********************************************************************************/
int readFile(char **listS, FILE *fpRead)
{
//  Local Declarations
    int counter = 0;
    char tempstr[50];
    char **ptr = listS;

//  Statements
    while(fscanf(fpRead, "%s", tempstr) != EOF)
    {
        *(ptr + counter) =(char*)calloc(strlen(tempstr)+1, sizeof(char));
        strcpy(*(ptr + counter), tempstr);
        counter++;
    }// while

    return counter;
}
/********************************************************************************
TASK:   removes commas, and periods, and shifts strings to fill in now empty
        spots.
PRE.:   listS pointer to pointer of chars
        wrdsz passed by value
POST:   changes strings in listS to lower and removes punctuations.
********************************************************************************/
void clnListUp(char **listS, int wrdsz, char large[])
{
//  Local Declarations
    int a, b, c;
    char *comma;
    char *period;

//  Statements
    for(a = 0; a < wrdsz; a++)
    {
        for(b = 0; listS[a][b]; b++)
        {
            listS[a][b] = tolower(listS[a][b]);
        }// inner for

        comma = strchr(listS[a], ',');
        if(comma != NULL)
        {
            *comma = '\0';
        }// inner if

        period = strchr(listS[a], '.');
        if(period != NULL)
        {
            *period = '\0';
        }// inner if
    }// outer for

    strcpy(large, listS[0]);

    for(c = 1; c < wrdsz; c++)
    {
        if(strlen(large) < strlen(listS[c]))
        {
            strcpy(large, listS[c]);
        }//inner if
    }// outer for

    return;
}
/********************************************************************************
TASK:   reallocates listS to proper size.
PRE.:   listS -> pointer to pointer of chars
POST:   listS allocated new memory to better fit.
********************************************************************************/
char **reAllocAry(char **listS, int wrdsz)
{
//  Local Declarations
    char **temp;

//  Statements
    temp = (char**)realloc (listS, (wrdsz + 1) * sizeof(char*));
    if(temp == NULL)
    {
        MEM_ERROR;
    }
    else
    {
        listS = temp;
        listS[wrdsz] = NULL;
    }

    return listS;
}
/********************************************************************************
TASK: allocates memory to frqcy array
PRE.:   frqcy -> pointer to pointer of ints
        wrdsz -> passed by value
POST:   frqcy table made.
********************************************************************************/
int* allocfreq(int *frqcy, int wrdsz)
{
//  Statements
    frqcy =(int*)calloc(wrdsz + 1, sizeof(int));
    if(frqcy == NULL)
    {
        MEM_ERROR, exit(103);
    }

    return frqcy;
}
/********************************************************************************
TASK:   Sequential search
PRE.:   listS -> pointer to pointer of chars
        frqcy -> pointer to pointer of ints
        wrdsz -> passed by value
POST:   returns strgCnt
********************************************************************************/
int seqSearch(char **listS, int *frqcy, int wrdsz)
{
//  Local Declarations
    int i, j, k;
    int cnt = 1;
    int strgCnt = 0;
    char tar[25];

// Statements
    for(i = 0, k = 0; i < wrdsz; i++)
    {
        if(listS[i] != NULL)
        {
            strcpy(tar, listS[i]);
            for(j = i + 1; j < wrdsz; j++)
            {
                if(listS[j] != NULL && strcmp(tar, listS[j]) == 0 && tar != listS[i])
                {
                    cnt++;
                    free(listS[j]);
                    listS[j] = NULL;
                }//inner inner if
            }//inner for

            frqcy[k] = cnt;

            k++;
            strgCnt++;
        }//inner if
        cnt = 1;
    }//outer for

    return strgCnt;
}

/********************************************************************************
TASK:   Cleans up NULL spaces
PRE.:   listS-> pointer to pointer of strings
        wrdsz-> passed by value
POST:   Strings get shifted up and NUlls get shifted down
********************************************************************************/
void shiftString(char** listS, int wrdsz)
{
//  Local Declarations
    int i, j;
    char **sfts;
    char **sftf;
    char *temp;

//  Statements
    for(i = 1; i < wrdsz; i++)
    {
        sfts = listS + i;
        for(j = i + 1; j < wrdsz; j++)
        {
            sftf = listS + j;
            if(*sftf != NULL)
            {
                temp = *sftf;
                *sftf = *sfts;
                *sfts = temp;
                break;
            }
        }
    }

    return;
}
/********************************************************************************
TASK:   Sorts listS alphabetically
PRE.:   listS -> ragged array of strings
        frqcy -> parallel array to listS
POST:   listS sorted alphabetically
********************************************************************************/
void alphSort(char **listS, int *frqcy)
{
//  Local Declarations
    char* tempList1;
    int tempfrqcy;
    int smallLetter;
    int current;
    int walk;

//  Statements
    for(current = 0; listS[current] != NULL; current++)
    {
        smallLetter = current;
        for(walk = current + 1; listS[walk] != NULL; walk++)
        {
            if(strcmp(listS[smallLetter], listS[walk]) > 0)
            {
                smallLetter = walk;
            }
        }


        tempList1 = listS[current];
        listS[current] = listS[smallLetter];
        listS[smallLetter] = tempList1;

        tempfrqcy = frqcy[current];
        frqcy[current] = frqcy[smallLetter];
        frqcy[smallLetter] = tempfrqcy;
    }

    return;
}
/********************************************************************************
TASK:   Writes to a file.
PRE.:   listS-> ragged array of strings
        frqcy-> 2-D array of ints
        file--> file pointer
        wrdsz-> passed by value
POST:   Writes data to a file.
********************************************************************************/
void prntFile(char **listS, int *frqcy, int strgCnt,
              char file[], char large[])
{
//  Local Declarations
    int i;
    FILE* fpWrite;
    char *out = "_out.txt";
    char tempOut[50];

//  Statements
    strcpy(tempOut, file);
    strcat(tempOut, out);

    fpWrite = fopen(tempOut, "w");
    if(fpWrite == NULL)
    {
        printf("Error writing file.");
        exit(104);
    }

    fprintf(fpWrite, "%d words\n", strgCnt);
    fprintf(fpWrite, "Maximum Length: %d\n\n", strlen(large));

    for(i = 0; i < strlen(large); i++)
    {
        fprintf(fpWrite, "=");
    }
    fprintf(fpWrite, " ");

    for(i = 0; i < 5; i++)
    {
        fprintf(fpWrite, "=");
    }

    if(strcmp(tempOut, "song_row_out.txt") == 0)
       {
           fprintf(fpWrite, "\n   Word Count\n");
       }
    else
    {
        fprintf(fpWrite, "\n        Word Count\n");
    }

    for(i = 0; i < strlen(large); i++)
    {
        fprintf(fpWrite, "=");
    }
    fprintf(fpWrite, " ");

    for(i = 0; i < 5; i++)
    {
        fprintf(fpWrite, "=");
    }
    fprintf(fpWrite, "\n");

    for(i = 0; i < strgCnt; i++)
    {
        fprintf(fpWrite, "%*s   %d\n", strlen(large), listS[i], frqcy[i]);
    }

    printf("\nFile saved to %s\n\n", tempOut);

    return;
}
/********************************************************************************
TASK:   Free the arrays
PRE.:   listS-> ragged array of strings
        frqcy-> array of pointers
        wrdsz-> passed by value
POST:   Frees the arrays.
********************************************************************************/
void freemem(int *frqcy, char **listS, int wrdsz)
{
    //  Local Declaration
    int i;

    //  Statement
    for(i = 0; i < wrdsz; i++)
    {
        free(listS[i]);
        free(frqcy);
    }
    free(listS);
    free(frqcy);

    return;
}
/********************************************************************************
TASK:   changes input by user to lower
PRE.:   inputString-> string
POST:   returns inputString (lower case version)
********************************************************************************/
char *stringToLower (char* inputString)
{
    int i;

    for(i = 0; i < strlen(inputString); i++)
    {
        inputString[i] = tolower(inputString[i]);
    }// for

    return inputString;
}
/********************************************************************************
TASK:   Ending statement
PRE.:   N/A
POST:   N/A
********************************************************************************/
void printDone()
{
    printf("\t\tThank you for using my program\n");

    return;
}

/********************************************************************************
Screen output:
*********************************************************************************
                Homework 4 - Strings and Pointers:
                By..: Sam Rucker
                Date: 2/28/13
                Let us begin!

Please enter name of file you wish to be read or quit to stop.
Choose song_row or song_ten FILE: song_row

File saved to song_row_out.txt


Please enter name of file you wish to be read or quit to stop.
Choose song_row or song_ten FILE: song_ten

File saved to song_ten_out.txt


Please enter name of file you wish to be read or quit to stop.
Choose song_row or song_ten FILE: qweqw
Invalid file Name
Please enter name of file you wish to be read or quit to stop.
Choose song_row or song_ten FILE: quit
                Thank you for using my program

                End of Program

                Have a great day!

********************************************************************************/
