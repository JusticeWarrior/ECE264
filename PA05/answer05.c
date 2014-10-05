#include <stdio.h>
#include <stdlib.h>

void partitionAll(int value)
{
	
}

void partitionAllRecur(int value, char* output)
{
	if (!value) // Base case
	{
		fprintf(stdout, "\n");
		return;
	}

	fprintf(stdout, " + ");

	int i = 1;
	for (; i <= value; i++)
	{
		fprintf(stdout, "%d", i);
		partitionAll(value - i); // Recursive call
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