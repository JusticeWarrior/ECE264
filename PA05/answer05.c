#include <stdio.h>
#include <stdlib.h>

void partitionAll(int value)
{
	if (!value) // Base case
	{
		fprintf(stdout, "/n");
		return;
	}

	int i;
	for (i = 1; i <= value; i++)
	{
		partitionAll(value - i); // Recursive call
		fprintf(stdout, "%d", i);
	}

	return;
}

void partitionIncreasing(int value)
{
	return;
}

void partitionDecreasing(int value)
{
	return;
}

void partitionOdd(int value)
{
	return;
}

void partitionEven(int value)
{
	return;
}

void partitionOddAndEven(int value)
{
	return;
}

void partitionPrime(int value)
{
	return;
}