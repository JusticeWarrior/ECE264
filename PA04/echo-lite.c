#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	int ind;

	if (argc == 1)
	{
		fprintf(stdout, " ");
	}

	for (ind = 1; ind < argc; ++ind) 
	{
		fprintf(stdout, "%s ", argv[ind]);
	}
	

	return EXIT_SUCCESS;
}