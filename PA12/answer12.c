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
	uint128 charNum;

	int j;
	int i;
	for (i = 0; i < strLen; i++)
	{
		charNum = str[i] - '0';
		if (charNum < 0 || charNum > 9)
		{
			for (j = 0; j < strLen - i; j++)
			{
				number /= 10;
			}
			return number;
		}

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
		str[i] = (value % 10) + '0';
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
	uint128 threadSize = (uint128)floor(sqrt(value) / n_threads) + 1;
	int isPrime = TRUE;

	if (value == 2)
		return TRUE;
	if (!(value % 2))
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
		if (startVal < 4)
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
