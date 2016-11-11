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
void freeMem(BST_TREE* );
void IndentTree(void* g, int lev);

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
        choice = toupper(choice);

        switch(choice)
        {
            case 'I': insert(tree);
                        break;
            case 'D': deleteGame(tree);
                        break;
            case 'P': print(tree);
                        break;
            case 'E': freeMem(tree);
                        break;
            default : printf("\nNot a valid Entry!\n\n");
                        break;
        }

    }while( choice != 'E' );

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
        game.name = processData(temp, &game.price, &game.rating, &game.year);
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

    return stricmp(gam1->name, gam2->name);
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
TASK:   prints list of games
Pre:    g is a pointer to the current node
        lev is a counter to level in the tree
post:   N/A
*************************************************************************************/
void IndentTree(void* g, int lev)
{
//  Local Declarations
    GAME* game = (GAME*)g;
    int i;
//  Statements
	
		for(i = 1; i <= lev; i++)
		{
			printf("  ");
		}
		printf("%d. %-35s %5.2lf %6.2lf %d\n",lev ,game->name, game->price, game->rating, game->year);
	
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
    scanf(" %[^\n]%*c", temp);
    insrtGame->name = (char*)malloc(strlen(temp) + 1);
    strcpy(insrtGame->name, temp);
    printf("\nPrice (xxx.xx): ");
    scanf("%f", &insrtGame->price);
    printf("\nRating (0-10): ");
    scanf("%f", &insrtGame->rating);
    printf("\nYear: ");
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
    BST_TraverseRLN(tree, IndentTree);
    printf("\n");

	return;
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
    GAME delGam;
    int success;

//  Statements
    printf("Delete: ");
    scanf(" %[^\n]s", tempd);
    delGam.name = (char*)malloc(strlen(tempd) + 1);
    if(!delGam.name)
    {
        printf("delGam->name failed to allocate!\n");
        exit(303);
    }
    strcpy(delGam.name, tempd);
    success = BST_Delete(tree, &delGam);
    if(success == true)
    {
        printf("\n%s has been deleted!\n\n", delGam.name);
    }
    else
    {
        printf("\n%s was not in the list!\n\n", delGam.name);
    }

    free(delGam.name);

    return;
}

void freeMem(BST_TREE* tree )
{
    BST_Destroy(tree);

    return;
}

/*
Insert[I]
Delete[D]
Print [P]
Exit  [E]

What would you like to do?: p
****************Name*************** Price Rating Year
Assassin's Creed II: Discovery      19.99   7.80 2009
Back to the Future: The Game        19.99   7.50 2010
BioShock 2                          12.99   8.90 2010
Borderlands                         19.99   9.10 2009
Call of Duty 3                      19.99   7.40 2006
Call of Duty: Black Ops II          59.99   7.00 2012
Diablo III                          59.99   6.20 2012
Far Cry                              9.99   9.50 2004
Guild Wars 2                        59.99   8.60 2012
Halo 2                              12.99   9.00 2004
Magicka                              9.99  10.00 2011
Marval vs. Capcom 2                 14.99   9.50 2000
Mass Effect 3                       17.99   8.50 2012
MindJack                             9.99   6.10 2011
Monster Hunter Tri                  19.99   9.40 2010
Okami                               19.99   9.40 2006
Okamiden                            19.99   7.90 2011
Pikmin 2                            39.99   9.60 2004
Pokemon Ruby                        29.99   9.20 2003
Pokemon Stadium                      9.99   8.20 2000
Samurai Warriors                     7.99  10.00 2004
SimCity 4                           19.99   9.50 2003
The Godfather: The Game             14.99   9.00 2006
The Legend of Zelda: Majora's Mask  38.99   9.90 2000
The Legend of Zelda: Spirit Tracks  24.99   8.30 2009
Warcraft III: The Frozen Throne     19.99   8.80 2003

Insert[I]
Delete[D]
Print [P]
Exit  [E]

What would you like to do?: i

Name: animal crossing
Price: 59.99
Rating: 8
Year: 2012

Insert[I]
Delete[D]
Print [P]
Exit  [E]

What would you like to do?: p
****************Name*************** Price Rating Year
                                    59.99   8.00 2012
Assassin's Creed II: Discovery      19.99   7.80 2009
Back to the Future: The Game        19.99   7.50 2010
BioShock 2                          12.99   8.90 2010
Borderlands                         19.99   9.10 2009
Call of Duty 3                      19.99   7.40 2006
Call of Duty: Black Ops II          59.99   7.00 2012
Diablo III                          59.99   6.20 2012
Far Cry                              9.99   9.50 2004
Guild Wars 2                        59.99   8.60 2012
Halo 2                              12.99   9.00 2004
Magicka                              9.99  10.00 2011
Marval vs. Capcom 2                 14.99   9.50 2000
Mass Effect 3                       17.99   8.50 2012
MindJack                             9.99   6.10 2011
Monster Hunter Tri                  19.99   9.40 2010
Okami                               19.99   9.40 2006
Okamiden                            19.99   7.90 2011
Pikmin 2                            39.99   9.60 2004
Pokemon Ruby                        29.99   9.20 2003
Pokemon Stadium                      9.99   8.20 2000
Samurai Warriors                     7.99  10.00 2004
SimCity 4                           19.99   9.50 2003
The Godfather: The Game             14.99   9.00 2006
The Legend of Zelda: Majora's Mask  38.99   9.90 2000
The Legend of Zelda: Spirit Tracks  24.99   8.30 2009
Warcraft III: The Frozen Throne     19.99   8.80 2003

Insert[I]
Delete[D]
Print [P]
Exit  [E]

What would you like to do?: d
Delete: pokemon

pokemon was not in the list!

Insert[I]
Delete[D]
Print [P]
Exit  [E]

What would you like to do?: d
Delete: simcity

simcity was not in the list!

Insert[I]
Delete[D]
Print [P]
Exit  [E]

What would you like to do?: p
****************Name*************** Price Rating Year
                                    59.99   8.00 2012
Assassin's Creed II: Discovery      19.99   7.80 2009
Back to the Future: The Game        19.99   7.50 2010
BioShock 2                          12.99   8.90 2010
Borderlands                         19.99   9.10 2009
Call of Duty 3                      19.99   7.40 2006
Call of Duty: Black Ops II          59.99   7.00 2012
Diablo III                          59.99   6.20 2012
Far Cry                              9.99   9.50 2004
Guild Wars 2                        59.99   8.60 2012
Halo 2                              12.99   9.00 2004
Magicka                              9.99  10.00 2011
Marval vs. Capcom 2                 14.99   9.50 2000
Mass Effect 3                       17.99   8.50 2012
MindJack                             9.99   6.10 2011
Monster Hunter Tri                  19.99   9.40 2010
Okami                               19.99   9.40 2006
Okamiden                            19.99   7.90 2011
Pikmin 2                            39.99   9.60 2004
Pokemon Ruby                        29.99   9.20 2003
Pokemon Stadium                      9.99   8.20 2000
Samurai Warriors                     7.99  10.00 2004
SimCity 4                           19.99   9.50 2003
The Godfather: The Game             14.99   9.00 2006
The Legend of Zelda: Majora's Mask  38.99   9.90 2000
The Legend of Zelda: Spirit Tracks  24.99   8.30 2009
Warcraft III: The Frozen Throne     19.99   8.80 2003

Insert[I]
Delete[D]
Print [P]
Exit  [E]

What would you like to do?: d
Delete: samurai warriors

samurai warriors has been deleted!

Insert[I]
Delete[D]
Print [P]
Exit  [E]

What would you like to do?: p
****************Name*************** Price Rating Year
                                    59.99   8.00 2012
Assassin's Creed II: Discovery      19.99   7.80 2009
Back to the Future: The Game        19.99   7.50 2010
BioShock 2                          12.99   8.90 2010
Borderlands                         19.99   9.10 2009
Call of Duty 3                      19.99   7.40 2006
Call of Duty: Black Ops II          59.99   7.00 2012
Diablo III                          59.99   6.20 2012
Far Cry                              9.99   9.50 2004
Guild Wars 2                        59.99   8.60 2012
Halo 2                              12.99   9.00 2004
Magicka                              9.99  10.00 2011
Marval vs. Capcom 2                 14.99   9.50 2000
Mass Effect 3                       17.99   8.50 2012
MindJack                             9.99   6.10 2011
Monster Hunter Tri                  19.99   9.40 2010
Okami                               19.99   9.40 2006
Okamiden                            19.99   7.90 2011
Pikmin 2                            39.99   9.60 2004
Pokemon Ruby                        29.99   9.20 2003
Pokemon Stadium                      9.99   8.20 2000
SimCity 4                           19.99   9.50 2003
The Godfather: The Game             14.99   9.00 2006
The Legend of Zelda: Majora's Mask  38.99   9.90 2000
The Legend of Zelda: Spirit Tracks  24.99   8.30 2009
Warcraft III: The Frozen Throne     19.99   8.80 2003

Insert[I]
Delete[D]
Print [P]
Exit  [E]

What would you like to do?: e
Press any key to continue . . .
*/
