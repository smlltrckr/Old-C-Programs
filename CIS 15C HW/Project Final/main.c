/**************************************************
    A project based on games. File I/O contains
    names, rating, price, and even the year the
    game was produced. This program also show the
    used of hast table, BST, link-list, structures,
    and many more.
        Written By: Nhat Nguyen
        Date: 5/18/2013
 **************************************************/
#include "Header.h"

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

int main (void)
{
    FILE   *fpFile;
    HEADER *pHead;
    GAME   *tempHolder;
    int    task = 0;
    int    loc, longName, success;

    //  Statement
    fpFile = openFile();
    pHead = aloHeader();
    pHead->pTree = readFile(fpFile);
    longName = getHashSize(pHead);
    pHead->pGameHash = aloHashTable(pHead);
	buildHash(pHead, pHead->hashSize, fpFile);

    do
    {
        task = menuDriver();
        if(task != 9 && task != 7)
        {
            printBoarder(task, longName);
        }

        switch( task )
        {
            case 1: tempHolder = addData(pHead);
                    loc = hashKey(tempHolder->name, pHead->hashSize);
					success = findDup(pHead, tempHolder, loc);
					if(!success)
					{
						collision(pHead, loc, tempHolder);
						insert(pHead->pTree, tempHolder);
						printf("\n%s has been added.\n", tempHolder->name);
						printf("\n");
					}
                    break;
            case 2: tempHolder = getData(pHead);
                    loc = hashKey(tempHolder->name, pHead->hashSize);
                    success = deleteData(pHead, tempHolder->name, loc);
                    break;
            case 3: searchKey(pHead, pHead->hashSize, longName);
                    break;
            case 4: printHash(pHead, pHead->hashSize, longName);
                    break;
            case 5: BST_Traverse(pHead->pTree, printgame);
                    printf("\n");
                    break;
            case 6: print(pHead->pTree);
                    break;
            case 7: writeFile(pHead, longName);
                    break;
            case 8: printEff(pHead, longName);
                    break;
            case 9: printf("\nGoodbye!\n");
                    break;
        }
    }
    while(task != 9);
	

    reWriteInput(pHead);
    fclose(fpFile);
    freeMem(pHead->pTree);
	pHead = freeMemHash(pHead);

    #ifdef _MSC_VER
    printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
	#endif

	system("pause");

    return 0;
}// main
