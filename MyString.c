#include <stdio.h>
#include <stdlib.h>
#include "MyString.h"
#include <string.h>

void testGets()
{
	char array[10];
	gets(array);
	puts(array);
}


void ReadStringFromInput()
{
	char c;
	while ( (c = getchar() ) != '\n')
		printf("%c\n", c);
}

void MyGets(char *array)
{
	char c;
	while ( (c = getchar() ) != '\n')
		*array++ = c;
	array = '\0';
}

void MyGetsSafe(char *array, int length)
{
	char c;
	int i;
	while ( (c = getchar() ) != '\n' && i < length-1 )	//length-1 because I need space for the '\0' character
		array[i++] = c;
	array[i] = '\0';
}


void MyPuts(char *array)
{
	while (*array != '\0')
		printf("%c", *array++);
}



void SwapChar(char *a, char *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void ReverseCharArray (char* v, int length)
{
	int i;
	for (i = 0; i < length / 2; i++)
	/*{
		int tmp = v[i];
		v[i] = v[length-i-1];
		v[length-i-1] = tmp;
	}*/	
	SwapChar(&v[i], &v[length-i-1]);		
}

void testParseString()
{
	char* received = "{\"ERR\":0, \"STRERR\":\"OK\", \"DATI\":[{\"act\":\"setConf\", \"ERR\":0, \"STRERR\":\"OK\",\"DATI\":{\"cmdid\":2874,\"#testdata\":\"\"testdata\":\"123125789\"\"}}]}]";	
	
	char * pPar;
    char * pEnd;
    
    char PeriodoString[5] = {0,0,0,0,0}; // ex F1234
    int periodo = 0;
    int minutiStart = 0;
    int minutiStop = 0;
    
    if ((pPar = strstr(received, HTTP_CONF_TEST_DATA_JSON_RESP)) != NULL)
    {
    	// sposto il puntato sul primo carattere
        pPar += strlen(HTTP_CONF_TEST_DATA_JSON_RESP);
        
        // cerco le virgolette succeccive
        pEnd = strstr(pPar, "\"");
        
        // check sulla lunghezza
        if (pEnd != NULL)
        {
            // verifico che la lunghezza della sringa letta sia esattramente 224 caratteri
            char local[100];
            memcpy(local, &pPar[0], pEnd - pPar);
            local[pEnd-pPar] = '\0';
            printf("ho ricevuto i dati:%s\r\n", local);
            
            PeriodoString[0] = local[0];
            PeriodoString[1] = local[1];
            PeriodoString[2] = local[2];
            //PeriodoString[3] = pPar[3];
            
            sscanf(PeriodoString, "%X", &periodo);
            printf("start: %d\r\n", periodo);
            
            // calcolo dei minuti con (12 bit con segno)
            minutiStart = (int)(periodo & MINUTE_MASK);
            minutiStart = ((minutiStart << 4) >> 4); // in questo modo ho il segno corretto
            
            PeriodoString[0] = local[3];
            PeriodoString[1] = local[4];
            PeriodoString[2] = local[5];
            //PeriodoString[3] = pPar[3];
            
            sscanf(PeriodoString, "%X", &periodo);
            printf("stop: %d\r\n", periodo);
            
            // calcolo dei minuti con (12 bit con segno)
            minutiStop = (int)(periodo & MINUTE_MASK);
            minutiStop = ((minutiStop << 4) >> 4); // in questo modo ho il segno corretto
            
            PeriodoString[0] = local[6];
            PeriodoString[1] = local[7];
            PeriodoString[2] = local[8];
            
            sscanf(PeriodoString, "%X", &periodo);
            printf("potenza: %d\r\n", periodo);                
        }
	}
}


void testScanfWithHex()
{
	char string[] = {'@', 'Y', ' ', 0x78, 0x79, 0x80};
	//char string[] = "ciaobello";
	char target[] = {'0','0','0','0','0'};
	
	char target1[] = {'0','0','0','0','0'};
	char target2[] = {'0','0','0','0','0'};
	
	printf("target\r\n");
	printf("%x\r\n", target1[0]);
	printf("%x\r\n", target1[1]);
	printf("%x\r\n", target1[2]);
	printf("%x\r\n", target1[3]);
	printf("%x\r\n", target1[4]);
	
	printf("%x\r\n", target2[0]);
	printf("%x\r\n", target2[1]);
	printf("%x\r\n", target2[2]);
	printf("%x\r\n", target2[3]);
	printf("%x\r\n", target2[4]);
	
	printf("string\r\n");
	printf("%x\r\n", string[0]);
	printf("%x\r\n", string[1]);
	printf("%x\r\n", string[2]);
	printf("%x\r\n", string[3]);
	printf("%x\r\n", string[4]);
	printf("%x\r\n", string[5]);
	
	/*printf("%c\r\n", string[0]);
	printf("%c\r\n", string[1]);
	printf("%c\r\n", string[2]);
	printf("%c\r\n", string[3]);
	printf("%c\r\n", string[4]);*/
	
	printf("testScanfWithHex\r\n");
	
	//sscanf(string, "%x%x %x%x%x", &target[0],&target[1],&target[2],&target[3],&target[4]);
    //sscanf(string, "%x%x %x%x%x", target[0],target[1],target[2],target[3],target[4]);	
    //sscanf(string, "%s", &target);
    sscanf(string, "%s %s", &target1, &target2);    
    
    
	printf("%x\r\n", target1[0]);
	printf("%x\r\n", target1[1]);
	printf("%x\r\n", target1[2]);
	printf("%x\r\n", target1[3]);
	printf("%x\r\n", target1[4]);
	printf("--------\r\n");
	printf("%x\r\n", target2[0]);
	printf("%x\r\n", target2[1]);
	printf("%x\r\n", target2[2]);
	printf("%x\r\n", target2[3]);
	printf("%x\r\n", target2[4]);
}

int Hex2Bin(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	
	if (c >= 'A' && c <= 'F')
		return c - '0' + 10;
		
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
}

void TestMyParse()
{
	char local[] = "f23125789";
	char PeriodoString[5] = {0,0,0,0,0}; // ex F1234
    int periodo = 0;
    int minutiStart = 0;
    int minutiStop = 0;
	
	printf("la stringa è %s\n", local);
	
	
        
    PeriodoString[0] = local[0];
    PeriodoString[1] = local[1];
    PeriodoString[2] = local[2];
    
    //PeriodoString[0] &= 0x7F;
    
    sscanf(PeriodoString, "%X", &periodo);
    
    int stato = periodo & 0x800 >> 11;
    printf("stato = %d\n", stato);
    
	if (periodo > 0x800)
    	periodo -= 0x800;    
    
    // calcolo dei minuti con (12 bit con segno)
    //minutiStart = (int16s)(periodo & MINUTE_MASK);
    //minutiStart = ((minutiStart << 4) >> 4); // in questo modo ho il segno corretto
    minutiStart = periodo;
    printf("start: %d\r\n", minutiStart);
    
    //calcolo stato
    //int8u stato = (int8u)((periodo & 0x800) >> 11);
    //ProfilePowerAlarm.isMajor = stato;
    //int stato = Hex2Bin(local[0]) >> 3;
    //printf("stato = %d\n", stato);
    
    
    
    PeriodoString[0] = local[3];
    PeriodoString[1] = local[4];
    PeriodoString[2] = local[5];
    
    sscanf(PeriodoString, "%X", &periodo);
    printf("stop: %d\r\n", periodo);
    
    // calcolo dei minuti con (12 bit con segno)
    //minutiStop = (int16s)(periodo & MINUTE_MASK);
    //minutiStop = ((minutiStop << 4) >> 4); // in questo modo ho il segno corretto
    minutiStart = periodo;
    
    PeriodoString[0] = local[6];
    PeriodoString[1] = local[7];
    PeriodoString[2] = local[8];
    
    float f;
    sscanf(PeriodoString, "%d", &periodo);
    f = periodo / 100.0;
    printf("potenza: %d [DaW]       (= %f KW)\r\n", periodo, f);
}


