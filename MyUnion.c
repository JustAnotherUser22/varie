#include <stdio.h>
#include <stdlib.h>
#include "MyUnion.h"
#include "TestIR.h"


/*
struct data{
	unsigned int b1:1;	//bit meno significativo
	unsigned int b2:1;
	unsigned int b3:1;
	unsigned int b4:1;
	unsigned int b5:1;
	unsigned int b6:1;
	unsigned int b7:1;
	unsigned int b8:1;	//bit più significativo
};


union test{
	struct data d;
	int v;
};

void testUnion()
{
	union test t;
	t.v = 16;
	
	printf("v = %x\n", t.v);
	
	printf("b1 = %d\n", t.d.b1);
	printf("b2 = %d\n", t.d.b2);
	printf("b3 = %d\n", t.d.b3);
	printf("b4 = %d\n", t.d.b4);
	printf("b5 = %d\n", t.d.b5);
	printf("b6 = %d\n", t.d.b6);
	printf("b7 = %d\n", t.d.b7);
	printf("b8 = %d\n", t.d.b8);	
}
*/

struct Frame5{
	uint8_t mode:3;
	uint8_t power:1;
	uint8_t fan:2;
	uint8_t swing:1;
	uint8_t sleepBitZero:1;
	
	/*uint8_t temperatura:4;
	uint8_t wifi:1;
	uint8_t timer:3;
	
	uint8_t TBD:4;
	uint8_t turbo:1;
	uint8_t light:1;
	uint8_t modalitaSanificazione:1;
	uint8_t modalitaDepurazione:1;
	
	uint8_t paletteVerticali:4;
	uint8_t paletteOrizzontali:4;
	
	uint8_t temp:2;
	uint8_t ifeel:1;
	uint8_t TBD2:5;*/
};

struct Frame6{
	uint8_t mode:3;
	uint8_t power:1;
	uint8_t fan:2;
	uint8_t swing:1;
	uint8_t sleepBitZero:1;
	
	uint8_t temperatura:4;
	uint8_t wifi:1;
	uint8_t timer:3;
	
	uint8_t TBD:4;
	uint8_t turbo:1;
	uint8_t light:1;
	uint8_t modalitaSanificazione:1;
	uint8_t modalitaDepurazione:1;
	
	uint8_t paletteVerticali:4;
	uint8_t paletteOrizzontali:4;
	
	uint8_t temp:2;
	uint8_t ifeel:1;
	
	//per pacchetto ID6
	uint8_t sleepBitUno:1;
	uint8_t quiet:2;
	uint8_t sleep_ora_uno:4;
	uint8_t sleep_ora_due:5;
	uint8_t fan_ID7:4;	
};

union Frame{
	struct Frame5 f5;
	//struct Frame6 f6;
	unsigned char data[1];
};

struct Time{
	int minutes:11;
};

union BigTime{
	struct Time t;
	int m;
};

void testUnion()
{
	/*
	union Frame frame;
	
	frame.f5.mode = MODE_VENTILAZIONE;
	frame.f5.power = POWER_OFF;
	frame.f5.fan = FAN_AUTO;
	frame.f5.swing = SWING_OFF;
	frame.f5.sleepBitZero = 0;		
	
	//int i;
	//for(i = 0; i < 8; i++)
	//	printf("data[%d] = %x\n", i, frame.data[i]);		
	
	char v = frame.f5.mode << 1;
	printf("%x", v);
	*/
	
	union BigTime bt;
	bt.m = 1234;
	printf("int = %x\n", bt.m >> 8);
	printf("struct = %x\n", bt.t.minutes);
}

