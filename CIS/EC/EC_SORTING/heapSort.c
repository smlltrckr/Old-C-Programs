/* 
   Heap Sort

   One of the advanced sorting algorithms to sort an array is the heap sort.
   It is based on the selection sort algorithm. Instead of traversing the 
   array to find the smallest element, first the array is converted into a
   min-heap (O(nlogn) run time), then the sorting actually begins: n-1 times
   find smallest (logn run time) and exchange.

   It is not a stable sorting algorithm.

      
   It has O(nlogn) complexity
*/

#include <stdio.h>

#define SIZE 100

void printAry      ( int ary[], int n );

void heapSort   (int  list[ ], int last);
void reheapUp   (int* heap,    int newNode);
void reheapDown (int* heap,    int root, int last);

int main ( void )
{
	int listSize   = 10;
	int list[SIZE] = { 20, 30, 80, 15, 50, 10, 40, 60, 25, 70 };
	

	printAry( list, listSize );

	heapSort ( list, listSize );

	printAry( list, listSize );
	
	return 0;
}


/*	===================== heapSort =====================
	Sort an array, list0 .. last], using a heap.
	   Pre  list must contain at least one item
	        last contains index to last element in list
	   Post list has been sorted smallest to largest
*/
void heapSort (int list[ ], int size)
{
	int sorted;
	int holdData;
	int walker;
	int last = size - 1;

	// Create Heap 
	for (walker = 1; walker <= last; walker++)
		reheapUp (list, walker);
	
	// Heap created. Now sort it. 
	sorted = last;
	while (sorted > 0){
	    holdData     = list[0];
	    list[0]      = list[sorted];
	    list[sorted] = holdData;
	    sorted--;
	    reheapDown (list, 0, sorted);
	} 
	return;
}	

/*	==================== reheapUp ==================== 
	Reestablishes heap by moving data in child up to
	correct location heap array.
	   Pre  heap is array containing an invalid heap
	        newNode is index location to new data in heap
	   Post newNode has been inserted into heap
*/
void reheapUp (int* heap, int newNode) 
{
	int parent;
	int hold;

	// if not at root of heap 
	if (newNode){
	   	parent = (newNode - 1)/ 2;
	    if ( heap[newNode] > heap[parent] ){
	        // child is greater than parent 
	        hold          = heap[parent]; 
	        heap[parent]  = heap[newNode];
	        heap[newNode] = hold;
	        reheapUp (heap, parent);
	       } 
	}
	return;
}// reheapUp 

/*	==================== reheapDown ==================== 
	Reestablishes heap by moving data in root down to its
	correct location in the heap.
	   Pre  heap is an array of data
	        root is root of heap or subheap
	        last is an index to the last element in heap
	   Post heap has been restored
*/
void reheapDown   (int* heap, int root, int last)
{
	int hold;
	int leftKey;
	int rightKey;
	int largeChildKey;
	int largeChildIndex;
	
	if ((root * 2 + 1) <= last){
	    // There is at least one child 	
	    leftKey   = heap[root * 2 + 1];
	    if ((root * 2 + 2) <= last)
	       rightKey  = heap[root * 2 + 2];
	    else
	       rightKey  = -1;
	       
	    // Determine which child is larger 
		if (leftKey > rightKey){ 
	        largeChildKey   = leftKey;
	        largeChildIndex = root * 2 + 1;
	    } 
		else{
	        largeChildKey   = rightKey;
	        largeChildIndex = root * 2 + 2;
	    }  

	    // Test if root > larger subtree 
	    if (heap[root] < heap[largeChildIndex]){
	         // parent < children 
	         hold                  = heap[root];
	         heap[root]            = heap[largeChildIndex];
	         heap[largeChildIndex] = hold;
	         reheapDown (heap, largeChildIndex, last);
	    } 
	} 
	return;
}// reheapDown 

/* ================================= */
void printAry( int ary[], int n )
{
	int i;

	printf( "\n" );
	for( i = 0; i < n; i++ )
		printf( "%3d", ary[i] );
	printf( "\n" );

	return;
}