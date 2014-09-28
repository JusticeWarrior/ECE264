#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * * argv)
{
	int i;
	for (i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "--help"))
		{
			fprintf(stdout, "<help-message>\n");
			fprintf(stdout, "Usage: grep-lite [OPTION]... PATTERN\n");
			fprintf(stdout, "Search for PATTERN in standard input. PATTERN is a\n");
			fprintf(stdout, "string. grep-lite will search standard input line by\n");
			fprintf(stdout, "line, and (by default) print out those lines which\n");
			fprintf(stdout, "contain pattern as a substring.\n\n");
			fprintf(stdout, "  -v, --invert-match     print non-matching lines\n");
			fprintf(stdout, "  -n, --line-number      print line numbers with output\n");
			fprintf(stdout, "  -q, --quiet            suppress all output\n\n");
			fprintf(stdout, "Exit status is 0 if any line is selected, 1 otherwise;\n");
			fprintf(stdout, "if any error occurs, then the exit status is 2.\n");
			fprintf(stdout, "</help-message>\n");
			return EXIT_SUCCESS;
		}
	}

	return EXIT_SUCCESS;
}