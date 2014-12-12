#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer12.h"

int testFile(const char * file, int testValue)
{
	FILE * primes = fopen(file, "rb");	
	if (primes == NULL)
	{
		fprintf(stdout, "Dumbass");
		return EXIT_FAILURE;
	}

	while(!feof(primes))
	{
		char * stringPrime = malloc(sizeof(char) * 40);
		fgets(stringPrime, 40, primes);
		uint128 currentPrime = alphaTou128(stringPrime);
		free(stringPrime);
		char * outputPrime = u128ToString(currentPrime);
		if (primalityTestParallel(currentPrime, 4) == testValue)
		{
			fprintf(stdout, "%s Test case failed\n", outputPrime);
		}
		else
		{
			fprintf(stdout, "%s Test case passed\n", outputPrime);
		}
		free(stringPrime);
		free(outputPrime);
	}
	fclose(primes);

	return EXIT_SUCCESS;
}

int main(int argc, char ** argv)
{
	uint128 test1 = alphaTou128("2\n");
	char * output1 = u128ToString(test1);

	uint128 test2 = alphaTou128("100y00000000000000000000000233232532532");
	char * output2 = u128ToString(test2);

	fprintf(stdout, "%s", output1);
	fprintf(stdout, "%s", output2);

	free(output1);
	free(output2);

	int result = EXIT_SUCCESS;

	fprintf(stdout, "\n\n");
	fprintf(stdout, "PRIME TEST START\n");

	result = testFile("inputs/390-nice-primes.text", FALSE);	
	
	fprintf(stdout, "\n\n");
	fprintf(stdout, "NON-PRIME TEST START\n");

	result = testFile("inputs/2116-nice-non-primes.text", TRUE);	

	return result;
}

