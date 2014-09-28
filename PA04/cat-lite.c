#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * * argv)
{
	int i;
	for (i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "--help"))
		{
			fprintf(stdout, "<help-message>\n");
			fprintf(stdout, "Usage: cat-lite [--help] [FILE]...\n");
			fprintf(stdout, "With no FILE, or when FILE is -, read standard input.\n\n");
			fprintf(stdout, "Examples:\n");
			fprintf(stdout, "  cat-lite README   Print the file README to standard output.\n");
			fprintf(stdout, "  cat-lite f - g    Print f's contents, then standard input,\n");
			fprintf(stdout, "                    then g's contents.\n");
			fprintf(stdout, "  cat-lite          Copy standard input to standard output.\n");
			fprintf(stdout, "</help-message>\n");
		}
	}

	return EXIT_SUCCESS;
}