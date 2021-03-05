
#ifndef FUNCTIONPOINTER_H
#define FUNCTIONPOINTER_H

#include <stdio.h>
#include <stdlib.h>



int b();

int FirstFunctionToCall(int n);
int SecondFunctionToCall(int (*f)(void));

typedef int (*new_var)(void);
//int ThirdFunctionToCall(new_var f(void));
int ThirdFunctionToCall(new_var f);



#endif
