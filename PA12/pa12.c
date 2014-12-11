#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer12.h"

int main(int argc, char ** argv)
{
	uint128 test1 = alphaTou128("324324325574");
	char * output1 = u128ToString(test1);

	uint128 test2 = alphaTou128("100000000000000000000000000233232532532");
	char * output2 = u128ToString(test2);

	fprintf(stdout, "%s", output1);
	fprintf(stdout, "%s", output2);

	free(output1);
	free(output2);

	return EXIT_SUCCESS;
}

