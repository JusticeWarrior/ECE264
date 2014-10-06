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
		fprintf(stdout, "%.*s\n", (int)strlen(output) - 3, output);
		return;
	}

	int i = 1;
	for (; i <= value; i++)
	{
		char addition[5];
		sprintf(addition, "%d", i);
		char* recurOutput = malloc(sizeof(char) * strlen(output) + sizeof(char) * 3 + (sizeof(char) * strlen(addition) + 1));
		strcpy(recurOutput, output);
		strcat(recurOutput, addition);
		strcat(recurOutput, " + ");
		partitionAllRecur(value - i, recurOutput); // Recursive call
		free(recurOutput);
	}

	//return;
}

void partitionIncreasing(int value)
{
	//return;
}

void partitionDecreasing(int value)
{
	//return;
}

void partitionOdd(int value)
{
	//return;
}

void partitionEven(int value)
{
	//return;
}

void partitionOddAndEven(int value)
{
	//return;
}

void partitionPrime(int value)
{
	//return;
}