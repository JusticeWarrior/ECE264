#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer12.h"

uint128 alphaTou128(const char * str)
{
	int strLen = strlen(str);
	uint128 number = 0;
	uint128 charNum;

	int j;
	int i;
	for (i = 0; i < strLen; i++)
	{
		charNum = str[i] - '0';
		if (charNum < 0 || charNum > 9)
			return 0;

		for (j = 0; j < strLen - i - 1; j++)
		{
			charNum *= 10;
		}
		number += charNum;
	}	

	return number;
}

static int u128Length(uint128 value)
{
	int len = 0;

	while(value > 0)
	{
		value /= 10;
		len++;
	}

	return len;
}

char * u128ToString(uint128 value)
{
	int len = u128Length(value);

	char * str = malloc(sizeof(char) * len + 1);
	str[len] = '\n';
	
	int i;
	for (i = len - 1; i >= 0; i--)
	{
		str[i] = (value % 10) + '0';
		value /= 10;
	}

	return str;
}


int primalityTestParallel(uint128 value, int n_threads)
{
	return 0;
}
