#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	int ind;

	for (ind = 1; ind < argc; ++ind) 
	{
		if (ind == argc - 1 && argv[argc - 1][0] == '\n')
		{
			fprintf(stdout, "\n");
			return EXIT_SUCCESS;
		}
		else
		{
			fprintf(stdout, "%s ", argv[ind]);
		}
	}
	

	return EXIT_SUCCESS;
}