/* 
   Quick Sort

   One of the well known advanced sorting algorithms was developed in 1962
   by C.A.R. Hoare. 

   Average time is O(n logn). 
   Worst-case time is O(n2). // array is already sorted
      
*/

#include <stdio.h>

#define SIZE 100

void quickSort       (int sortData[ ], int left, int right);
void quickInsertion	 (int sortData[ ], int first, int last); 
void medianLeft		 (int sortData[ ], int left, int right); 

void printAry        ( int ary[], int n );


int main ( void )
{
	int listSize   = 10;
	int list[SIZE] = { 20, 30, 80, 15, 50, 10, 40, 60, 25, 70 };
	

	printAry( list, listSize );

	quickSort ( list, 0, listSize - 1 );

	printAry( list, listSize );
	
	return 0;
}

//	=================== Program 12-7 quickInsertion ==================== 

/*	===================== quickSort ====================== 
	Array, sortData[left..right] sorted using recursion.
	   Pre  sortData is an array of data to be sorted
	        left identifies first element of sortData 
	        right identifies last element of sortData 
	   Post sortData array is sorted
*/

void quickSort (int sortData[ ], int left, int right)
{
	#define MIN_SIZE 16
	
	int sortLeft;
	int sortRight;
	int pivot;
	int hold;


	if ((right - left) > MIN_SIZE) {
	   medianLeft (sortData, left, right);
	   pivot     = sortData [left];
	   sortLeft  = left + 1;
	   sortRight = right;
	   while (sortLeft <= sortRight){
	      // Find key on left that belongs on right 
	      while (sortData [sortLeft] < pivot) 
	         sortLeft = sortLeft + 1;
	      // Find key on right that belongs on left 
	      while (sortData[sortRight] >= pivot)
	         sortRight = sortRight - 1;
	      if (sortLeft <= sortRight){
	         hold                = sortData[sortLeft];
	         sortData[sortLeft]  = sortData[sortRight];
	         sortData[sortRight] = hold;
	         sortLeft            = sortLeft  + 1;
	         sortRight           = sortRight - 1;
	      } // if 
	   } // while 
	   // Prepare for next pass 
	   sortData [left]         = sortData [sortLeft - 1];
	   sortData [sortLeft - 1] = pivot;
	   if (left < sortRight)
	       quickSort (sortData, left, sortRight - 1);
	   if (sortLeft < right)
	       quickSort (sortData, sortLeft, right);
	} // if right 
	else
	  quickInsertion (sortData, left, right);
    return;
}	// quickSort 

/*	=================== quickInsertion ==================== 
	Sort data[1Élast] using insertion sort. data is 
	divided into sorted and unsorted lists. With each 
	pass, the first element in unsorted list is inserted 
	into the sorted list. This is a special version of the 
	insertion sort modified for use with quick sort.
	   Pre  data must contain at least one element
	        first is index to first element in data
	        last is index to last element in data
	   Post data has been rearranged
*/
void quickInsertion (int data[], int first, int last)
{
//	Local Definitions 
	int hold;
	int walker;
	int current;

//	Statements 
	for (current = first + 1; current <= last; current++){
	    hold   = data[current];
	    walker = current - 1;
	    while (walker >= first && hold < data[walker]){
	           data[walker + 1] = data[walker];
	           walker               = walker - 1;
	    } // while 
	    data[walker + 1] = hold;
	} // for 
	return;
}	// quickInsertion 

//	=================== Program 12-8 medianLeft ==================== 

/*	=================== medianLeft ==================== 
	Find the median value of an array, 
	sortData[left..right], and place it in the 
	location sortData[left].
	   Pre  sortData is array of at least three elements
	        left and right are boundaries of array
	   Post median value placed at sortData[left]
*/
void medianLeft (int sortData[], int left, int right)
{
//	Local Definitions 
	int mid;
	int hold;

//	Statements 
	// Rearrange sortData so median is middle location 
	mid = (left + right) / 2;
	if (sortData[left] > sortData[mid]){
	    hold            = sortData[left];
	    sortData[left]  = sortData[mid];
	    sortData[mid]   = hold;
	} // if 
	if (sortData[left] > sortData[right]){
	    hold            = sortData[left];
	    sortData[left]  = sortData[right];
	    sortData[right] = hold;
	} // if 
	if (sortData[mid]  > sortData[right]){
	    hold            = sortData[mid];
	    sortData[mid]   = sortData[right];
	    sortData[right] = hold;
	} // if 
	   
	// Median is in middle. Exchange with left 
	hold           = sortData[left];
	sortData[left] = sortData[mid];
	sortData[mid]  = hold;

	return;
}	// medianLeft 

/* ================================= */
void printAry( int ary[], int n )
{
	int i;

	printf( "\n" );
	for( i = 0; i < n; i++ )
	{
		printf( "%4d", ary[i] );
		if( (i + 1) % 19 == 0 )
			printf( "\n" );
	}
	printf( "\n" );

	return;
}