#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void partitionAllRecur(int value, char* output);
void partitionIncreRecur(int value, int startVal, char* output);
void partitionDecreRecur(int value, int endVal, char* output);
void partitionOddRecur(int value, char* output);
void partitionEvenRecur(int value, char* output);

void partitionAll(int value)
{
	partitionAllRecur(value, "= ");
	return;
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

	return;
}

void partitionIncreasing(int value)
{
	partitionIncreRecur(value, 1, "= ");
	return;
}

void partitionIncreRecur(int value, int startVal, char* output)
{
	if (!value) // Base case
	{
		fprintf(stdout, "%.*s\n", (int)strlen(output) - 3, output);
		return;
	}

	int i = startVal;
	for (; i <= value; i++)
	{
		char addition[5];
		sprintf(addition, "%d", i);
		char* recurOutput = malloc(sizeof(char) * strlen(output) + sizeof(char) * 3 + (sizeof(char) * strlen(addition) + 1));
		strcpy(recurOutput, output);
		strcat(recurOutput, addition);
		strcat(recurOutput, " + ");
		partitionIncreRecur(value - i, i + 1, recurOutput); // Recursive call
		free(recurOutput);
	}

	return;
}

void partitionDecreasing(int value)
{
	partitionDecreRecur(value, value, "= ");
	return;
}

void partitionDecreRecur(int value, int endVal, char* output)
{
	if (!value) // Base case
	{
		fprintf(stdout, "%.*s\n", (int)strlen(output) - 3, output);
		return;
	}

	int i = 1;
	for (; i <= endVal; i++)
	{
		char addition[5];
		sprintf(addition, "%d", i);
		char* recurOutput = malloc(sizeof(char) * strlen(output) + sizeof(char) * 3 + (sizeof(char) * strlen(addition) + 1));
		strcpy(recurOutput, output);
		strcat(recurOutput, addition);
		strcat(recurOutput, " + ");
		partitionDecreRecur(value - i, i - 1, recurOutput); // Recursive call
		free(recurOutput);
	}

	return;
}

void partitionOdd(int value)
{
	partitionOddRecur(value, "= ");
	return;
}

void partitionOddRecur(int value, char* output)
{
	if (!value) // Base case
	{
		fprintf(stdout, "%.*s\n", (int)strlen(output) - 3, output);
		return;
	}

	int i = 1;
	for (; i <= value; i += 2)
	{
		char addition[5];
		sprintf(addition, "%d", i);
		char* recurOutput = malloc(sizeof(char) * strlen(output) + sizeof(char) * 3 + (sizeof(char) * strlen(addition) + 1));
		strcpy(recurOutput, output);
		strcat(recurOutput, addition);
		strcat(recurOutput, " + ");
		partitionOddRecur(value - i, recurOutput); // Recursive call
		free(recurOutput);
	}

	return;
}

void partitionEven(int value)
{
	partitionEvenRecur(value, "= ");
	return;
}

void partitionEvenRecur(int value, char* output)
{
	if (!value) // Base case
	{
		fprintf(stdout, "%.*s\n", (int)strlen(output) - 3, output);
		return;
	}

	int i = 2;
	for (; i <= value; i += 2)
	{
		char addition[5];
		sprintf(addition, "%d", i);
		char* recurOutput = malloc(sizeof(char) * strlen(output) + sizeof(char) * 3 + (sizeof(char) * strlen(addition) + 1));
		strcpy(recurOutput, output);
		strcat(recurOutput, addition);
		strcat(recurOutput, " + ");
		partitionEvenRecur(value - i, recurOutput); // Recursive call
		free(recurOutput);
	}

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