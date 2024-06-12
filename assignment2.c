#include <cs3050.h>
#include "stdio.h"
void heapify(void * array, int i, size_t nitems, size_t size, int (*CompareFunc)(const void *, const void*));
void buildHeap(void * array, size_t nitems, size_t size, int (*CompareFunc)(const void *, const void*));
void heapsort(void *array, size_t nitems, size_t size, int (*CompareFunc)(const void *, const void*));

void heapify(void * array, int i, size_t nitems, size_t size, int (*CompareFunc)(const void *, const void*))
{
	//indexes for left, right, and placeholder for largest value
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int largest = i;

	//case for item on left being bigger than largest
	if (l <= nitems && CompareFunc(array + (l * size),array + (i * size)) > 0)
	{
		largest = l;
	}

	//case for item on right being larger
	if (r <= nitems && CompareFunc(array + (r * size), array + (largest * size)) > 0)
	{
		largest = r;
	}

	//if the largest value's index is not the current index, they are swapped and heapify is recursively called 
	if (largest != i)
	{
		Swap(array + (i * size), array + (largest * size), size);
		heapify(array, largest, nitems - 1, size, CompareFunc);
	}
}

void buildHeap(void * array, size_t nitems, size_t size, int (*CompareFunc)(const void *, const void*))
{
	//builds heap using heapify moving downward from nitems/2 - 1
	for (int i = (nitems/2) - 1; i >= 0; i--)
	{
		heapify(array, i, nitems - i, size, CompareFunc);
	}
}

void heapsort(void *array, size_t nitems, size_t size, int (*CompareFunc)(const void *, const void*))
{
	//call buildHeap
	buildHeap(array, nitems, size, CompareFunc);

	//variable for length/size of heap
	int length = nitems - 1;

	//sort the heap using swaps and heapify
	while (length > 0)
	{
		Swap(array, array + (size * length), size);
		length--;
		heapify(array, 0, length, size, CompareFunc);
	}
}