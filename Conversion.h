
#ifndef CONVERSION_H
#define CONVERSION_H

//convert integer n to a binary number and write it in an array with provided size
void dec2bin (int n, int* array,  int size);

//convert integer n to a hex number and write it in an array with provided size
void dec2hex (int n, char* array,  int size);

//convert hex number to an integer and write it in an array with provided size
int hex2dec (char* array, int size);

//convert binary number to an integer and write it in an array with provided size
int bin2dec (int* array, int size);

//reverse the ordere of the provided arary
void ReverseArray (int* v, int length);

//swap two elements
void Swap(int *a, int *b);

//compute the binary sum of a and b and write the result in c (a,b and c are array with provided length)
void BinarySum(int* a, int *b, int *c, int length);

//test program
void testConversion();







void initializeArray(int *a, int length);

//compute power
int power(int base, int esponente);

#endif
