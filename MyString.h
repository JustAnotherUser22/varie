#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MYSTRING_H
#define MYSTRING_H

#define HTTP_CONF_TEST_DATA_JSON_RESP	"\"testdata\":\""
#define MINUTE_MASK 0x0FFF

void testGets();
void ReadStringFromInput();
void MyGets(char *array);
void MyGetsSafe(char *array, int length);
void MyPuts(char *array);
void testScanfWithHex();

void ReverseCharArray (char* v, int length);
void SwapChar(char *a, char *b);

void testParseString();
#endif
