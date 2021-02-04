#include "Data.h"

#define TRUE 0
#define FALSE 1

int CheckMonth(struct Data data)
{
	if (data.month > 1 && data.month < 12)
		return TRUE;
	return FALSE;
}

int DayInMonth(struct Data data)
{
	if (data.month == NOV ||
		data.month == APR ||
		data.month == JUN ||
		data.month == SEP )
		return 30;
	
	if (data.month == FEB)
		if (IsBisestile(data))
			return 28;
		else
			return 29;
	
	return 31;
}



int CheckDay(struct Data data)
{
	if (data.day > 1 && data.day < DayInMonth(data))
		return TRUE;
	return FALSE;
}

int IsBisestile(struct Data data)
{
	if (data.year % 4 == 0 || data.year % 100 == 0)
		return TRUE;
	return FALSE;
}

int isDataCorrect(struct Data data)
{
	if (CheckMonth(data) == TRUE && CheckDay(data) == TRUE )
		return TRUE;
	return FALSE;
}




int CheckMonthWithPointers(struct Data *data)
{
	if (data->month > 1 && data->month < 12)
		return TRUE;
	return FALSE;
}

int DayInMonthWithPointers(struct Data *data)
{
	if (data->month == NOV ||
		data->month == APR ||
		data->month == JUN ||
		data->month == SEP )
		return 30;
	
	if (data->month == FEB)
		if (IsBisestileWithPointers(data))
			return 28;
		else
			return 29;
	
	return 31;
}


int CheckDayWithPointers(struct Data *data)
{
	if (data->day > 1 && data->day <= DayInMonthWithPointers(data))
		return TRUE;
	return FALSE;
}

int IsBisestileWithPointers(struct Data *data)
{
	if (data->year % 4 == 0 || data->year % 100 == 0)
		return TRUE;
	return FALSE;
}

int isDataCorrectWithPointers(struct Data *data)
{
	if (CheckMonthWithPointers(data) == TRUE && CheckDayWithPointers(data) == TRUE )
		return TRUE;
	return FALSE;
}

int CompareData(struct Data *data1, struct Data *data2)
{
	if (data1->year < data2->year)
		return -1;
	if (data1->year > data2->year)
		return 1;
		
	if (data1->month < data2->month)
		return -1;
	if (data1->month > data2->month)
		return 1;
		
	if (data1->day < data2->day)
		return -1;
	if (data1->day > data2->day)
		return 1;
		
	return 0;
}



int UpdateData(struct Data *data)
{
	data->day++;
	if (data->day > CheckDayWithPointers(data))
	{
		data->day = 1;
		data->month++;
		if (CheckMonthWithPointers(data) == FALSE)
		{
			data->month = 1;
			data->year++;
		}	
	}
}


void printData(struct Data *d)
{
	printf("day = %d\t", d->day);
	printf("month = %d\t", d->month);
	printf("year = %d\n", d->year);
}




















