#include <stdio.h>
#include <stdlib.h>
#include "Varie.h"


void ReadVaraibles()
{
	int a;
	char c;
	char array[10];
	
	printf("insert a char: ");
	scanf("%c", &c);
	printf("the char is: %c\n\n", c);
	
	
	printf("insert an integer: ");
	scanf("%d", &a);
	printf("the integer is: %d\n\n", a);
	
	
	
	printf("insert a string: ");
	gets(array);
	printf("the array is: %s\n\n", array);
}


void SizeOfVariables()
{
	printf("size of char is: %d\n", sizeof(char));
	printf("size of int is: %d\n", sizeof(int));
	printf("size of float is: %d\n", sizeof(float));
	printf("size of double is: %d\n", sizeof(double));
}


void AddDataTovector(int* vector, int* index, int* data)
{
	if (vector[0] == 0)
		vector[0] = *data;
	
	if (vector[1] == 0)
		vector[1] = *data;
	
	if (vector[2] == 0)
		vector[2] = *data;
	
	vector[*index] = *data;
	(*index)++;
	if (*index > 2)
		*index = 0;	
} 

void increment(int*i)
{ 
	(*i)++;		//metti le parentesi o non funziona niente!!!
	if (*i > 2)
		*i = 0;
}	


void TestWithSscanf(void)
{
	char s[] = "0F";
	int n;
	float f;
	
	sscanf(s, "%x", &n);
	printf("n = %d\n", n);	
	
	sscanf(s, "%f", &f);
	printf("f = %f\n", f);	
}


void AnotherTest(void)
{
	int array[] = {0, 0, 0};
	int i = 0;
	int val = 5;
	AddDataTovector(array, &i, &val);
	printArray(array, 3);
	val = 4;
	AddDataTovector(array, &i, &val);
	printArray(array, 3);
	val = 3;
	AddDataTovector(array, &i, &val);
	printArray(array, 3);
	val = 2;
	AddDataTovector(array, &i, &val);
	printArray(array, 3);
	val = 1;
	AddDataTovector(array, &i, &val);
	printArray(array, 3);
	val = 0;
	AddDataTovector(array, &i, &val);
	printArray(array, 3);
	
}


	
