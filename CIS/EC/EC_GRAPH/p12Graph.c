/*	This program tests the graph ADT as implemented 
	in Gilberg & Forouzan.
	
	Written by: G & F
	Date:       2/98
	
    Brooks/Cole Publishing Company
	An International Thomson Publishing Company
	Copyright 1998. All Rights Reserved
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <crtdbg.h>

#include "graphADT.h"

#define INPUT "graph_0.txt"

void doInsertVertex   (GRAPH *graph);
void doInsertArc      (GRAPH *graph);
void doDeleteVertex   (GRAPH *graph);
void doDeleteArc      (GRAPH *graph);
void search           (GRAPH *graph);
void doRetrieveVertex (GRAPH *graph);
void doFirstArc       (GRAPH *graph);
void testUtilties     (GRAPH *graph);

void buildAGraph12_1a (GRAPH *graph);
void buildAGraph      (GRAPH *graph, char fileName[]);

char   doMenu (void);

int    compare (void *newDataPtr, void *rootDataPtr);

void   process (void *dataPtr);

void printVertex (GRAPH *graph, void  *pFromKey);

void printGraph (GRAPH *graph);

int main ( void )
{
	
	char   option;
	int    key;
	GRAPH *graph;

	printf(	"Start Explore Graphs\n" );		
	graph = createGraph (compare);
	if (!graph)
	   printf("\aERROR: Cannot create graph\a\n"), exit (100);

	//buildAGraph12_1a(graph);	// builds the graph in Figure 12-1(a)
	buildAGraph (graph, INPUT);		// builds graph from file

	while ( (option = doMenu () ) != 'q' )
	{
		 switch (option)
		 {
			 case 'i' :  doInsertVertex (graph);
						 break;
			 case 'd' :  doDeleteVertex (graph);
						 break;
			 case 'a' :  doInsertArc (graph);
						 break;
			 case 'b' :  doDeleteArc (graph);            
						 break;                     
			 case 'p' :  printf("Enter vertex key: ");
						 scanf ("%d", &key);
						 printVertex(graph, &key);
						 break;
			 case 'l' :  printGraph(graph);
				         break;
			 case 'r' :  doRetrieveVertex (graph);
						 break;
			 case 's' :  doFirstArc (graph);
						 break;
			 case 't' :  process (NULL);                   //Set count
						 printf("\nBegin depth first traversal\n");
						 depthFirst (graph, process);
						 printf("\nEnd depth first traversal\n");
                     
						 printf("\nBegin breadth first traversal\n");
						 process (NULL);                   //Set count
						 breadthFirst (graph, process);
						 printf("\nEnd breadth first traversal\n");
						 break;
			 case 'x' :  testUtilties (graph);
						 break;
			 default  :  printf( "\a\a\nInvalid option. Please try again.\n" );
		 } // switch 
	}// while 

	destroyGraph(graph);
	printf( "End Explore Graphs\n" );
	printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");

	system("pause");

	return 0;
}// main 
/* ================================================================ */
/*	This function prints a menu and reads the user selection.
	Pre		Nothing.
	Post	option returned.
*/
char	doMenu ( void ) 
{
	char	option;
 
 	printf( "\n============ Menu =============\n" );
 	printf( " i :     Insert new item         \n" );
 	printf( " d :     Delete a vertex         \n" );
 	printf( " a :     Insert an arc           \n" );
 	printf( " b :     Delete an arc           \n" );
    printf( " p :     Print Vertex Adjacency  \n" );
	printf( " l :     Print Graph             \n" );
    printf( " r :     Retrieve Vertex         \n" );
 	printf( " s :     Retrieve First Arc      \n" );
 	printf( " t :     Traverse graph          \n" );
 	printf( " x :     Test ADT utilities      \n" );
 	printf( " q :     Quit                  \n\n" );
 	printf( "===============================  \n" );
 	printf( "Please enter your choice:  " );
 		 
 	scanf( " %c", &option );
 	option = tolower ( option );
 	
 	return option;
}// doMenu 


/* ================================================================ */
/*	This function locates a vertex in the graph.
	Pre	 graph exists.
	Post vertex retrieved and printed.
*/
void doRetrieveVertex (GRAPH *graph)
{
	int key;
	int success;
	int *addr;

	printf("Please enter key to be found: ");
	scanf ("%d", &key);
	
	success = retrieveVertex (graph, &key, &addr);
	
	if (success == 1)
	    printf("\nKey found. Contains %d\n", *addr);
	else
	    printf("\n\aKey %d not found\n", key);
	
	return;
}// doRetrieveVertex 

/* ================================================================ */
/*	This function locates the first arc of a vertex.
	Pre	 graph exists.
	Post vertex first arc retrieved and printed.
*/
void doFirstArc (GRAPH *graph)
{
	int key;
	int success;
	int *addr;

	printf("Please enter key of first arc: ");
	scanf ("%d", &key);
	
	success = firstArc (graph, &key, &addr);
	
	if (success == 1)
	    printf("\nFirst arc of %d contains %d\n", key, *addr);
	else if (success == -2)
	    printf("\n\aVertex Key %d not found\n", key);
	else
	    printf("\n%d has no arcs\n", key);
	
	return;
}// doFirstArc 

/* ================================================================ */
/*	This function gets input from the user and passes it to  
	vertex insert vertex function.
	Pre	 graph exists.
	Post vertex has been inserted.
*/
void doInsertVertex (GRAPH *graph) 
{
	int *newPtr;
	int  success;

	newPtr = (int *) malloc (sizeof(int));
	if (!newPtr )
	     printf( "\aERROR: Cannot allocate data.\n" ), exit (101);
 
	printf("\nPlease enter interger to be inserted: ");
	scanf ("%d", newPtr);

	success = insertVertex (graph, newPtr);
	if (success)
	    printf("%3d inserted\n", *newPtr);
	else
	    printf("%3d NOT inserted\a\n", *newPtr);
   
	return;
}// doInsertVertex 

/* ================================================================ */
/*	This function gets input from the user and passes it to  
	arc insert vertex function.
	Pre	 graph exists.
	Post arc has been inserted.
*/
void doInsertArc (GRAPH *graph) 
{
	int  fromKey;
	int  toKey;
	int  success;

	printf("\nPlease enter from key: ");
	scanf ("%d", &fromKey);

	printf("\nPlease enter to key: ");
	scanf ("%d", &toKey);

	success = insertArc (graph, &fromKey, &toKey);
	switch (success)
	{
	    case 1 : printf("arc %3d-to-%3d inserted\n", fromKey, toKey); 
	             break;
	    case -1: printf("Overflow: arc NOT inserted\a\n");
	             break;             
	    case -2: printf("From Key %3d Error\a\n", fromKey);
	             break;
	    case -3: printf("To Key %3d Error\a\n", toKey);
	             break;
	    default: printf("Unknown error %d in doInsertArc\n", success);
	             printf("ABORTING 100\a\a\n");
	             exit  (100);
	}// switch 
	return;
}// doInsertArc 

/* ================================================================ */
/*	This function gets input from the user and passes it to  
	the delete arc function.
	Pre	 graph exists.
	Post arc has been deleted.
*/
void doDeleteArc (GRAPH *graph) 
{
	int  fromKey;
	int  toKey;
	int  success;

	printf("\nPlease enter from key: ");
	scanf ("%d", &fromKey);

	printf("\nPlease enter to key: ");
	scanf ("%d", &toKey);

	success = deleteArc (graph, &fromKey, &toKey);
	switch (success)
	{
	    case 1 : printf("arc %3d-to-%3d deleted\n", fromKey, toKey); 
	             break;
	    case -2: printf("From Key %3d Error\a\n", fromKey);
	             break;
	    case -3: printf("To Key %3d Error\a\n", toKey);
	             break;
	    default: printf("Unknown error %d in diDeleteArc\n", success);
	             printf("ABORTING 101\a\a\n");
	             exit  (101);
	}  
	return;
}// doDeleteArc 

/* ================================================================ */
/*	This function deletes a node from the graph. It asks the user for the
	key of the node to be deleted and then removes it from the graph.
	Pre	 graph must be initialized. Null graph is OK.
	Post The node is deleted and its space recylced
		-or- An error message is printed.
*/
void doDeleteVertex ( GRAPH *graph ) 
{
 	int	 dltKey;
 	int  success;
 	int *dltDataPtr;
 	 
 	printf( "\nPlease enter integer to be deleted: " );
	scanf(  "%d", &dltKey );
 
  	retrieveVertex(graph, &dltKey, &dltDataPtr);
	success = deleteVertex (graph, &dltKey);
	switch (success)
	{
	    case  1 : printf("%3d deleted\n", dltKey);
	              free (dltDataPtr);
	              break;
	    case -1 : printf("%3d's degree not zero\a\n", dltKey);
	              break;
	    case -2 : printf("%3d's key not found\a\n",   dltKey);          
	              break;
	    default : printf("UNKNOWN ERROR 101 in delete\a\n");
	              printf("ABORTING\a");
	              exit  (101);
	}
	return;
}// doDeleteVertex 

/* ================================================================ */
/*	This function compares two integers identified
	by pointers to integers.
	Pre		arguPtr and listPtr are pointers to integers
	Return	-1: arguPtr value <  listPtr value
			-0: arguPtr value == listPtr value
			+1: arguPtr value > listPtr value
*/
int compare (void *arguPtr, void *listPtr)
{
	int arguValue;
	int listValue;
	
	arguValue = *(int *)arguPtr;
	listValue = *(int *)listPtr;
	
	if (arguValue < listValue)
		return -1;
	else if (arguValue == listValue)
		return 0;
	else
		return +1;
}// compare 

/* ================================================================ */
/*	This function "processes" a graph by printing a
	sequential number and the vertex data.
	Pre     dataPtr is pointer to user data structure
	Post	Data (integer) printed.
*/
void process (void *dataPtr)
{
	static int count = 1;

	if (!dataPtr)
	   count = 1;
	else
	{
		printf("Vertex #%2d: %5d @ %p\n", count, *(int *)dataPtr, dataPtr);
 	    count++;
	}
	return;
}// process 

/* ================================================================ */
/*	This function tests the ADT utilities by calling
	each in turn and printing their results.
	Pre     graph has been created.
	Post	Results printed.
*/
void testUtilties (GRAPH *graph)
{
	printf("Tree contains %3d nodes: \n", graphCount(graph));
	if (emptyGraph(graph))
	    printf("The graph IS empty\n");
	else
	    printf("The graph IS NOT empty\n");
	if (graphFull(graph))
	    printf("The graph IS full\a\n");
	else
	    printf("The graph IS NOT full\n");
	return;
}// testUtilities

/*	=================== buildAGraph ================== 
	This function builds the graph in Figure 12-1(a)
	        using 1 for A, 2 for B, etc.
	Pre     graph has been created.
	Post	graph built.
*/
void buildAGraph12_1a (GRAPH *graph)
{
	int  i;
	int  success;
	int  fromKey;
	int  toKey;
	int *newPtr;
	
	for (i = 1; i <= 6; i++)
	{
	    newPtr = (int *) malloc (sizeof(int));
	    if (!newPtr )
	         printf( "\aERROR: Cannot allocate data.\n" ), exit (101);
	    *newPtr = i;
	    success = insertVertex (graph, newPtr);
	    if (!success)
	       printf("Insert error in buildAGraph\a\a\n"), exit(100);
	} 
	
    //	Vertices built. Now build arcs 
	fromKey = 1;
	toKey   = 2;
	success = insertArc (graph, &fromKey, &toKey);
	
	fromKey = 2;
	toKey   = 3;
	success = insertArc (graph, &fromKey, &toKey);
	
	fromKey = 3;
	toKey   = 4;
	success = insertArc (graph, &fromKey, &toKey);

	fromKey = 3;
	toKey   = 5;
	success = insertArc (graph, &fromKey, &toKey);
	
	fromKey = 5;
	toKey   = 4;
	success = insertArc (graph, &fromKey, &toKey);
	
	fromKey = 5;
	toKey   = 6;
	success = insertArc (graph, &fromKey, &toKey);
	
	fromKey = 2;
	toKey   = 5;
	success = insertArc (graph, &fromKey, &toKey);
	
	if (!success)
	   printf("Error adding arcs in buildAGraph\a\a\n"), exit(100);
	return;	
}// buildAGraph 

/* ================================================================ */
/*	This function builds a graph from an input text file	        
	Pre     graph has been created.
	        fileName
	Post	graph built.
*/
void buildAGraph (GRAPH *graph, char fileName[])
{
	FILE *fpGraph;
	int  i, n, num;
	int  success;
	int  fromKey;
	int  toKey;
	int *newPtr;
	
	if( !(fpGraph = fopen( fileName, "r")) ) 
		printf("Error opening %s\n", fileName), exit(111);
	
	fscanf(fpGraph, "%d", &n); // read the number of nodes
	for (i = 1; i <= n; i++)
	{
	    newPtr = (int *) malloc (sizeof(int));
	    if (!newPtr )
	         printf( "\aERROR: Cannot allocate data.\n" ), exit (101);
		fscanf(fpGraph, "%d", &num ); // read data in the current node
	    *newPtr = num;
	    success = insertVertex (graph, newPtr);  // insert the new node into the graph
	    if (!success)
	       printf("Insert error in buildAGraph\a\a\n"), exit(100);
	} 
	
    //	Vertices built. Now build arcs 
	while(fscanf(fpGraph, "%d %d", &fromKey, &toKey) != EOF)
	{
		success = insertArc (graph, &fromKey, &toKey);
		if (!success)
	        printf("Error adding arcs in buildAGraph\a\a\n"), exit(100);
	}

	fclose(fpGraph);

	return;	
}// buildAGraph 

/*	====================== End of Program ====================== */

/*	Results
	Standard graph (option !) traversals:
	
===============================  
Please enter your choice:  t

Begin depth first traversal
Vertex: 0x05f6f9f8 Vertex # 1:     1 @ 0x05f6f9e8
Vertex: 0x05f6fa28 Vertex # 2:     2 @ 0x05f6fa18
Vertex: 0x05f6fab8 Vertex # 3:     5 @ 0x05f6faa8
Vertex: 0x05f6fae8 Vertex # 4:     6 @ 0x05f6fad8
Vertex: 0x05f6fa88 Vertex # 5:     4 @ 0x05f6fa78
Vertex: 0x05f6fa58 Vertex # 6:     3 @ 0x05f6fa48

End depth first traversal

Begin breadth first traversal
Vertex: 0x05f6f9f8 Vertex # 1:     1 @ 0x05f6f9e8
Vertex: 0x05f6fa28 Vertex # 2:     2 @ 0x05f6fa18
Vertex: 0x05f6fa58 Vertex # 3:     3 @ 0x05f6fa48
Vertex: 0x05f6fab8 Vertex # 4:     5 @ 0x05f6faa8
Vertex: 0x05f6fa88 Vertex # 5:     4 @ 0x05f6fa78
Vertex: 0x05f6fae8 Vertex # 6:     6 @ 0x05f6fad8
End breadth first traversal
******************************************************
					PART A
******************************************************
============ Menu =============

 s :     Retrieve First Arc
 t :     Traverse graph
 x :     Test ADT utilities
 q :     Quit

===============================
Please enter your choice:  x
Tree contains   5 nodes:
The graph IS NOT empty
The graph IS NOT full

============ Menu =============
 i :     Insert new item
 d :     Delete a vertex
 a :     Insert an arc
 b :     Delete an arc
 p :     Print Vertex Adjacency
 l :     Print Graph
 r :     Retrieve Vertex
 s :     Retrieve First Arc
 t :     Traverse graph
 x :     Test ADT utilities
 q :     Quit

===============================
Please enter your choice:  t

Begin depth first traversal
Vertex # 1:    10 @ 001815F8
Vertex # 2:    90 @ 00181690
Vertex # 3:    70 @ 00181858
Vertex # 4:    20 @ 001817C0
Vertex # 5:    50 @ 00181728

End depth first traversal

Begin breadth first traversal
Vertex # 1:    10 @ 001815F8
Vertex # 2:    50 @ 00181728
Vertex # 3:    90 @ 00181690
Vertex # 4:    20 @ 001817C0
Vertex # 5:    70 @ 00181858

End breadth first traversal

============ Menu =============
 i :     Insert new item
 d :     Delete a vertex
 a :     Insert an arc
 b :     Delete an arc
 p :     Print Vertex Adjacency
 l :     Print Graph
 r :     Retrieve Vertex
 s :     Retrieve First Arc
 t :     Traverse graph
 x :     Test ADT utilities
 q :     Quit

===============================
Please enter your choice:  l
        Vertex: 10
      inDegree:  2
     outDegree:  2
Adjacency List:  50  90

        Vertex: 20
      inDegree:  1
     outDegree:  3
Adjacency List:  10  70  90

        Vertex: 50
      inDegree:  2
     outDegree:  0
Adjacency List:

        Vertex: 70
      inDegree:  2
     outDegree:  3
Adjacency List:  10  50  90

        Vertex: 90
      inDegree:  3
     outDegree:  2
Adjacency List:  20  70


============ Menu =============
 i :     Insert new item
 d :     Delete a vertex
 a :     Insert an arc
 b :     Delete an arc
 p :     Print Vertex Adjacency
 l :     Print Graph
 r :     Retrieve Vertex
 s :     Retrieve First Arc
 t :     Traverse graph
 x :     Test ADT utilities
 q :     Quit

===============================
Please enter your choice:  p
Enter vertex key: 90
Adjacency list for:   90 inDegree:  3--outDegree:  2
  20  70
============ Menu =============
 i :     Insert new item
 d :     Delete a vertex
 a :     Insert an arc
 b :     Delete an arc
 p :     Print Vertex Adjacency
 l :     Print Graph
 r :     Retrieve Vertex
 s :     Retrieve First Arc
 t :     Traverse graph
 x :     Test ADT utilities
 q :     Quit

===============================
Please enter your choice:  i

Please enter interger to be inserted: 45
 45 inserted

============ Menu =============
 i :     Insert new item
 d :     Delete a vertex
 a :     Insert an arc
 b :     Delete an arc
 p :     Print Vertex Adjacency
 l :     Print Graph
 r :     Retrieve Vertex
 s :     Retrieve First Arc
 t :     Traverse graph
 x :     Test ADT utilities
 q :     Quit

===============================
Please enter your choice:  l
        Vertex: 10
      inDegree:  2
     outDegree:  2
Adjacency List:  50  90

        Vertex: 20
      inDegree:  1
     outDegree:  3
Adjacency List:  10  70  90

        Vertex: 45
      inDegree:  0
     outDegree:  0
Adjacency List:

        Vertex: 50
      inDegree:  2
     outDegree:  0
Adjacency List:

        Vertex: 70
      inDegree:  2
     outDegree:  3
Adjacency List:  10  50  90

        Vertex: 90
      inDegree:  3
     outDegree:  2
Adjacency List:  20  70


============ Menu =============
 i :     Insert new item
 d :     Delete a vertex
 a :     Insert an arc
 b :     Delete an arc
 p :     Print Vertex Adjacency
 l :     Print Graph
 r :     Retrieve Vertex
 s :     Retrieve First Arc
 t :     Traverse graph
 x :     Test ADT utilities
 q :     Quit

===============================
Please enter your choice:  a

Please enter from key: 45

Please enter to key: 90
arc  45-to- 90 inserted

============ Menu =============
 i :     Insert new item
 d :     Delete a vertex
 a :     Insert an arc
 b :     Delete an arc
 p :     Print Vertex Adjacency
 l :     Print Graph
 r :     Retrieve Vertex
 s :     Retrieve First Arc
 t :     Traverse graph
 x :     Test ADT utilities
 q :     Quit

===============================
Please enter your choice:  p
Enter vertex key: 45
Adjacency list for:   45 inDegree:  0--outDegree:  1
  90
============ Menu =============
 i :     Insert new item
 d :     Delete a vertex
 a :     Insert an arc
 b :     Delete an arc
 p :     Print Vertex Adjacency
 l :     Print Graph
 r :     Retrieve Vertex
 s :     Retrieve First Arc
 t :     Traverse graph
 x :     Test ADT utilities
 q :     Quit

===============================
Please enter your choice:  t

Begin depth first traversal
Vertex # 1:    10 @ 001815F8
Vertex # 2:    90 @ 00181690
Vertex # 3:    70 @ 00181858
Vertex # 4:    20 @ 001817C0
Vertex # 5:    50 @ 00181728
Vertex # 6:    45 @ 001859E0

End depth first traversal

Begin breadth first traversal
Vertex # 1:    10 @ 001815F8
Vertex # 2:    50 @ 00181728
Vertex # 3:    90 @ 00181690
Vertex # 4:    20 @ 001817C0
Vertex # 5:    70 @ 00181858
Vertex # 6:    45 @ 001859E0

End breadth first traversal

============ Menu =============
 i :     Insert new item
 d :     Delete a vertex
 a :     Insert an arc
 b :     Delete an arc
 p :     Print Vertex Adjacency
 l :     Print Graph
 r :     Retrieve Vertex
 s :     Retrieve First Arc
 t :     Traverse graph
 x :     Test ADT utilities
 q :     Quit

===============================
Please enter your choice:  r
Please enter key to be found: 90

Key found. Contains 90

============ Menu =============
 i :     Insert new item
 d :     Delete a vertex
 a :     Insert an arc
 b :     Delete an arc
 p :     Print Vertex Adjacency
 l :     Print Graph
 r :     Retrieve Vertex
 s :     Retrieve First Arc
 t :     Traverse graph
 x :     Test ADT utilities
 q :     Quit

===============================
Please enter your choice:  s
Please enter key of first arc: 45

First arc of 45 contains 90

============ Menu =============
 i :     Insert new item
 d :     Delete a vertex
 a :     Insert an arc
 b :     Delete an arc
 p :     Print Vertex Adjacency
 l :     Print Graph
 r :     Retrieve Vertex
 s :     Retrieve First Arc
 t :     Traverse graph
 x :     Test ADT utilities
 q :     Quit

===============================
Please enter your choice:  q
End Explore Graphs
Memory Leak
Press any key to continue . . .

*************************************************
					PART B
*************************************************

Begin depth first traversal
Vertex # 1:    10 @ 00045428
Vertex # 2:    90 @ 000454C0
Vertex # 3:    80 @ 00045688
Vertex # 4:    40 @ 000455F0
Vertex # 5:    50 @ 00045558
Vertex # 6:    60 @ 00045720

End depth first traversal

Begin breadth first traversal
Vertex # 1:    10 @ 00045428
Vertex # 2:    90 @ 000454C0
Vertex # 3:    40 @ 000455F0
Vertex # 4:    80 @ 00045688
Vertex # 5:    50 @ 00045558
Vertex # 6:    60 @ 00045720

End breadth first traversal

*/	
