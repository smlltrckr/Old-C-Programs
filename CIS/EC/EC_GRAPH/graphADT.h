/*	This header file contains the graph ADT. Note that it also requires
	the stack and queue ADTs.

	Written by: G & F
	Date:       2/98
	
    Brooks/Cole Publishing Company
	An International Thomson Publishing Company
	Copyright 1998. All Rights Reserved
*/

#include <stdio.h>	
#include "stackADT.h"
#include "queueADT.h"
#include <stdlib.h>
//	=============== Type Definitions =============== 
struct vertex;
struct arc;

typedef struct
{
    int     count; 
    struct  vertex *first; 
    int    (*compare) (void *argu1, void *argu2); 
} GRAPH;

typedef struct vertex
{
	 struct vertex  *pNextVertex;
	 void           *dataPtr;
	 int            inDegree;
	 int            outDegree;
	 short          processed;
	 struct arc    *pArc;
} VERTEX;

typedef struct arc
{
	 VERTEX       *destination;
	 struct   arc *pNextArc;
} ARC;	

//	=============== Prototype Delcarations =============== 
GRAPH  *createGraph (int  (*compare) (void *argu1, void *argu2));
GRAPH  *destroyGraph(GRAPH *graph);

int insertVertex   (GRAPH *graph, void  *dataInPtr);
int deleteVertex   (GRAPH *graph, void  *dltKey);
int insertArc      (GRAPH *graph, void  *pFromKey, 
                                  void  *pToKey);
int deleteArc      (GRAPH *graph, void  *pFromKey,
                                  void  *pToKey);
int retrieveVertex (GRAPH *graph, void  *pKey,
                                  void **pDataOut);
int firstArc       (GRAPH *graph, void  *pKey,
                                  void **pDataOut);
int emptyGraph     (GRAPH *graph);
int graphFull      (GRAPH *graph);
int graphCount     (GRAPH *graph);

int depthFirst    (GRAPH *graph, void (*process) (void *dataPtr));
int breadthFirst  (GRAPH *graph, void (*process) (void *dataPtr));

GRAPH  *destroyGraph(GRAPH *graph);

/*	========================== End of Graph Library ========================== */
