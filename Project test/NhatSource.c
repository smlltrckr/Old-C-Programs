#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Header.h"

#define FLUSH while (getchar()!='\n')


/* ==================== openFile ====================
    This function opens the .TXT file.
        PRE:  Nothing.
        POST: returns a pointer to the file.
 ================================================== */
FILE* openFile(void)
{
    //  Local Declaration
    FILE* fpFile;

    //  Statement
    fpFile = fopen("videogames.txt", "r");
    if(!fpFile)
    {
        printf("Sorry, file could not be open.\n");
        exit(100);
    }

    return fpFile;
}// openFile

/* ==================== aloHeader ====================
    This function allocates memory for the HEADER
    structure.
        PRE:  Nothing.
        POST: returns a pointer to the allocated memory.
 =================================================== */
HEADER* aloHeader(void)
{
    //  Local Declaration
    HEADER *pHead;

    //  Statement
    pHead = (HEADER*)malloc(sizeof(HEADER));
    if(!pHead)
    {
        printf("Sorry, memory overflow.\n");
        exit(101);
    }

    return pHead;
}// aloHeader

/* ==================== getHashSize ====================
    This function process the string inside the file.
    It allocates memory for the nodes in the link
    list. It also calculates the size for the hash
    table.
        PRE:  pHead - passed by refference.
              fpFile - pointer to a file.
        POST: returns int - hash size for table.
 ================================================== */
int getHashSize(HEADER *pHead)
{
    //  Local Declaration
    FILE* fpFile;
    int   hashSize = 0;
    int   size = 0;
    char  temp[1000];
    char  name[100];
    int  success;

    //  Statement
    fpFile = openFile();
    while(fgets(temp, sizeof(temp), fpFile) != NULL)
    {
        sscanf(temp, "%[^;]", name);
        if(strlen(name) > size)
        {
            size = (int)strlen(name);
        }
        hashSize++;
    }
    hashSize *= 2;
    hashSize++;

    //hashSize = 13;
    //pHead->hashSize = hashSize;

    success = isPrime(hashSize);
    if(success)
    {
        hashSize = nextPrime(hashSize);
    }
    pHead->hashSize = hashSize;

    rewind(fpFile);

    return size;
}// getHashSize



/* ==================== isPrime ====================
    This function finds out if the hashsize is prime.
        PRE:  hashSize - is passed by value.
        POST: returns true or false.
================================================= */
int isPrime(int hashSize)
{
    //  Local Declaration
    int i;

    //  Statement
    if(hashSize < 2)
        return 0;
    for(i = 2; i < hashSize; ++i)
    {
        if(hashSize % i == 0)
            return 0;
    }

    return 1;
}// isPrime

/* ==================== nextPrime ====================
    This function finds the next prime number.
        PRE:  hashSize - is passed by value.
        POST: returns the next prime number.
=================================================== */
int nextPrime(int hashSize)
{
    //  Local Declaration

    //  Statement
    for( ; !isPrime(hashSize); ++hashSize)
    ;

    return hashSize;
}// nextPrime

/* ==================== aloHashTable ====================
    This function allocates the hashtable.
        PRE:  hashSize - the size of the hash table.
        POST: returns a pointer to HASH allocation.
 ====================================================== */
HASH* aloHashTable(HEADER *pHead)
{
    //  Local Declaration
    HASH *pHash;
	int i;

    //  Statement
    pHash = (HASH*)malloc(pHead->hashSize * sizeof(HASH));
    if(!pHash)
    {
        printf("Memory allocaton for pHash failed.\n");
        exit(103);
    }
	for(i = 0; i < pHead->hashSize; i++)
	{
		pHash[i].pGame = NULL;
		pHash[i].link = NULL;
	}

    return pHash;
}// aloHashTable

/* ==================== buildHash ====================
    This function builds the hash table.
        PRE:  pHead - a pointer to a HEADER structure.
              hashSize - size of hash table.
        POST: Nothing.
 =================================================== */
void buildHash(HEADER *pHead, int hashSize, FILE *fpFile)
{
    //  Local Declaration
    char temp[1000];
    GAME *entryHolder;
    int loc;
	char tempStr[100];

    //  Statement
    while(fgets(temp, sizeof(temp), fpFile) != NULL)
    {
        sscanf(temp, "%[^;]%*c", tempStr);
		entryHolder = aloGame(tempStr);

		sscanf(temp, "%[^;]%*c %f %f %d", entryHolder->name, &(entryHolder->price), &(entryHolder->rate), &(entryHolder->year));
		capString(tempStr, entryHolder->name);

        loc = hashKey(entryHolder->name, hashSize);
        collision(pHead, loc, entryHolder);
    }

    return;
}// buildHash

/* ==================== hashKey ====================
    This function hash the key and produce the loca-
    tion for the hash table.
        PRE:  key - pointer to a string.
              hashSize - size of hash table.
        POST: returns loc for hash table.
================================================= */
int hashKey(char *key, int hashSize)
{
    //  Local Declaration
    int  loc = 0;
    int  i;
    char name[100];

    //  Statment
    strcpy(name, key);
    for(i = 0; i < strlen(name); i++)
    {
        loc += name[i];
		loc += name[i+1] * i;
    }
    loc = loc % hashSize;

    return loc;
}// hashKey

/* ==================== aloGame ====================
 This function alocated GAME struct.
    PRE:  Nothing.
    POST: returns a pointer to the GAME structure.
 ================================================= */
GAME* aloGame(char *key)
{
    //  Local Declaration
    GAME* g1;

    //  Statement
    g1 = (GAME*)malloc(sizeof(GAME));
    if(!g1)
    {
        printf("Error, allocation for GAME struct failed");
        exit(105);
    }

	g1->name = (char*)malloc(sizeof(char) * strlen(key) + 1);
    if(!g1->name)
    {
        printf("Error, allocation for name failed.");
        exit(106);
    }

    return g1;
}// aloGame

/* ==================== capString ====================
	This function caps all the letters.
		PRE: temp - is an array of char.
			 key  - is a pointer to the updated string.
==================================================== */
void capString(char temp[], char *key)
{
	//	Local Declaration
	int i;
	//char *string;

	//	Statement
	for(i = 0; i < strlen(temp); i++)
	{
		temp[i] = toupper(temp[i]);
	}
	strcpy(key, temp);

	return;
}// capString

/* ==================== findDup ====================
    This function checks for any duplication in names.
        PRE:
        POST:
=================================================== */
int findDup(HEADER *pHead, GAME *entryHolder, int loc)
{
    //  Local Declartion
    LINK *pWalk;
    int found = 0;

    //  Statement
    if(pHead->pGameHash[loc].pGame != NULL &&
       strcmp(pHead->pGameHash[loc].pGame->name, entryHolder->name) == 0)
    {
        printf("\nSorry, game already exist.\n\n");
        found++;
        free(entryHolder);
    }
    else if(pHead->pGameHash[loc].link != NULL)
    {
        pWalk = pHead->pGameHash[loc].link;
        while(pWalk != NULL && !found)
        {
            if(strcmp(pWalk->pGame->name, entryHolder->name) == 0)
            {
                printf("\nSorry, game already exist.\n\n");
                free(entryHolder);
                found++;
            }
            else
                pWalk = pWalk->next;
        }
    }

    return found;
}

/* ==================== collision ====================
    This function solves collision in the hash table
        PRE:  pHead - pointer to HEADER.
              loc - location for hash table.
              entryHolder - pointer to a GAME struct.
        POST: returns a pointer to the HEADER struct.
=================================================== */
int collision(HEADER* pHead, int loc, GAME *entryHolder)
{
    //  Local Declaration
    LINK   *pWalk;
    LINK   *pNew;
    int success = 0;

    //  Statment
    //  pGame isn't empty
    if(pHead->pGameHash[loc].pGame != NULL)
    {
        //  link has no successor
        if(pHead->pGameHash[loc].link == NULL)
        {
            pNew = aloNode();
            pNew->pGame = entryHolder;
            pNew->next == NULL;
            pHead->pGameHash[loc].link = pNew;
        }

        //  if the hash contain other data.
        else if(pHead->pGameHash[loc].link != NULL)
        {
            pNew = aloNode();
            pNew->pGame = entryHolder;
            pWalk = pHead->pGameHash[loc].link;
            pHead->pGameHash[loc].link = pNew;
            pNew->next = pWalk;
        }
        success++;
    }
    else
	{
        pHead->pGameHash[loc].pGame = entryHolder;
	}
    return success;
}// collision

/* ==================== aloNode ====================
    This function allocates NODES for collision in
    the hash table.
        PRE:  Nothing.
        POST: returns a pointer to the NODE allocation.
================================================= */
LINK* aloNode(void)
{
    //  Local Declaration
    LINK *ptr;

    //  Statement
    ptr = (LINK*)malloc(sizeof(LINK));
    if(!ptr)
    {
        printf("Allocation for NODES failed.");
        exit(106);
    }
    ptr->next =(LINK*)malloc(sizeof(LINK));
    if(!ptr->next)
    {
        printf("Allocation for link failed.\n");
        exit(107);
    }
    ptr->next = NULL;

    return ptr;
}// aloNode

/* ==================== menuDriver ====================
    This function display the menu driver for the user
    to pick which process they want to perform. It uses
    recursion to make sure the input is valid.
        PRE:  Nothing.
        Post: returns the task number.
 ==================================================== */
int menuDriver(void)
{
    //  Local Declaration
    int task = 0;

    //  Statement
    printf("(1) Add New Data        \t(2) Delete Data\n");
    printf("(3) Search Key          \t(4) List Hash Table\n");
    printf("(5) List In Key Sequence\t(6) Print Tree\n");
    printf("(7) Write To File       \t(8) Efficiency\n");
    printf("(9) Quit\n");
    printf("\nPlease select from the option above: ");
    scanf("%d", &task);
    FLUSH;
    if(task > 9 || task < 1)
    {
        printf("\nSorry, please enter a valid input.\n\n");
        task = menuDriver();
    }

    return task;
}// menuDriver

/* ==================== printBoarder ====================
 This function prints the head boarder for each menu
 option.
 PRE:  task - the menu choosen from user.
 POST: print boarder.
 ===================================================== */
void printBoarder(int task, int longName)
{
    //  Local Declaration
    int i;

    //  Statement
    printf("\n");
    for(i = 0; i < longName + 22; i++)
    {
        printf("=");
    }
    switch( task)
    {
        case 1: printf("\n%*s\n", longName, "Add New Data");
                break;
        case 2: printf("\n%*s\n", longName, "Delete Data");
                break;
        case 3: printf("\n%*s\n", longName, "Search Key");
                break;
        case 4: printf("\n%*s\n", longName, "List Hash Table");
                break;
        case 5: printf("\n%*s\n", longName, "List In Key Sequence");
                break;
        case 6: printf("\n%*s\n", longName, "Print Tree");
                break;
        case 8: printf("\n%*s\n", longName, "Efficiency");
                break;
    }
    for(i = 0; i < longName + 22; i++)
    {
        printf("=");
    }
    printf("\n");


    return;
}// printBoarder

/* ==================== addData ====================
    This function adds new data into the hash table.
        PRE:  pHead - pointer to a HEADER struct.
              longName - size of longest string.
        POST: returns a pointer to the GAME struct.
================================================= */
GAME* addData(HEADER* pHead)
{
    //  Local Declaration
    GAME* ptrGame;
	char temp[100];
	//int success;
	//int loc;

    //  Statement
    printf("Please enter game name: ");
    while(scanf("%[^\n]", temp) != 1)
	{
		printf("Please enter game name: ");
		scanf("%[^\n]", temp);
		FLUSH;
	}

	ptrGame = aloGame(temp);
	capString(temp, ptrGame->name);

	printf("Please enter game price $xxx.xx: ");
	while(scanf("%f", &(ptrGame->price)) != 1)
	{
		printf("Please enter game price $xxx.xx: ");
		scanf("%f", &(ptrGame->price));
		FLUSH;
	}

	printf("Please enter game rating xx.x: ");
	while(scanf("%f", &(ptrGame->rate)) != 1)
	{
		printf("Please enter game rating xx.x: ");
		scanf("%f", &(ptrGame->rate));
		FLUSH;
	}

	printf("Please enter game year production xxxx: ");
	while(scanf("%d", &(ptrGame->year)) != 1)
	{
		printf("Please enter game year production xxxx: ");
		scanf("%4d", &(ptrGame->year));
		FLUSH;
	}

    return ptrGame;
}// addData

/* ==================== getData ====================
    This function deletes data from the hashtable.
        PRE:  pHead - pointer to a HEADER struct.
        POST: returns a pointer to game struct.
================================================= */
GAME*   getData(HEADER *pHead)
{
    //  Local Declaration
    GAME* ptrGame;
	char temp[100];

    //  Statement

    printf("Please enter the game name to be deleted: ");
    while(scanf("%[^\n]", temp) != 1)
    {
        printf("Please enter the game name to be deleted: ");
        scanf("%[^\n]", temp);
        FLUSH;
    }
    printf("\n");
	ptrGame = aloGame(temp);
	capString(temp, ptrGame->name);

    return ptrGame;
}// getData

/* ==================== deleteData ====================
    This function deletes data from the hash table.
        PRE:  pHead - pointer to HEADER struct.
              key - pointer to a string.
              loc - location for hash table.
              longName - size of longest string.
        POST: returns a pointer to the HEADER struct.
==================================================== */
int deleteData(HEADER *pHead, char *key, int loc)
{
    //  Local Declaration
    LINK   *pWalk, *temp;
    LINK   *pPre = NULL;
    int    found = 0;

    //  Statement

    //  key not found
    if(pHead->pGameHash[loc].pGame == NULL)
    {
        printf("Sorry, key wasn't found.\n\n");
    }

    //  check to see if location isn't NULL and if hash data matches
    else if(pHead->pGameHash[loc].pGame != NULL &&
            strcmp(pHead->pGameHash[loc].pGame->name, key) == 0)
    {
        //  if entry has no other links associated with it
        if(pHead->pGameHash[loc].link == NULL)
        {
            printf("%s deleted.\n\n", pHead->pGameHash[loc].pGame->name);
			deleteGame(pHead->pTree, key);

			//free(pHead->pGameHash[loc].pGame->name);
            //free(pHead->pGameHash[loc].pGame);

			pHead->pGameHash[loc].pGame = NULL;
            found++;
        }

        // if entry matches in first location and has links to it
        else
        {
            printf("%s deleted.\n\n", pHead->pGameHash[loc].pGame->name);
            pWalk = pHead->pGameHash[loc].link;
            pHead->pGameHash[loc].pGame = pWalk->pGame;
            temp = pWalk;
            pWalk = pWalk->next;
			//free(temp->pGame->name);
            //free(temp->pGame);
			free(temp);
			//temp = NULL;
            pHead->pGameHash[loc].link = pWalk;
            found++;
			deleteGame(pHead->pTree, key);
        }
    }

    //  if location isn't null and hash data isn't a match
    else if(strcmp(pHead->pGameHash[loc].pGame->name, key) != 0 &&
            pHead->pGameHash[loc].pGame != NULL)
    {
        // if there are other data links with the same hash key
        if(pHead->pGameHash[loc].link != NULL)
        {
            pWalk = pHead->pGameHash[loc].link;
            found = findKey(&pWalk, &pPre, key);

            // if key is found
            if(found)
            {
                temp = pWalk;

                //  if node has successor and pPre isn't null
                if(pWalk->next != NULL && pPre != NULL)
                {
                    printf("%s deleted.\n\n", pWalk->pGame->name);
                    pWalk = pWalk->next;
                    pPre->next = pWalk;

					deleteGame(pHead->pTree, key);

                    //free(temp->pGame->name);
					//free(temp->pGame);
					free(temp);
					temp = NULL;
                    found++;
					deleteGame(pHead->pTree, key);
                }

                //  if node has no successor and pPre is NULL
                else if(pWalk->next == NULL && pPre == NULL)
                {
                    printf("%s deleted.\n\n", pWalk->pGame->name);

					deleteGame(pHead->pTree, key);

                    //free(temp->pGame->name);
					//free(temp->pGame);
					free(temp);
					temp = NULL;
                    pHead->pGameHash[loc].link = NULL;
                    found++;
					deleteGame(pHead->pTree, key);
                }

                // if node has successors and pPre is NULL
                else
                {
                    printf("%s deleted.\n\n", pWalk->pGame->name);
                    pWalk = pWalk->next;
                    pHead->pGameHash[loc].link = pWalk;

					deleteGame(pHead->pTree, key);

                    //free(temp->pGame->name);
					//free(temp->pGame);
					free(temp);
					temp = NULL;
                    found++;
					deleteGame(pHead->pTree, key);
                }
            }
            else
                printf("Sorry, no matching key.\n\n");
        }
        else
            printf("Sorry, no matching key.\n\n");
    }

    return found;
}// deleteData

/* ==================== findKey ====================
    This function searches the link list for match-
    ing key to be deleted.
        PRE:  ptrNode - pointer to a pointer of a
              NODE.
              pPre - pointer to a pointer of a NODE.
              key - pointer to a string.
        POST: returns 1 - found.
              returns 0 - not found.
================================================= */
int findKey(LINK **ptrNode, LINK **pPre, char *key)
{
    //  Local Declaration
    int found = 0;

    //  Statement
    if((*pPre) == NULL)
    {
        if((*ptrNode)->next != NULL &&
           strcmp((*ptrNode)->pGame->name, key) != 0)
        {
            (*pPre) = (*ptrNode);
            (*ptrNode) = (*ptrNode)->next;
        }
        else if(strcmp((*ptrNode)->pGame->name, key) == 0)
        {
            return ++found;
        }
    }

    while((*ptrNode)->next != NULL && strcmp((*ptrNode)->pGame->name, key) != 0)
    {
        (*pPre) = (*ptrNode);
        (*ptrNode) = (*ptrNode)->next;
    }

    if(strcmp((*ptrNode)->pGame->name, key) == 0)
    {
        return ++found;
    }
    else
        return found;
}// findKey

/* ==================== searchKey ====================
    This function searches the key.
        PRE:  pHead - pointer to a HEADER struct.
              hashSize - the size of the hash table.
              longName - size of longest string.
        POST: Nothing.
=================================================== */
void searchKey(HEADER *pHead, int hashSize, int longName)
{
    //  Local Declaration
    char temp[100];
	char *name;
    int  loc;
    LINK *pWalk;

    //  Statement
    printf("Please enter game name: ");
    scanf("%[^\n]", temp);
    FLUSH;

	name = (char*)malloc(sizeof(char) * strlen(temp) + 1);
	capString(temp, name);

    loc = hashKey(name, hashSize);

    // hash table that consist of links.
    if(pHead->pGameHash[loc].link != NULL)
    {
       pWalk = pHead->pGameHash[loc].link;

       if(strcmp(pHead->pGameHash[loc].pGame->name, name) !=0)
       {
           while(pWalk != NULL && strcmp(pWalk->pGame->name, name) != 0)
           {
               pWalk = pWalk->next;
           }
           if(pWalk != NULL)
           {
               printf("\n%-*s Price: %6.2f  Rating: %4.1f Year: %d\n\n", longName - 18,
                      pWalk->pGame->name,
                      pWalk->pGame->price,
                      pWalk->pGame->rate,
                      pWalk->pGame->year);
           }
           else
               printf("\nSorry, game could not be found.\n\n");
       }
       else
           printf("\n%-*s Price: %6.2f  Rating: %4.1f Year: %d\n\n", longName - 18,
                  pHead->pGameHash[loc].pGame->name,
                  pHead->pGameHash[loc].pGame->price,
                  pHead->pGameHash[loc].pGame->rate,
                  pHead->pGameHash[loc].pGame->year);
    }

    // hash table with no links and at least 1 data in the hash
    else if(pHead->pGameHash[loc].pGame != NULL && pHead->pGameHash[loc].link == NULL)
    {
        if(strcmp(pHead->pGameHash[loc].pGame->name, name) == 0)
        {
            printf("\n%-*s Price: %6.2f  Rating: %4.1f Year: %d\n\n", longName - 18,
                   pHead->pGameHash[loc].pGame->name,
                   pHead->pGameHash[loc].pGame->price,
                   pHead->pGameHash[loc].pGame->rate,
                   pHead->pGameHash[loc].pGame->year);
        }
        else
            printf("\nSorry, game could not be found.\n\n");
    }
    else
    {
        printf("\nSorry, game could not be found.\n\n");
    }

	free(name);

    return;
}// searchKey

/* ==================== printHash ====================
    This function prints out the hash table.
        PRE:  pHead - pointer to a HEADER struct.
              hashSize - size of hash table.
              longName - size of longest string.
        POST: Nothing.
================================================== */
 void printHash(HEADER *pHead, int hashSize, int longName)
{
    //  Local Declaration
    int i;
    LINK *pWalk;

    // Statement
    for(i = 0; i < hashSize; i++)
    {
        if(pHead->pGameHash[i].pGame != NULL)
        {
            printf("%2d: %-*s  %6.2f %4.1f %4d\n", i, longName, pHead->pGameHash[i].pGame->name,
                                                  pHead->pGameHash[i].pGame->price,
                                                  pHead->pGameHash[i].pGame->rate,
                                                  pHead->pGameHash[i].pGame->year);
        }
        else
        {
            printf("%2d: NULL\n", i);
        }

        pWalk = pHead->pGameHash[i].link;
        while(pWalk != NULL)
        {
            printf("    %-*s  %6.2f %4.1f %4d\n", longName, pWalk->pGame->name,
                                                 pWalk->pGame->price,
                                                 pWalk->pGame->rate,
                                                 pWalk->pGame->year);

            pWalk = pWalk->next;
        }

    }
    printf("\n");

    return;
}// printHash

/* ==================== printEff ====================
 This function finds the longest collision hash table
 and prints all the nodes in the list.
 PRE:  pHead - pointer to the header struct.
 POST: print longest collision link list.
 ========================================================= */
void printEff(HEADER* pHead, int longName)
{

    //  Local Declaration
    LINK *pWalk;
    float loadFactor, avg;
    int loc, i, size;

    //  Statement
    calculation(pHead, &loadFactor, &loc, &avg, &size);

    printf("Load Factor: %4.2f\n", loadFactor);
    printf("Average Number of Nodes: %4.2f\n", avg);

    printf("\nLongest link list size: %d\n", size);
	if(size > 0)
	{
		pWalk = pHead->pGameHash[loc].link;
		while(pWalk != NULL)
		{
			printf("%-*s %6.2f %5.2f %d\n", longName, pWalk->pGame->name,
				                        pWalk->pGame->price,
					                    pWalk->pGame->rate,
						                pWalk->pGame->year);
			pWalk = pWalk->next;
		}
	}
		printf("\n");

    return;

}// printEff

/* ==================== calculation ====================
    This function prints the load factor.
        PRE:  This function calculates the load factor for
              the hash table.
        POST: prints load factor percentage.
========================================================== */
void calculation(HEADER *pHead, float *loadFactor, int *loc, float *avg, int *count)
{
    //  Local Declaration
    int i, j;
    int size   = 0;
    int large  = 0;
    int total = 0;
    LINK *pWalk;

    //  Statement

    // load factor calulation
    for(i = 0, j = 0; i < pHead->hashSize; i++)
    {
        if(pHead->pGameHash[i].pGame == NULL)
        {
            j++;
        }
    }

    *loadFactor = 100 / (float)(pHead->hashSize) * (pHead->hashSize - j);

    for(i = 0; i < pHead->hashSize; i++)
    {
        size = 0;
        if(pHead->pGameHash[i].link != NULL)
        {
            pWalk = pHead->pGameHash[i].link;
            while(pWalk != NULL)
            {
                pWalk = pWalk->next;
                size++;
                total++;
            }
            if(size > large)
            {
                large = size;
                *loc = i;
            }
        }
    }
	*count = large;
    *avg = (float) total / pHead->hashSize;

    return;
}// calculation

/* ==================== writeFile ====================
    This function writes all the data to a txt file.
        PRE:  pHead - pointer to the header struct.
              longName - size of longest string.
        POST: data written to file.
=================================================== */
void writeFile(HEADER* pHead, int longName)
{
    //  Local Declaration
    FILE  *fpOut;
    LINK  *pWalk;
    int   i, size;
    int   loc = 0;
    float loadFactor, avg;

    //  Statement

    //  Open the a new file.
    fpOut = fopen("GameProjectOut.txt", "w");
    if(!fpOut)
    {
        printf("Error while trying to write to file.\n");
        exit(105);
    }

    calculation(pHead, &loadFactor, &loc, &avg, &size);

    // print hash table
    fprintf(fpOut, "%*s", longName, "Hash Table:\n");
    for(i = 0; i < pHead->hashSize; i++)
    {
        if(pHead->pGameHash[i].pGame != NULL)
        {
            fprintf(fpOut, "%2d: %-*s %6.2f %4.1f %d\n", i, longName, pHead->pGameHash[i].pGame->name,
                                                         pHead->pGameHash[i].pGame->price,
                                                         pHead->pGameHash[i].pGame->rate,
                                                         pHead->pGameHash[i].pGame->year);
            pWalk = pHead->pGameHash[i].link;
            while(pWalk != NULL)
            {
                fprintf(fpOut, "    %-*s %6.2f %4.1f %d\n", longName, pWalk->pGame->name,
                                                            pWalk->pGame->price,
                                                            pWalk->pGame->rate,
                                                            pWalk->pGame->year);
                pWalk = pWalk->next;
            }
        }
        else
            fprintf(fpOut, "%2d: NULL\n", i);
    }

    // print the efficiency
    fprintf(fpOut, "\n%*s\n", longName, "Efficiency:");
    fprintf(fpOut, "Load Factor: %6.2f\n", loadFactor);
    fprintf(fpOut, "Average Number of Nodes: %4.2f", avg);

    pWalk = pHead->pGameHash[loc].link;
    fprintf(fpOut, "\nLongest Collision: %d\n\n", size);
    fprintf(fpOut, "%*s", longName, "Longest Collision List:\n");
    while(pWalk != NULL)
    {
        fprintf(fpOut, "%-*s %6.2f %4.1f %d\n", longName, pWalk->pGame->name,
                                                pWalk->pGame->price,
                                                pWalk->pGame->rate,
                                                pWalk->pGame->year);
        pWalk = pWalk->next;
    }

    printf("\nFile saved to GameProjectOut.txt\n\n");
	fclose(fpOut);

    return;
}// writeFile

/* ==================== freeMem ====================
    This function free all allocated memory.
        PRE:  pHead - pointer to header struct.
        POST: returns NULL.
================================================= */
HEADER* freeMemHash(HEADER *pHead)
{
    //  Local Declaration
    int i;
    LINK *pWalk;
    LINK *temp;

    //  Statement
    for(i = 0; i < pHead->hashSize; i++)
	{
		if(pHead->pGameHash[i].pGame != NULL)
		{
			if(pHead->pGameHash[i].link != NULL)
			{
				pWalk = pHead->pGameHash[i].link;
				while(pWalk != NULL)
				{
					temp = pWalk;
					pWalk = pWalk->next;
					//free(temp->pGame->name);
					//free(temp->pGame);
					free(temp);
					temp = NULL;
				}
				free(pHead->pGameHash[i].pGame->name);
				free(pHead->pGameHash[i].pGame);
			}
		}
	}
    free(pHead->pGameHash);
    free(pHead);

    return NULL;
}// freeMem

/* ==================== reWriteInput ====================
    This function rewrites the input so that it can be
    reuse.
        PRE:  pHead - pointer to the header struct.
        POST: file written.
======================================================= */
void reWriteInput(HEADER *pHead)
{
    //  Local Declaration
    FILE *fpFile;
    LINK *pWalk;
    int i;

    //  Statement
    fpFile = fopen("newInput.txt", "w");
    if(!fpFile)
    {
        printf("Sorry, file could not be written.\n");
    }

    for(i = 0; i < pHead->hashSize; i++)
    {
        if(pHead->pGameHash[i].pGame != NULL)
        {
            fprintf(fpFile, "%s; %6.2f %4.1f %d\n", pHead->pGameHash[i].pGame->name,
                    pHead->pGameHash[i].pGame->price,
                    pHead->pGameHash[i].pGame->rate,
                    pHead->pGameHash[i].pGame->year);

            pWalk = pHead->pGameHash[i].link;
            while(pWalk != NULL)
            {
                fprintf(fpFile, "%s; %6.2f %4.1f %d\n", pWalk->pGame->name,
                        pWalk->pGame->price,
                        pWalk->pGame->rate,
                        pWalk->pGame->year);
                pWalk = pWalk->next;
            }
        }
    }

    printf("File saved to newInput.txt.\n");

    fclose(fpFile);
    return;
}// reWriteInput
