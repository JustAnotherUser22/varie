

#include "FunctionPointer.h"




//funzione che vuole come argomento un intero er restituisce un intero
int FirstFunctionToCall(int n)
{
	if (n == 0)
		printf("done\n");
	else
		printf("error\n");		
}


//funzione che vuole come argomento un puntatore a una funzione(che ritorna un int e non accetta argomenti) e ritorna un int
int SecondFunctionToCall(int (*f)(void))
{
	if (f() == 0)
		printf("done\n");
	else
		printf("error\n");
}



int ThirdFunctionToCall(new_var f)
{
	if (f() == 0)
		printf("done\n");
	else
		printf("error\n");
}


int b()
{
	return 0;
}


int localMain()
{
	FirstFunctionToCall(b());
	
	SecondFunctionToCall(b);
	
	ThirdFunctionToCall(b);
}





