#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void partitionAllRecur(int value, char* output);

void partitionAll(int value)
{
	partitionAllRecur(value, "= ");
}

void partitionAllRecur(int value, char* output)
{
	if (!value) // Base case
	{
		fprintf(stdout, "%s\n", output);
		return;
	}

	int i = 1;
	for (; i <= value; i++)
	{
		char* addition = atoi(i);
		char* recurOutput = malloc(sizeof(char) * strlen(output) + sizeof(char) * 3 + sizeof(char) * strlen(addition));
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