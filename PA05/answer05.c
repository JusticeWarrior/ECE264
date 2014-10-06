#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void partitionAllRecur(int value, char* output);
void partitionIncreRecur(int value, int startVal, char* output);
void partitionDecreRecur(int value, int endVal, char* output);
void partitionOddRecur(int value, char* output);
void partitionEvenRecur(int value, char* output);
void partitionAlterEvenRecur(int value, char* output);
void partitionAlterOddRecur(int value, char* output);
void partitionEvenOddStartRecur(int value, char* output);
int nextPrime(int value);
void partitionPrimeRecur(int value, char* output);

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
	partitionEvenOddStartRecur(value, "= ");
	return;
}

void partitionEvenOddStartRecur(int value, char* output)
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
		if (i % 2)
		{
			partitionAlterEvenRecur(value - i, recurOutput); // Recursive call
		}
		else
		{
			partitionAlterOddRecur(value - i, recurOutput); // Recursive call
		}
		
		free(recurOutput);
	}

	return;
}

void partitionAlterEvenRecur(int value, char* output)
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
		partitionAlterOddRecur(value - i, recurOutput); // Recursive call
		free(recurOutput);
	}

	return;
}

void partitionAlterOddRecur(int value, char* output)
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
		partitionAlterEvenRecur(value - i, recurOutput); // Recursive call
		free(recurOutput);
	}

	return;
}

void partitionPrime(int value)
{
	partitionPrimeRecur(value, "= ");
	return;
}

int nextPrime(int value)
{
	do
	{
		value++;
	} while (!((value == 2 || value % 2) && (value == 3 || value % 3) && (value == 5 || value % 5) && (value == 7 || value % 7) && (value == 11 || value % 11) && (value == 13 || value % 13) && (value == 17 || value % 17)));
	return value;
}

void partitionPrimeRecur(int value, char* output)
{
	if (!value) // Base case
	{
		fprintf(stdout, "%.*s\n", (int)strlen(output) - 3, output);
		return;
	}

	int i = 2;
	for (; i <= value; i = nextPrime(i))
	{
		char addition[5];
		sprintf(addition, "%d", i);
		char* recurOutput = malloc(sizeof(char) * strlen(output) + sizeof(char) * 3 + (sizeof(char) * strlen(addition) + 1));
		strcpy(recurOutput, output);
		strcat(recurOutput, addition);
		strcat(recurOutput, " + ");
		partitionPrimeRecur(value - i, recurOutput); // Recursive call
		free(recurOutput);
	}

	return;
}