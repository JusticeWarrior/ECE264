
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer07.h"
#include <libgen.h>

void print_usage(char * argv0)
{
	printf("\n"
		"   Usage: %s <filename-1> <filename-2>\n"
		"\n"
		"      Compares the two files, but not strictly. The two files\n"
		"      must have the same number of bytes; however, each byte can\n"
		"      differ plus or minus 4. This is to compare normalized files\n"
		"      which will have small differences from rounding errors\n"
		"\n"
		"      Exit status is 0 if the files are the \"same\", 1 if they\n"
		"      are different, and 2 if there is some error reading the\n"
		"      files.\n"
		"\n");
	basename(argv0));
}

int compare(char ** argv)
{
	FILE * fp1 = fopen(argv[1], "rb");
	if (fp1 == NULL) {
		fprintf(stderr, "Failed to open filename '%s'\n", argv[1]);
		return 2;
	}
	FILE * fp2 = fopen(argv[2], "rb");
	if (fp2 == NULL) {
		fprintf(stderr, "Failed to open filename '%s'\n", argv[2]);
		return 2;
	}

	int ret = EXIT_SUCCESS;
	int byte_counter = 0;
	int ch1, ch2;
	int tolerance = 5; // rounding error of 5 pixels is generous
	while (ret == EXIT_SUCCESS) {
		ch1 = fgetc(fp1);
		ch2 = fgetc(fp2);
		if (ch1 == ch2 && ch1 == EOF) {
			break; // all is good
		}
		else if (ch1 == EOF || ch2 == EOF) {
			fprintf(stderr, "'%s' is shorter than '%s'\n",
				argv[(ch1 == EOF ? 1 : 2)],
				argv[(ch2 == EOF ? 1 : 2)]);
			ret = EXIT_FAILURE;
		}
		else if (ch1 - ch2 < -tolerance || ch1 - ch2 > tolerance) {
			fprintf(stderr, "Difference found at byte %d\n", byte_counter);
			ret = EXIT_FAILURE;
		}
		byte_counter++;
	}

	fclose(fp1);
	fclose(fp2);

	return ret;
}

int main(int argc, char * * argv)
{
	if (argc != 7) {
		print_usage(argv[0]);
		if (argc == 2 && strcmp(argv[1], "--help") == 0)
			return EXIT_SUCCESS;
		return EXIT_FAILURE;
	}

	char inputImage[40];
	strcpy(inputImage, argv[1]);
	char compImage[40];
	strcpy(compImage, argv[2]);
	char setting[5];
	strcpy(setting, argv[3]);
	char outputImage[40];
	strcpy(outputImage, argv[4]);
	char outputLinImage[40];
	strcpy(outputLinImage, argv[5]);
	char testLinImage[40];
	strcpy(testLinImage, argv[6]);

	if (setting[0] == 'b')
	{
		Image * test1 = Image_loadbmp(inputImage);

		if (test1 == NULL)
		{
			printf("Failed to load the BMP image: %s", inputImage);
			return EXIT_FAILURE;
		}

		if (Image_savebmp(outputImage, test1) == 0)
		{
			printf("Failed to save to the BMP image: %s", outputImage);
			return EXIT_FAILURE;
		}

		Image_free(test1);
		argv[1] = outputImage;
		argv[2] = compImage;
		int result = compare(argv);
		if (result != 0)
			return result;

		test1 = Image_loadbmp(inputImage);

		if (test1 == NULL)
		{
			printf("Failed to load the BMP image: %s", inputImage);
			return EXIT_FAILURE;
		}

		linearNormalization(test1->width, test1->height, test1->data);

		if (Image_savebmp(outputLinImage, test1) == 0)
		{
			printf("Failed to save to the BMP image: %s", outputLinImage);
			return EXIT_FAILURE;
		}

		argv[1] = outputLinImage;
		argv[2] = testLinImage;
		result = compare(argv);
		if (result != 0)
			return result;
	}

	if (setting[0] == 'e')
	{
		Image * test1 = Image_load(inputImage);

		if (test1 == NULL)
		{
			printf("Failed to load the ee264 image: %s", inputImage);
			return EXIT_FAILURE;
		}

		if (Image_save(outputImage, test1) == 0)
		{
			printf("Failed to save to the ee264 image: %s", outputImage);
			return EXIT_FAILURE;
		}

		Image_free(test1);

		test1 = Image_load(inputImage);

		if (test1 == NULL)
		{
			printf("Failed to load the ee264 image: %s", inputImage);
			return EXIT_FAILURE;
		}

		linearNormalization(test1->width, test1->height, test1->data);

		if (Image_save(outputLinImage, test1) == 0)
		{
			printf("Failed to save to the ee264 image: %s", outputLinImage);
			return EXIT_FAILURE;
		}

		Image_free(test1);
		argv[1] = outputImage;
		argv[2] = compImage;
		int result = compare(argv);
		if (result != 0)
			return result;

		argv[1] = outputLinImage;
		argv[2] = testLinImage;
		result = compare(argv);
		if (result != 0)
			return result;
	}

	return EXIT_SUCCESS;
}

