/*******************************************************************************
Binary search tree
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bstADT.h"

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

#define FLUSH while( getchar() != '\n' )
FILE* openFile();
BST_TREE* readFile(FILE* );
int compare(void* , void* );
void print(BST_TREE* );
void printgame(void* );
char* processData(char* , float*, float*, int* );
void insert(BST_TREE* );
void deleteGame(BST_TREE* );

typedef struct
{
    char* name;
    float price;
    float rating;
    int year;
} GAME;

int main( void )
{
//  Local Definitions
    FILE* fpInpt;
    char choice;
    BST_TREE* tree;

//  Statements
    fpInpt = openFile();
    tree = readFile(fpInpt);
    do
    {
        printf("Insert[I]\n");
        printf("Delete[D]\n");
        printf("Print [P]\n");
        printf("Exit  [E]\n");
        printf("\nWhat would you like to do?: ");
        scanf(" %[^\n]c", &choice);
        //printf("\n");
        choice = toupper(choice);

        switch(choice)
        {
            case 'I': insert(tree);
                        break;
            case 'D': deleteGame(tree);
                        break;
            case 'P': print(tree);
                        break;
            case 'E':   break;
            default : printf("Not a valid Entry!\n\n");
                        break;
        }

    }while( choice != 'E' );

    //GAME* game;
    //BST_TREE* gameTree = BST_Create(compare);
    //  readinpt
    // loop (fgets)
    // sscanf
    // game = (GAME*)malloc(sizeof(GAME));
    // populate game
    // BST_Insert(gameTree, game);
    // BST_Traverse(gameTree, printgame);

#ifdef _MSC_VER
    printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
#endif

    system ("pause");

    return 0;
}
/*************************************************************************************
TASK: opens the input file
Pre:  N/A
post: returns pointer to input file
*************************************************************************************/
FILE* openFile()
{
//  Local Declarations
    FILE* inptFile;

//  Statements
    inptFile = fopen("videogames.txt", "r");
    if(!inptFile)
    {
        printf("videogames.txt didn't open correctly!");
        exit(300);
    }

    return inptFile;
}
/*************************************************************************************
TASK: read data from file and inserts it into tree alphabetically by name
Pre:  inptFile is a pointer to the input file videogames.txt
post: N/A
*************************************************************************************/
BST_TREE* readFile(FILE* inptFile)
{
//  Local Declarations
    char temp[100];
    GAME game; // temp structure for GAME
    GAME* newgame;
    BST_TREE* gameTree = BST_Create(compare); // creates head node for Tree and returns its address to caller

//  Statements
    while (fgets(temp, 100, inptFile) != NULL)
    {
        newgame = (GAME*)malloc(sizeof(GAME));
        if(!newgame)
        {
            printf("game failed to allocate!");
            exit(301);
        }
        game.name = processData(temp, &game.price, &game.rating, &game.year); //
        (*newgame) = game; // copies data to GAME
        BST_Insert(gameTree, newgame);// inserts node into tree
    }

    return gameTree;
}
/*************************************************************************************
TASK: parses the string scanned from file
Pre:  temp is a temporary pointer to the name of the video game
       price is a pointer to the price
       rating in a pointer to the rating
       year is a pointer to the year
post:  returns the name of the game
*************************************************************************************/
char* processData(char* temp, float* price, float* rating, int* year)
{
//  Local Declarations
    char* name;
    char tempNam[100];

//  Statements

    sscanf(temp, "%[^;]%*c %f %f %d", tempNam, price, rating, year);
    name = (char*)malloc(strlen(tempNam) + 1);
    strcpy(name, tempNam);

    return name;
}
/*************************************************************************************
TASK:   compares two games to help determine placement within tree
Pre:    G1 is a pointer to one video game
        G2 is a pointer to another video game
post:   returns an integer that determines which game comes before the other in the tree
*************************************************************************************/
int compare(void* G1, void* G2)
{
//  Local Declarations
    GAME* gam1 = (GAME*)G1;
    GAME* gam2 = (GAME*)G2;

//  Statements
/*
        GAME* temp1;
        GAME* temp2;

        temp1 = (GAME*)malloc(strlen(data1)+1);
        temp2 = (GAME*)malloc(strlen(data2)+1);

        strcpy(temp1, data1);
        strcpy(temp2, data2);

        temp1 = toupper(temp1);
        temp2 = toupper(temp2);

        strcmp(temp1
    */
    return strcasecmp(gam1->name, gam2->name);
}
/*************************************************************************************
TASK:   prints list of games
Pre:    g is a pointer to the current node
post:   N/A
*************************************************************************************/
void printgame(void* g)
{
//  Local Declarations
    GAME* game = (GAME*)g;

//  Statements
    printf("%-35s %5.2lf %6.2lf %d\n", game->name, game->price, game->rating, game->year);

    return;
}
/*************************************************************************************
TASK:   Inserts a new game to the tree
Pre:    tree is a pointer to the tree
post:   N/A
*************************************************************************************/
void insert(BST_TREE* tree)
{
//  Local Declarations
    GAME* insrtGame;
    char temp[100];

//  Statements
    insrtGame = (GAME*)malloc(sizeof(GAME));
    printf("\nName: ");
    scanf(" %[^\n]s", temp);
    insrtGame->name = (char*)malloc(strlen(temp) + 1);
    strcpy(insrtGame->name, temp);
    printf("Price: ");
    scanf("%f", &insrtGame->price);
    printf("Rating: ");
    scanf("%f", &insrtGame->rating);
    printf("Year: ");
    scanf("%d", &insrtGame->year);
    printf("\n");

    BST_Insert(tree, insrtGame);

    return;
}
/*************************************************************************************
TASK:   prints the tree
Pre:    tree is a pointer to the tree
post:   N/A
*************************************************************************************/
void print(BST_TREE* tree)
{
//  Local Declarations
    int i, k;
//  Statements
    for(k = 0; k < 16; k++)
    {
        printf("*");
    }
    printf("Name");
    for(i = 0; i < 15; i++)
    {
        printf("*");
    }
    printf(" Price Rating Year\n");
    BST_Traverse(tree, printgame);
    printf("\n");
}
/*************************************************************************************
TASK:   delete a node from the tree
Pre:    tree is a pointer to the tree
post:   N/A
*************************************************************************************/
void deleteGame(BST_TREE* tree)
{
//  Local Declarations
    char tempd[100];
    GAME* delGam;
    int success;

//  Statements
    printf("Delete: ");
    scanf(" %[^\n]s", tempd);
    //FLUSH;
    delGam = (GAME*)malloc(sizeof(GAME));
    if(!delGam)
    {
        printf("delGam failed to allocate!\n");
        exit(302);
    }
    delGam->name = (char*)malloc(strlen(tempd) + 1);
    if(!delGam->name)
    {
        printf("delGam->name failed to allocate!\n");
        exit(303);
    }
    strcpy(delGam->name, tempd);
    success = BST_Delete(tree, delGam);
    if(success == true)
    {
        printf("\n%s has been deleted!\n\n", delGam->name);
    }
    else
    {
        printf("\n%s was not in the list!\n\n", delGam->name);
    }

    return;
}
