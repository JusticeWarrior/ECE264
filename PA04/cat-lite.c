#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * * argv)
{
	int ind;

	for (ind = 1; ind < argc; ++ind) {
		printf("%s ", ind, argv[ind]);
	}

	return EXIT_SUCCESS;
}