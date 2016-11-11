/**************************************************
    This file contains structs as well as local
    declaration that would be used in mind.

 openFile
 aloHeader
 readFile
 compare
 processData
 getHashSize
 isPrime
 nextPrime
 aloHashTable
 buildHash
 aloGame
 aloNode
 hashKey
 menuDriver
 printBoarder
 findDup
 collision
 sortLink
 addData
 getData
 deleteData
 findKey
 searchKey
 printHash
 print
 printgame
 IndentTreeprintLoadFactor
 printLongColli
 writeFile
 freeMemHash
 freeMem


**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bstADT.h"

typedef struct
{
    char  *name;
    float price;
    float rate;
    int   year;
}GAME;

typedef struct linkTag
{
    GAME *pGame;
    struct linkTag *next;
}LINK;

typedef struct
{
    GAME *pGame;
    LINK *link;
}HASH;

typedef struct
{
    int        hashSize;
    HASH       *pGameHash;
    BST_TREE   *pTree;
}HEADER;

//  Function Declaration
FILE*     openFile(void);
HEADER*   aloHeader(void);
BST_TREE* readFile(FILE* );
int       compare(void* , void* );
char*     processData(char* , float*, float*, int* );
int       getHashSize(HEADER *pHead);
int       isPrime(int hashSize);
int       nextPrime(int hashSize);
HASH*     aloHashTable(HEADER *pHead);
void      buildHash(HEADER *pHead, int hashSize, FILE *fpFile);
GAME*     aloGame(char *key);
void      capString(char temp[], char *key);
LINK*     aloNode(void);
int       hashKey(char *key, int hashSize);
int       menuDriver(void);
void      printBoarder(int task, int longName);
int       findDup(HEADER *pHead, GAME *entryHolder, int loc);
int       collision(HEADER *pHead, int loc, GAME *entryHolder);
GAME*     addData(HEADER *pHead);
void      insert(BST_TREE* tree, GAME *temp);
GAME*     getData(HEADER *pHead);
int       deleteData(HEADER *pHead, char *key, int loc);
void      deleteGame(BST_TREE* tree, char *temp);
int       findKey(LINK **ptrNode, LINK **pPre, char *key);
void      searchKey(HEADER *pHead, int hashSize, int longName);
void      printHash(HEADER *pHead, int hashSize, int longName);
void      print(BST_TREE* );
void      printgame(void* );
void      IndentTree(void* g, int lev);
void      printEff(HEADER* pHead, int longName);
void      calculation(HEADER *pHead, float *loadfactor, int *loc, float *avg, int *count);
void      writeFile(HEADER* pHead, int longName);
HEADER*   freeMemHash(HEADER* pHead);
void      freeMem(BST_TREE* );
void      reWriteInput(HEADER *pHead);
void      freeName(void* );
