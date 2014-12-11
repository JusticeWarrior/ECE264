#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer12.h"

uint128 alphaTou128(const char * str)
{
	int strLen = strlen(str);
	uint128 number = 0;
	int charNum;

	int i;
	for (i = 0; i < strLen; i++)
	{
		charNum = str[i] - '0';
		if (charNum < 0 || charNum > 9)
			return 0;
		number += charNum * (strLen - i);
	}	

	return number;
}

char * u128ToString(uint128 value)
{
	return NULL;
}


int primalityTestParallel(uint128 value, int n_threads)
{
	return 0;
}
