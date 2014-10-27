#include "answer07.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <libgen.h>
#include <string.h>

#define BMP_MAGIC_NUMBER 0x4d42

#define FALSE 0
#define TRUE 1

Image * Image_load(const char * filename)
{
	FILE * file = fopen(filename, "rb");

	if (file == NULL)
	{
		return NULL;
	}
		
	ImageHeader* header = malloc(sizeof(ImageHeader));

	if (!fread(&(header->magic_number), sizeof(uint32_t), 1, file))
	{
		free(header);
		fclose(file);
		return NULL;
	}
	if (header->magic_number != ECE264_IMAGE_MAGIC_NUMBER)
	{
		free(header);
		fclose(file);
		return NULL;
	}

	if (!fread(&(header->width), sizeof(uint32_t), 1, file))
	{
		free(header);
		fclose(file);
		return NULL;
	}
	if (header->width == 0)
	{
		free(header);
		fclose(file);
		return NULL;
	}

	if (!fread(&(header->height), sizeof(uint32_t), 1, file))
	{
		free(header);
		fclose(file);
		return NULL;
	}
	if (header->height == 0)
	{
		free(header);
		fclose(file);
		return NULL;
	}

	if (!fread(&(header->comment_len), sizeof(uint32_t), 1, file))
	{
		free(header);
		fclose(file);
		return NULL;
	}
	if (header->comment_len == 0)
	{
		free(header);
		fclose(file);
		return NULL;
	}

	Image* image  = malloc(sizeof(Image));

	image->width = header->width;
	image->height = header->height;

	image->comment = malloc(sizeof(char) * (int)(header->comment_len));
	if (image->comment == NULL)
	{
		free(image->comment);
		free(image);
		free(header);
		fclose(file);
		return NULL;
	}

	image->data = malloc(sizeof(uint8_t) * image->width * image->height);
	if (image->data == NULL)
	{
		free(image->comment);
		free(image->data);
		free(image);
		free(header);
		fclose(file);
		return NULL;
	}

	int i;
	for (i = 0; i < ((int)header->comment_len - 1); i++)
	{
		//image->comment[i] = fgetc(file);
		if (!fread(&(image->comment[i]), sizeof(char), 1, file))
		{
			free(image->comment);
			free(image->data);
			free(image);
			free(header);
			fclose(file);
			return NULL;
		}
	}
	if (fgetc(file) != '\0')
	{
		free(image->comment);
		free(image->data);
		free(image);
		free(header);
		fclose(file);
		return NULL;
	}
	image->comment[i] = '\0';

	for (i = 0; i < (image->width * image->height); i++)
	{
		if (!fread(&(image->data[i]), sizeof(uint8_t), 1, file))
		{
			free(image->comment);
			free(image->data);
			free(image);
			free(header);
			fclose(file);
			return NULL;
		}
	}

	fread(image->data, sizeof(uint8_t), 1, file);

	if (!feof(file))
	{
		free(image->comment);
		free(image->data);
		free(image);
		free(header);
		fclose(file);
		return NULL;
	}

	free(header);
	return image;
}

int Image_save(const char * filename, Image * image)
{
	FILE * file = fopen(filename, "wb");

	if (file == NULL)
		return FALSE;

	uint32_t magicNumber[1] = { (uint32_t)ECE264_IMAGE_MAGIC_NUMBER };
	fwrite(magicNumber, sizeof(uint32_t), 1, file);

	uint32_t width[1] = { (uint32_t)image->width };
	fwrite(width, sizeof(uint32_t), 1, file);

	uint32_t height[1] = { (uint32_t)image->height };
	fwrite(height, sizeof(uint32_t), 1, file);

	uint32_t commentLen[1] = { (uint32_t)(strlen(image->comment) + 1) };
	fwrite(commentLen, sizeof(uint32_t), 1, file);

	int i;
	for (i = 0; i < (int)commentLen[0]; i++)
	{
		fwrite(&image->comment[i], sizeof(char), 1, file);
	}

	for (i = 0; i < (image->width * image->height); i++)
	{
		fwrite(&image->data[i], sizeof(uint8_t), 1, file);
	}

	fclose(file);

	return TRUE;
}

void Image_free(Image * image)
{
	free(image->comment);
	free(image->data);
	free(image);
}

void linearNormalization(int width, int height, uint8_t * intensity)
{
	int max = 0;
	int min = 255;
	int i;

	for (i = 0; i < width * height; i++)
	{
		if ((int)intensity[i] > max)
			max = (int)intensity[i];
		if ((int)intensity[i] < min)
			min = (int)intensity[i];
	}

	for (i = 0; i < width * height; i++)
	{
		intensity[i] = (uint8_t)((intensity[i] - min) * 255.0 / (max - min));
	}
}