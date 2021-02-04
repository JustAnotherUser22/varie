#ifndef HEADER2
#define HEADER2



#include "TestGuard.h"

//int varGuard;
int varGuard = 5;

//se dichiaro anche questo sotto, definisco la stessa cosa in due file diversi e non va bene...
/*struct foo {
    int member;
};*/



void printVarGuard()
{
	//varGuard = 2;
	printf("varGuard = %d\r\n", varGuard);	
}


#endif
