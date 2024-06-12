#include <cs3050.h>

void bubblesort(void *array, 
				size_t nitems, 
				size_t size, 
				int (*CompareFunc)(const void *, const void*))
{
	for (int i=0;i<nitems;i++)
	{
		for (int j=0;j<nitems-1;j++)
		{
			void * item1 = array + j*size;
			void * item2 = array + (j+1)*size;
			if (CompareFunc(item1,item2)>0)
			{
				Swap(item1,item2,size);
			}
		}
	}
}

void insertionsort(void *array, size_t nitems, size_t size, int (*CompareFunc)(const void *, const void*))
{
	if (nitems == 0)
	{
		return;
	}

	//Copy solution
	for (int i = 1; i < nitems; i++)
	{
		//init j variable for while loop use
		int j = i - 1;

		//init item1, holds the value of array[i] so it isn't lost in the swap
		void * item1 = malloc(sizeof(void *));
		Copy(item1, array + (j + 1) * size, size);

		//init item2
		void * item2 = array + (j * size);
		
		//CompareFunc: 1st is greater = > 0, 2nd is greater = <0, equal = 0
		while (j >= 0 && CompareFunc(item2, item1) > 0)
		{
			//copy item2 to array[j+1] destination, size is used because value type is unknown
			Copy(item2 + size, item2, size);
			j--;
			//item2 now points to array[j-1]
			item2 -= size;
		}
		//+ size is used to allocate the space, value in item1 copied to restore it
		Copy(item2 + size, item1, size);
	}

	//Swap Solution (DOES NOT WORK)
	/*for (int i = 1; i < nitems; i++)
	{
		//init j variable for while loop use
		int j = i - 1;

		//init item1 and item2
		void * item1 = array + (j + 1) * size;
		void * item2 = array + j * size;
		
		//CompareFunc: 1st is greater = > 0, 2nd is greater = <0, equal = 0
		while (j > 0 && CompareFunc(item2, item1) < 0)
		{
			Swap(item1, item2, size);
			j--;
			item2 = array + j * size;
		}
	}*/
	return;
}
