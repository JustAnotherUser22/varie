#include <stdio.h>
#include <stdlib.h>

int externVariable;

void printArray(int* a, int length)
{
	/*int i;
	for(i = 0; i < length; i++)
		printf("%d", a[i]);
	printf("\n");*/
	
	//using pointers
	int i;
	for(i = 0; i < length; i++)
	{
		printf("%d", *a);
		*a++;		//select the next value
	}	
		
	printf("\n");
	
}

void AddValueToArray(int* array, int* index, int* val)
{
	array[*index] = *val;	
}

void TestArray()
{
	int v[] = {9,8,7,6};
	printArray(v, 4);
	
	int val = 3;
	int index = 1;
	
	AddValueToArray(v, &index, &val);
	printArray(v, 4);
}
