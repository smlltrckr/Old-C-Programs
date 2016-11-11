/**************************************************
    This is the source file that will be used inside
    of main.
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Header.h"

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
        game.name = processData(temp, &game.price, &game.rate, &game.year);
        (*newgame) = game; // copies data to GAME
        BST_Insert(gameTree, newgame);// inserts node into tree
    }

	rewind(inptFile);

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
	char string[100];

    //  Statements
    sscanf(temp, "%[^;]%*c", string);
    sscanf(temp, "%[^;]%*c %f %f %d", tempNam, price, rating, year);
    name = (char*)malloc(strlen(tempNam) + 1);
    capString(string, name);

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

    return strcmp(gam1->name, gam2->name);
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
 printf("%-35s %5.2lf %6.2lf %d\n", game->name, game->price, game->rate, game->year);

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
    printf("%d. %-35s %5.2lf %6.2lf %d\n",lev ,game->name, game->price, game->rate, game->year);

    return;
}

/*************************************************************************************
 TASK:   Inserts a new game to the tree
 Pre:    tree is a pointer to the tree
 post:   N/A
 *************************************************************************************/
void insert(BST_TREE* tree, GAME *temp)
{
    //  Local Declarations
    GAME* insrtGame;

    //  Statements
    insrtGame = (GAME*)malloc(sizeof(GAME));
    insrtGame->name = (char*)malloc(strlen(temp) + 1);
    insrtGame = temp;

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
    //  Statements
    BST_TraverseRLN(tree, IndentTree);
    printf("\n");

	return;
}
/*************************************************************************************
 TASK:   Destroy Tree
 Pre:    tree is pointer to BST_tree
 post:   destroy tree
 *************************************************************************************/
void freeMem(BST_TREE* tree )
{
    BST_Destroy(tree, freeName);

    return;
}

/*************************************************************************************
 TASK:   delete a node from the tree
 Pre:    tree is a pointer to the tree
 post:   N/A
 *************************************************************************************/
void deleteGame(BST_TREE* tree, char *temp)
{
    //  Local Declarations
    GAME delGam;

    //  Statements
	delGam.name = temp;
    BST_Delete(tree, &delGam);

    return;
}
/*************************************************************************************
 TASK:   free name
 Pre:
 post:   N/A
 *************************************************************************************/
 void freeName(void* dGam)
 {
     // Local Declarations
     GAME* delGam = (GAME*)dGam;

     // Statements
     free(delGam->name);
     free(delGam);

     return;
 }
