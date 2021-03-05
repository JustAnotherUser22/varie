#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TestIR.h"
#include "MyUnion.h"
#include "FunctionPointer.h"
//#include <stdint.h>


extern settings_List_t TestObj;


int main(int argc, char *argv[])
{
	//IRTX_Send(IR_CMD_ON, DEF_MODEL_GREE);
	IRTX_Send(IR_CMD_ON_OFF, DEF_MODEL_GREE, &TestObj);	
	//localMain();

	//uint8_t n = 0xea;
	//printf("%02x\n", n);
	
	//ConvertFromAnalysIRUsingFile();
	//TestObjToState();
	
	//testUnion();
	//FromAnalysIR2Frame();
		
	//int n = 0x03;
	//ConvertByte(n);
	//ComputeChecksumTest();
	
	//ConvertFromAnalysIR();
		
	return 0;
}
