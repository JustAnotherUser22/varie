#include <stdio.h>
#include "MyFile.h"

void ReadFile()
{
	FILE *fp;
	char buff[200];
	char c;

	fp = fopen("file.txt", "r");
	
	if (fp == NULL)
	{
		printf("file non trovato");
		return;
	}
	
	//read each word and print it 
	//while(fscanf(fp, "%s", buff) != EOF)
	//	printf("%s", buff);
		
	//read each char and print it 
	while( (c = getc(fp)) != EOF)
		putchar(c);
		
	fclose(fp);
}

void WriteFile(float data)
{
	FILE *fp;
	
	fp = fopen("log.txt", "a");
	
	if (fp == NULL)
	{
		printf("impossibile aprire il file");
		return;
	}
	
	fprintf(fp, "%f\n", data);
	printf("ho scritto %f\n", data);
	fclose(fp);
}


void ParseFile()
{
	FILE *fp;
	char buff[200];
	char separatore = ',';
	char line[200];
	char c;
	int i = 0;

	fp = fopen("file.txt", "r");
	
	if (fp == NULL)
	{
		printf("file non trovato");
		return;
	}
	
	c = getc(fp);
	while(c != EOF)		//till I reach the end of the text
	{
		
		i = 0;
		
		while (c != '\n')	//read till i reach the end of the line
		{
			line[i++] = c;
			c = getc(fp);
		}	
		
		line[i] = '\0';
		puts(line);	
		c = getc(fp);	
	}
	
	line[i] = '\0';
	puts(line);
	
	fclose(fp);
}


