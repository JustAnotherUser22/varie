#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TestIR.h"
#include "MyUnion.h"
//#include <stdint.h>


int main(int argc, char *argv[])
{
	//IRTX_Send(IR_CMD_ON, DEF_MODEL_GREE);
	
	ConvertFromAnalysIRUsingFile();
	
	//testUnion();
	//FromAnalysIR2Frame();
		
	//int n = 0x03;
	//ConvertByte(n);
	//ComputeChecksumTest();
	
	//ConvertFromAnalysIR();
		
	return 0;
}
