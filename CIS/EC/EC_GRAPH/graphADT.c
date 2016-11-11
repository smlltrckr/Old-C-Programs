/*	This header file contains the graph ADT. Note that it also requires
	the stack and queue ADTs.

	Written by: G & F
	Date:       2/98
	
    Brooks/Cole Publishing Company
	An International Thomson Publishing Company
	Copyright 1998. All Rights Reserved
*/

#include "graphADT.h"

/*  =================== insertVertex =================== 
	This function inserts new data into the graph.
	Pre    graph is a pointer to a valid graph structure.
	Post   data have been inserted or abort if memory O/F.
*/
int insertVertex (GRAPH *graph, void  *dataInPtr) 
{
	VERTEX *newPtr;
	VERTEX *locPtr;
	VERTEX *predPtr;
	
	if (newPtr = (VERTEX *)malloc(sizeof (VERTEX)))
	{		
	    newPtr->pNextVertex  = NULL;
	    newPtr->dataPtr      = dataInPtr;
	    newPtr->inDegree     = 0;
	    newPtr->outDegree    = 0;
	    newPtr->processed    = 0;
	    newPtr->pArc         = NULL;
	    (graph->count)++;
	          
		// Now find insertion point 
		locPtr = graph->first;
		if (!locPtr)
			// Empty graph. Insert at beginning 
			graph->first = newPtr;
		else
		{
			predPtr = NULL;
			while (locPtr && (graph->compare(dataInPtr, locPtr->dataPtr) > 0))
			{
				predPtr = locPtr;
				locPtr  = locPtr->pNextVertex;
			} 
			if (!predPtr) // Insert before first vertex 
				graph->first = newPtr;
			else
				predPtr->pNextVertex = newPtr;
			newPtr->pNextVertex = locPtr;
		}

		return 1;
	}

	return 0;
}// insertVertex   

/* ==================== Program deleteVertex ==================== 
	Deletes an existing vertex only if its degree is zero
	Pre    Graph is pointer to a graph head structure
           dltKey is the key of the vertex to be deleted
	Post   Vertex deleted if degree zero
	       -or- An error code is returned.
    Return Success +1 if successful
                   -1 if degree not zero
                   -2 if dltKey not found
*/
int deleteVertex (GRAPH *graph, void  *dltKey)
{
	VERTEX  *predPtr;
	VERTEX  *walkPtr;

	if (!graph->first)
	    return -2;

	// Locate vertex to be deleted 
	predPtr = NULL;
	walkPtr = graph->first;
	while (walkPtr && (graph->compare(dltKey, walkPtr->dataPtr) > 0))
	{
	    predPtr = walkPtr;
	    walkPtr = walkPtr->pNextVertex;
	} 
	if (!walkPtr || graph->compare(dltKey, walkPtr->dataPtr) != 0)
	   return -2;
	   
	// Found vertex. Test degree 
	if ((walkPtr->inDegree > 0) || (walkPtr->outDegree > 0))
	    return -1;
	
	// OK to delete 
	if (!predPtr)
	    graph->first         = walkPtr->pNextVertex;
	else
	    predPtr->pNextVertex = walkPtr->pNextVertex;
	--graph->count;
	free(walkPtr);
	return 1;
}// deleteVertex 

/* ====================== insertArc ====================== 
	Adds an arc vertex between two vertices.
	Pre    graph is a pointer to a graph
	       fromKey is pointer to key of start vertex
	       toKey   is pointer to key of destination vertex
	Post   Arc added to adjacency list
    Return success  +1 if successful
                    -1 if memory overflow
                    -2 if fromKey not found
                    -3 if toKey not found
*/
int insertArc (GRAPH *graph, void  *pFromKey, void  *pToKey)
{
	ARC *newPtr;
	ARC *arcPredPtr;
	ARC *arcWalkPtr;
	
	VERTEX *vertFromPtr;
	VERTEX *vertToPtr;

	newPtr = (ARC *)malloc(sizeof(ARC));
	if (!newPtr)
	   return (-1);

	// Locate source vertex 
	vertFromPtr = graph->first;
	while (vertFromPtr && (graph->compare(pFromKey, vertFromPtr->dataPtr) > 0))
	{
	    vertFromPtr = vertFromPtr->pNextVertex;
	} 
	if (!vertFromPtr || (graph->compare(pFromKey, vertFromPtr->dataPtr) != 0))
	   return (-2);
	
	// Now locate to vertex 
	vertToPtr   = graph->first;
	while (vertToPtr && graph->compare(pToKey, vertToPtr->dataPtr) > 0)
	{
	    vertToPtr   = vertToPtr->pNextVertex;
	} 
	if (!vertToPtr || (graph->compare(pToKey, vertToPtr->dataPtr) != 0))
	   return (-3);
	   
	// From and to vertices located. Insert new arc 
	++vertFromPtr->outDegree;
	++vertToPtr  ->inDegree;
	newPtr->destination = vertToPtr;
	if (!vertFromPtr->pArc)
	{
	    // Inserting first arc for this vertex 
	    vertFromPtr->pArc = newPtr;
	    newPtr-> pNextArc = NULL;
	    return 1;
	   } // if new arc 
	
	// Find insertion point in adjacency (arc) list 
	arcPredPtr = NULL;
	arcWalkPtr = vertFromPtr->pArc;
	while (arcWalkPtr && graph->compare(pToKey, arcWalkPtr->destination->dataPtr) >= 0)
	{
	    arcPredPtr = arcWalkPtr;
	    arcWalkPtr = arcWalkPtr->pNextArc;
	} 
	
	if (!arcPredPtr)  // Insertion before first arc 
	    vertFromPtr->pArc    = newPtr;
	else
	    arcPredPtr->pNextArc = newPtr;
	newPtr->pNextArc = arcWalkPtr;
    return 1;
}// insertArc	

/* ====================== deleteArc ====================== 
	Deletes an existing arc 
	Pre    Graph is pointer to a graph head structure
           fromKey is the key of the start vertex and toKey is
         the key of the destination vertex to be deleted
	Post   Arc deleted 
    Return Success +1 if successful
                   -2 if fromKey not found
                   -3 if toKey not found
*/
int deleteArc (GRAPH *graph, void  *fromKey, void  *toKey)
{
	VERTEX *fromVertexPtr;
	VERTEX *toVertexPtr;
	
	ARC *preArcPtr;
	ARC *arcWalkPtr;

	if (!graph->first)
	    return -2;

	// Locate source vertex 
	fromVertexPtr = graph->first;
	while (fromVertexPtr && (graph->compare(fromKey,
	                         fromVertexPtr->dataPtr) > 0))
	    fromVertexPtr = fromVertexPtr->pNextVertex;

	if (!fromVertexPtr || graph->compare(fromKey,
	                          fromVertexPtr->dataPtr) != 0)
	   return -2;
	   
	// Locate destination vertex in adjacency list 
	if (!fromVertexPtr->pArc)
	    return -3;
	
	preArcPtr = NULL;
	arcWalkPtr = fromVertexPtr->pArc;
	while (arcWalkPtr && (graph->compare(toKey, arcWalkPtr->destination->dataPtr) > 0))
	{
	    preArcPtr  = arcWalkPtr;
	    arcWalkPtr = arcWalkPtr->pNextArc;
	} 
	if (!arcWalkPtr || (graph->compare(toKey,
	               arcWalkPtr->destination->dataPtr) != 0))
	    return -3;
	toVertexPtr = arcWalkPtr->destination;
	
	// from, toVertex & arcPtr located. Delete arc 
	--fromVertexPtr->outDegree;     
	--toVertexPtr -> inDegree;
	if (!preArcPtr)  // Deleting first arc 
	    fromVertexPtr->pArc  = arcWalkPtr->pNextArc;
	else
	    preArcPtr->pNextArc = arcWalkPtr->pNextArc;
	free (arcWalkPtr);

	return 1;
}// deleteArc 

/*	===================== depthFirst =====================
	Process the data in the graph in depth-first order.
	   Pre   graph is the a pointer to graph head
	   Post  vertices "processed".
	   Return 1 - success
	          0 - memory overflow

	Processed Flag: 0 = not processed
	                1 = pushed into stack
	                2 = processed
*/
int depthFirst (GRAPH *graph, void (*process) (void *dataPtr))
{
	int success;
	
	VERTEX *walkPtr;
	VERTEX *vertexPtr;
	VERTEX *vertToPtr;
	STACK  *stack;
	ARC    *arcWalkPtr;
	
	if (!graph->first)
	    return 0;

	// Set processed flags to not processed 
	walkPtr = graph->first;
	while (walkPtr)
	{
	    walkPtr->processed = 0;
	    walkPtr            = walkPtr->pNextVertex;
	} 
	
	// Process each vertex in list 
	stack = createStack ();
	walkPtr = graph->first;
	while (walkPtr)
	{
	    if (walkPtr->processed < 2)
	    {
	        if (walkPtr->processed < 1)
	        {   // Push & set flag to pushed 
	            success = pushStack (stack, walkPtr);
	            if (!success)
	                   return 0;
	            walkPtr->processed = 1;
	           } // if processed < 1 
	       } // if processed < 2 
	    // Process descendents of vertex at stack top 
	    while (!emptyStack (stack))
	    {
	        vertexPtr = popStack(stack);
	        process (vertexPtr->dataPtr);
	        vertexPtr->processed = 2;
	        
	        // Push all vertices from adjacency list 
	        arcWalkPtr = vertexPtr->pArc;
	        while (arcWalkPtr)
	        {
	            vertToPtr = arcWalkPtr->destination;
	            if (vertToPtr->processed == 0)
	            {
	                success = pushStack(stack, vertToPtr);
	                if (!success)
						return 0;
	                vertToPtr->processed = 1;
	            } 
	            arcWalkPtr = arcWalkPtr->pNextArc;
	        } 
	           
	    } 
	    walkPtr = walkPtr->pNextVertex;
	   } 
	destroyStack(stack); 
	return 1;
}// depthFirst 

/*	================== breadthFirst ================== */
/*	 Process the data of the graph in breadth-first order. 
	   Pre  graph is a pointer of a graph head structure
	   Post graph has been processed.
	   Return 1 - success
	          0 - fail

	Processed Flag: 0 = not processed
	                1 = enqueued
	                2 = processed
*/
int breadthFirst (GRAPH *graph, void (*process) (void *dataPtr))
{
	int success;
	
	VERTEX *walkPtr;
	VERTEX *vertexPtr;
	VERTEX *vertToPtr;
	QUEUE  *queue;	
	ARC    *arcWalkPtr;
	
	if (!graph->first)
	    return 0;
 
	// Set processed flags to not processed 
	walkPtr = graph->first;
	while (walkPtr)
	{
	    walkPtr->processed = 0;
	    walkPtr            = walkPtr->pNextVertex;
	} 
	
	// Process each vertex in list 
	queue = createQueue ();
	walkPtr = graph->first;
	while (walkPtr)
	{
	    if (walkPtr->processed < 2)
	    {
	        if (walkPtr->processed < 1)
	        {
	            // Enqueue & set flag to queue 
	            success = enqueue(queue, walkPtr);
	            if (!success)
	               return 0;
	            walkPtr->processed = 1;
	        } 
	    } 
	    // Process descendents of vertex at queue front 
	    while (!emptyQueue (queue))
	    {
	        dequeue(queue, &vertexPtr);
	        process (vertexPtr->dataPtr);
	        vertexPtr->processed = 2;
	        
	        // Enqueue all vertices from adjacency list 
	        arcWalkPtr = vertexPtr->pArc;
	        while (arcWalkPtr)
	        {
	            vertToPtr = arcWalkPtr->destination;
	            if (vertToPtr->processed == 0)
	            {
	                success = enqueue(queue, vertToPtr);
	                if (!success)
	                   return 0;
	                vertToPtr->processed = 1;
	            } 
	            arcWalkPtr = arcWalkPtr->pNextArc;
	        } 	           
	    } 
	    walkPtr = walkPtr->pNextVertex;
	   }
	destroyQueue(queue); 

	return 1;
 }// breadthFirst 
 
/*	======================= Extra Functions =======================
	The following functions are not included in the text but are
	required for the ADT. Some have been included in the text as
	Practice Sets.
*/
/*	=============== createGraph ==============
	Allocates dynamic memory for a linked list head
	node and returns its address to caller
	Pre    compare is address of compare function used whenever
	       two node entries need to be compared.
	Post   head allocated or error returned
	Return head node pointer or null if memory overflow 
*/
GRAPH *createGraph (int (*compare) (void *argu1, void *argu2))
{
	GRAPH *graph;

	graph = (GRAPH *) malloc (sizeof (GRAPH));
	if (graph)
	{
		 graph->first   = NULL;
		 graph->count   = 0;
		 graph->compare = compare;
	} 

	return graph;
}// createGraph 


/*	=============== emptyGraph ============== 
	Returns true if graph is empty, false if any data.
	Pre   graph has been created. May be null.
	Post  returns boolean
*/
int emptyGraph (GRAPH *graph)
{
	return (graph->count == 0);
}// emptyGraph 

/*	=============== graphFull ============== 
	If there is no room for another node, returns true.
	Pre      graph has been created.
	Returns  True if no room for another insert,
	         false if room.
*/
int graphFull (GRAPH *graph)
{
	VERTEX *newPtr;
	
	newPtr = (VERTEX *)malloc(sizeof (VERTEX));
	if (newPtr)
	{
		 free (newPtr);
		 return 0;
	}
	else
	     return 1;
}// graphFull 

/*	=============== graphCount ==============
	Returns number of nodes in graph.
	Pre   Tree has been created.
	Post  returns boolean  
*/
int graphCount (GRAPH *graph)
{
	return (graph->count);
}// graphCount 

/* ============================= retrieveVertex ============================= 
	Data contained in vertex identified by key rturned to caller. 
	Pre    Graph is pointer to a graph head structure
           keyPtr is the key of the vertex data to be retrieved
           pDataOut is a pointer for data pointer
	Post   Vertex data pointer copied to pDataOut
    Return Success +1 if successful
                   -2 if fromKey not found
*/
int retrieveVertex (GRAPH *graph, void  *keyPtr, void **pDataOut)
{
    VERTEX *walkPtr;

	if (!graph->first)
	    return -2;
	
	walkPtr = graph->first;
	while (walkPtr && (graph->compare
	                    (keyPtr, walkPtr->dataPtr) > 0))
	    walkPtr = walkPtr->pNextVertex;
	if (graph->compare(keyPtr, walkPtr->dataPtr) == 0)
    {
	    *pDataOut = walkPtr->dataPtr;
	    return 1;
	} 
	else
	   return -2;
}// retrieveVertex 
                    
 
/* ============================= firstArc ============================= 
	Key of first arc from vertex is located and passed back to caller. 
	Pre    Graph is pointer to a graph head structure
           keyPtr is the key of the vertex data
           pDataOut is a pointer for data pointer
	Post   Vertex data pointer copied to pDataOut
    Return Success +1 if successful
                   -2 if fromKey not found
                   -3 no destination key (no arc)
*/
int firstArc (GRAPH *graph, 
              void  *keyPtr,
              void **pDataOut)
{
    VERTEX *walkPtr;   
    ARC    *toPtr;

	if (!graph->first)
	    return -2;
	
	walkPtr = graph->first;
	while (walkPtr && (graph->compare(keyPtr, walkPtr->dataPtr) > 0))
	    walkPtr = walkPtr->pNextVertex;
	if (graph->compare(keyPtr, walkPtr->dataPtr) == 0)
	{
	    if (walkPtr->pArc)
	    {
	        toPtr     = walkPtr->pArc;
	        *pDataOut = toPtr->destination->dataPtr;
	        return 1;
	    } 
	    else
	        return -3;
	} 
	else
	   return -2;
}// firstArc 

 
/* ============================= firstArc ============================= 
	Release memory
	Pre    Graph is pointer to a graph head structure           
	Post   
    Return NULL
*/
GRAPH  *destroyGraph(GRAPH *graph)
{
	VERTEX *pVertexWalk, *pVertexDel;
	ARC *pArcWalk, *pArcDel;


	pVertexWalk = graph->first; 
	while (pVertexWalk)
    {
		pArcWalk = pVertexWalk->pArc; 
	    while (pArcWalk)
		{
			pArcDel = pArcWalk;
	        pArcWalk = pArcWalk->pNextArc; // free a node in the adjacency list
			free(pArcDel);
		} 

		pVertexDel = pVertexWalk;
		pVertexWalk = pVertexWalk->pNextVertex;
		free(pVertexDel->dataPtr); // free data in the current node
		free(pVertexDel); // free a vertex
	}

	free(graph);  // free header of the graph

	return NULL;
}
 
/*	======================= END GRAPH ADT ======================= */
/*	======================= END GRAPH ADT ======================= */
/*	======================= END GRAPH ADT ======================= */

/*	The following functions are not part of the ADT. They are 
	included to provide debugging output.
*/
//#if (DEBUG)
/*  ============================= printVertex ============================= 
	This function prints a graph vertex and its adjacency list 
	
	NOTE: THIS IS NOT AN APPLICATION ADT FUNCTION. IT IS 
	USED ONLY FOR DEBUGGING PURPOSES.
	
	Pre	 Graph must be initialized. Null graph is OK.
	     pFromKey is key of vertex to be prited.
	Post Graph has been printed.
*/
void printVertex (GRAPH *graph, void  *pFromKey) 
{
	VERTEX *pVertexWalk;
	ARC   *pArcWalk;
//	void  *pVoid;
	
	// Locate vertex 
	pVertexWalk = graph->first;
	while (pVertexWalk && ((graph->compare(pFromKey, pVertexWalk->dataPtr) > 0)))
	    pVertexWalk = pVertexWalk->pNextVertex;
	if (!pVertexWalk || ((graph->compare(pFromKey, pVertexWalk->dataPtr) != 0)))
	{
	    //printf("\aVertex %d does not exist\n", *pFromKey);
		printf("\aVertex %d does not exist\n", *(int *)pFromKey);
	    return;
	} 
	
	printf("Adjacency list for: %4d ", *(int *)pFromKey);
	printf("inDegree: %2d--outDegree: %2d\n", 
	        pVertexWalk->inDegree, pVertexWalk->outDegree);

	pArcWalk = pVertexWalk->pArc; 
	while (pArcWalk)
    {
	     printf("%4d", *(int *)pArcWalk->destination->dataPtr);	             
	     pArcWalk = pArcWalk->pNextArc;
    } 
    return;
}// printVertex 


/* ========================================================== 
	Prints the graph
	Pre    Graph is pointer to a graph head structure           
	Post   graph printed
    Return nothing
*/
void printGraph(GRAPH *graph)
{
	
	VERTEX *pVertexWalk;
	ARC   *pArcWalk;


	pVertexWalk = graph->first;
	while ( pVertexWalk )
	{		
		// print adjacency list for the current vertex
		printf("        Vertex: %2d\n", *(int *)pVertexWalk->dataPtr);
		printf("      inDegree: %2d\n"
			   "     outDegree: %2d\n", pVertexWalk->inDegree, pVertexWalk->outDegree);
        printf("Adjacency List:" );

		pArcWalk = pVertexWalk->pArc; 
		while (pArcWalk)
		{
			 printf("%4d", *(int *)pArcWalk->destination->dataPtr);	             
			 pArcWalk = pArcWalk->pNextArc;
		} 
		printf("\n\n");
		// move to the next vertex in the graph
		pVertexWalk = pVertexWalk->pNextVertex;		
	}
    
	return;
}

//#endif

/*	========================== End of p12Graph.h Library ========================== */
