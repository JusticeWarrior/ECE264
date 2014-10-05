#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer05.h"

int main(int argc, char * * argv)
{
	if (argc != 3)
	{
		return EXIT_SUCCESS;
	}

	if (!strcmp(argv[1], "partitionAll"))
	{
		partitionAll(atoi(argv[2]));
	}

	if (!strcmp(argv[1], "partitionIncreasing"))
	{
		partitionIncreasing(atoi(argv[2]));
	}

	if (!strcmp(argv[1], "partitionDecreasing"))
	{
		partitionDecreasing(atoi(argv[2]));
	}

	if (!strcmp(argv[1], "partitionOdd"))
	{
		partitionOdd(atoi(argv[2]));
	}

	if (!strcmp(argv[1], "partitionEven"))
	{
		partitionEven(atoi(argv[2]));
	}

	if (!strcmp(argv[1], "partitionOddAndEven"))
	{
		partitionOddAndEven(atoi(argv[2]));
	}

	if (!strcmp(argv[1], "partitionPrime"))
	{
		partitionPrime(atoi(argv[2]));
	}

	return EXIT_SUCCESS;
}