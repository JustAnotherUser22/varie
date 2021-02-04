#include <stdio.h>
#include <stdlib.h>

#ifndef DATA_H
#define DATA_H

struct Data
{
	int day;
	int month;
	int year;	
};


enum MONTH {GEN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};


//check if month is correct
int CheckMonth(struct Data data);

//check if day is correct
int CheckDay(struct Data data);
int IsBisestile(struct Data data);
int isDataCorrect(struct Data data);

//same functions as above but implemented with pointers
int CheckMonthWithPointers(struct Data *data);
int CheckDayWithPointers(struct Data *data);
int IsBisestileWithPointers(struct Data *data);
int isDataCorrectWithPointers(struct Data *data);
int DayInMonthWithPointers(struct Data *data);

int CompareData(struct Data *data1, struct Data *data2);

//compute "data + 1 day"
int UpdateData(struct Data *data);
void printData(struct Data *d);



#endif
