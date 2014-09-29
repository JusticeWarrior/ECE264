#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * * argv)
{
	if (argc == 1)
	{
		char output = fgetc(stdin);
		while (!feof(stdin))
		{
			fputc(output, stdout);
			output = fgetc(stdin);
		}
		return EXIT_SUCCESS;
	}

	int i;
	for (i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "--help"))
		{
			fprintf(stdout, "Usage: cat-lite [--help] [FILE]...\n");
			fprintf(stdout, "With no FILE, or when FILE is -, read standard input.\n\n");
			fprintf(stdout, "Examples:\n");
			fprintf(stdout, "  cat-lite README   Print the file README to standard output.\n");
			fprintf(stdout, "  cat-lite f - g    Print f's contents, then standard input,\n");
			fprintf(stdout, "                    then g's contents.\n");
			fprintf(stdout, "  cat-lite          Copy standard input to standard output.\n");
			return EXIT_SUCCESS;
		}
	}

	for (i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "-"))
		{
			char output = fgetc(stdin);
			while (!feof(stdin))
			{
				fputc(output, stdout);
				output = fgetc(stdin);
			}
			continue;
		}

		FILE * fp = fopen(argv[i], "r");
		if (fp == NULL)
		{
			fprintf(stderr, "cat cannot open %s\n", argv[i]);
			return EXIT_FAILURE;
		}
		
		char output = fgetc(fp);
		while (!feof(fp))
		{
			fputc(output, stdout);
			output = fgetc(fp);
		}
		fclose(fp);
	}

	return EXIT_SUCCESS;
}