#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include "answer12.h"

uint128 alphaTou128(const char * str)
{
	int strLen = strlen(str);
	uint128 number = 0;
	uint128 charNum = 0;

	int j;
	int i = 0;
	int k = 0;
	if (i < strLen && str[i] == ' ')
	{
		i = 1;
	}
	if (strLen > 39)
		strLen = 39;
	for (; k < strLen; k++)
	{
		charNum = (uint128)(str[i] - '0');
		if (charNum < 0 || charNum > 9)
		{
			for (j = 0; j < strLen - k; j++)
			{
				number /= 10;
			}
			return number;
		}

		if (charNum == 0)
		{
			i++;
			continue;
		}
		else
		{
			for (j = 0; j < strLen - k - 1; j++)
			{
				charNum *= 10;
			}
			number += charNum;
		}
		i++;
	}	

	return number;
}

static int u128Length(uint128 value)
{
	if (value == 0)
		return 1;

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

	char * str = malloc((sizeof(char) * len) + 1);
	str[len] = '\0';
	
	int i;
	for (i = len - 1; i >= 0; --i)
	{
		str[i] = (char)((int)(value % 10) + '0');
		value /= 10;
	}

	return str;
}

typedef struct m_PrimalityArgs
{
	uint128 * value;
	uint128 startValue;
	uint128 endValue;
	int * isPrime;
} PrimalityArgs;

static void PrimalityArgsFill(PrimalityArgs * args, uint128 * value, uint128 startValue, uint128 endValue, int * isPrime)
{
	args->value = value;
	args->startValue = startValue;
	args->endValue = endValue;
	args->isPrime = isPrime;
}

static void * testPrimalityThread(void * primalityArg)
{
	PrimalityArgs * arguments = (PrimalityArgs *)primalityArg;

	uint128 i;
	for (i = arguments->startValue; i <= arguments->endValue; i += 2)
	{
		if (!(*(arguments->value) % i))
		{
			*(arguments->isPrime) = FALSE;
			return NULL;
		}
	}
	return NULL;
}

int primalityTestParallel(uint128 value, int n_threads)
{
	uint128 max = (uint128)floor(sqrt(value));
	if (max * max == value)
		return FALSE; 
	uint128 threadSize = (max / n_threads) + 1;
	int isPrime = TRUE;

	if (value == 2 || value == 3)
		return TRUE;
	if (!(value % 2))
		return FALSE;
	if (!(value % 3))
		return FALSE;

	pthread_t threads[n_threads];	
	PrimalityArgs args[n_threads];

	PrimalityArgsFill(&args[0], &value, 3, threadSize, &isPrime);
	pthread_create(&threads[0], NULL, testPrimalityThread, &args[0]);
	
	int i;
	for (i = 1; i < n_threads; i++)
	{
		uint128 startVal = threadSize * i;
		if (startVal % 2 == 0)
			startVal--;
		if (startVal < 4 || startVal >= max)
		{
			args[i].startValue = -1;
			continue;
		}
		PrimalityArgsFill(&args[i], &value, startVal, startVal + threadSize, &isPrime);
		pthread_create(&threads[i], NULL, testPrimalityThread, &args[i]);
	}

	for (i = 0; i < n_threads; i++)
	{
		if (args[i].startValue == -1)
			continue;
		pthread_join(threads[i], NULL);
	}

	return isPrime;
}
