#include "Conversion.h"
#include "Mystring.h"

char toHex[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};


void ReverseArray (int* v, int length)
{
	int i;
	for (i = 0; i < length / 2; i++)
		Swap(&v[i], &v[length-i-1]);		
}

void dec2bin (int n, int* array, int size)
{
	while( n != 0)
	{
		*array++ = n % 2;
		n /= 2;
	}
	ReverseArray (array, size);
}

int bin2dec (int* array, int size)
{
	int local = 0;
	int i;
	
	for (i = 0; i < size; i++)
		local += array[i] * power(2, size-i-1);
	
	return local;
}

void dec2hex (int n, char* array,  int size)
{
	while (n != 0)
	{
		*array++ = toHex[n % 16];
		n /= 16;
	}
	ReverseCharArray (array, size);
}

int hex2dec (char* array, int size)
{
	int local = 0;
	int i;
	
	for (i = 0; i < size; i++)
		local += array[i] * power(16, size-i-1);
	
	return local;
}


void Swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void BinarySum(int* a, int *b, int *c, int length)
{
	int i = 0;
	for (i = length-1; i > 0; i--)
	{
		c[i] += a[i] + b[i];
		if (c[i] > 1)
		{
			c[i] = 0;
			c[i-1] = 1;
		}
	}
}


int binaryArray[10];
int binaryArrayCounter = 0;

void WriteInArray(int a, int b, int c, int d)
{
	binaryArray[binaryArrayCounter++] = a;
	binaryArray[binaryArrayCounter++] = b;
	binaryArray[binaryArrayCounter++] = c;
	binaryArray[binaryArrayCounter++] = d;	
}

void InitBinaryArray()
{
	int i;
	for(i =0; i < 10; i++)
		binaryArray[i] = -1;
}

int hex2decToArray (char* array, int size)
{
	int i;
	
	
	for(i = 0; i < size; i++)
	{
		switch(array[i])
		{
			case '0':
				WriteInArray(0, 0, 0, 0);
				break;
				
			case '1':
				WriteInArray(0, 0, 0, 1);
				break;
				
			case '2':
				WriteInArray(0, 0, 1, 0);
				break;
				
			case '3':
				WriteInArray(0, 0, 1, 1);
				break;
				
			case '4':
				WriteInArray(0, 1, 0, 0);
				break;
				
			case '5':
				WriteInArray(0, 1, 0, 1);
				break;
				
			case '6':
				WriteInArray(0, 1, 1, 0);
				break;
				
			case '7':
				WriteInArray(0, 1, 1, 1);
				break;
				
			case '8':
				WriteInArray(1, 0, 0, 0);
				break;
				
			case '9':
				WriteInArray(1, 0, 0, 1);
				break;
				
			case 'A':
			case 'a':
				WriteInArray(1, 0, 1, 0);
				break;
				
			case 'B':
			case 'b':
				WriteInArray(1, 0, 1, 1);
				break;
				
			case 'C':
			case 'c':
				WriteInArray(1, 1, 0, 0);
				break;
				
			case 'D':
			case 'd':
				WriteInArray(1, 1, 0, 1);
				break;
				
			case 'E':
			case 'e':
				WriteInArray(1, 1, 1, 0);
				break;
				
			case 'F':
			case 'f':
				WriteInArray(1, 1, 1, 1);
				break;
		}
		
		/*if(array[i] == '0')
			WriteInArray(0, 0, 0, 0);
			
		if(array[i] == '1')
			WriteInArray(0, 0, 0, 1);
			
		if(array[i] == '2')
			WriteInArray(0, 0, 1, 0);
	
		if(array[i] == '3')
			WriteInArray(0, 0, 1, 1);
			
		if(array[i] == '4')
			WriteInArray(0, 1, 0, 0);
			
		if(array[i] == '5')
			WriteInArray(0, 1, 0, 1);
			
		if(array[i] == '6')
			WriteInArray(0, 1, 1, 0);
			
		if(array[i] == '7')
			WriteInArray(0, 1, 1, 1);
			
		if(array[i] == '8')
			WriteInArray(1, 0, 0, 0);
			
		if(array[i] == '9')
			WriteInArray(1, 0, 0, 1);
			
		if(array[i] == 'A' || array[i] == 'a')
			WriteInArray(1, 0, 1, 0);

		if(array[i] == 'B' || array[i] == 'b')
			WriteInArray(1, 0, 1, 1);
		
		if(array[i] == 'C' || array[i] == 'c')
			WriteInArray(1, 1, 0, 0);
	
		if(array[i] == 'D' || array[i] == 'd')
			WriteInArray(1, 1, 0, 1);
	
		if(array[i] == 'E' || array[i] == 'e')
			WriteInArray(1, 1, 1, 0);
		
		if(array[i] == 'F' || array[i] == 'f')
			WriteInArray(1, 1, 1, 1);*/
	}
}


void testConversion()
{
	/*int array1[10];
	int array2[10];
	int array3[10];
	
	initializeArray(array1, 10);
	initializeArray(array2, 10);
	initializeArray(array3, 10);	
	
	dec2bin(4, array1);
	dec2bin(4, array2);
	ReverseArray(array1, 10);
	ReverseArray(array2, 10);
	
	BinarySum(array1, array2, array3, 10);
	
	printArray(array1, 10);
	printArray(array2, 10);
	printArray(array3, 10);*/
	
	/*char array[10];
	int i;
	for(i = 0; i < 10; i++)
		array[i] = 0;
	
	dec2hex(123456, array, 10);
	
	for(i = 0; i < 10; i++)
		printf("%c", array[i]);*/
		
	/*char a[] = "123456";
	ReverseCharArray(a,6);
	int i;
	for(i = 0; i < 6; i++)
		printf("%c",a[i]);*/
		
	/*int v[] = {1, 1, 0, 0, 0};
	int a = bin2dec (v, 5);
	printf("%d", a);*/
	
	//char a[] = {'A', 'B'};
	char a[] = "AB";
	InitBinaryArray();
	int dimension = sizeof(a)/sizeof(char);
	hex2decToArray(a, dimension);
	
	int i;
	
	for(i = 0; i < sizeof(binaryArray)/sizeof(int); i++)
		printf("%d ", binaryArray[i]);
	
}



void initializeArray(int *a, int length)
{
	int i = 0;
	for(i = 0; i < length; i++)
		*a++ = 0;
}

int power(int base, int esponente)
{
	int i;
	int local = 1;
	for (i = 0; i < esponente; i++)
		local *= base;
	return local;
}
