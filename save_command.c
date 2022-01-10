#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#define LENGHTMAX 100
void save_bw(picture photo, char *filename, char type)
{
	FILE *file = fopen(filename, "w");
	if (!file)
	{
		printf("Failed to load %s\n", filename);
		return;
	}
	if (type == 'a')
		fprintf(file, "P%d\n", photo.type);
	else
	{
		fprintf(file, "P%d\n", photo.type + 3);
	}
	fprintf(file, "%ld %ld\n", photo.size.width, photo.size.height);
	if (photo.type == 2)
		fprintf(file, "%d\n", photo.max);
	for (uint_fast32_t i = 0; i < photo.size.height; i++)
	{
		for (uint_fast32_t j = 0; j < photo.size.width; j++)
			if (type == 'a')
				fprintf(file, "%d ", photo.bw[i][j]);
			else
				fwrite(&photo.bw[i][j], sizeof(uint_fast8_t), 1, file);
		if (type == 'a')
			fprintf(file, "%s", "\n");
	}
	printf("Saved %s\n", filename);
	fclose(file);
}

void save_rgb(picture photo, char *filename, char type)
{
	FILE *file = fopen(filename, "w");
	if (!file)
	{
		printf("Failed to load %s\n", filename);
		return;
	}
	if (type == 'a')
		fprintf(file, "P%d\n", photo.type);
	else
	{
		fprintf(file, "P%d\n", photo.type + 3);
	}
	fprintf(file, "%ld %ld\n", photo.size.width, photo.size.height);
	fprintf(file, "%d\n", photo.max);
	for (uint_fast32_t i = 0; i < photo.size.height; i++)
	{
		for (uint_fast32_t j = 0; j < photo.size.width; j++)
			if (type == 'a')
				fprintf(file, "%d %d %d ", photo.red[i][j], photo.green[i][j], photo.blue[i][j]);
			else
			{
				fwrite(&photo.red[i][j], sizeof(uint_fast8_t), 1, file);
				fwrite(&photo.green[i][j], sizeof(uint_fast8_t), 1, file);
				fwrite(&photo.blue[i][j], sizeof(uint_fast8_t), 1, file);
			}
		if (type == 'a')
			fprintf(file, "%s", "\n");
	}
	printf("Saved %s\n", filename);
	fclose(file);
}

void save_image(picture photo, char *filename)
{
	char buff;
	buff = getchar();
	if (buff == ' ')
	{
		char rest[LENGHTMAX];
		scanf("%s", rest);
		if (!photo.loaded)
		{
			printf("No image loaded\n");
			return;
		}

		if (photo.type == 4 || photo.type == 5 || photo.type == 6)
			photo.type -= 3;
		if (photo.type == 2 || photo.type == 1)
		{
			save_bw(photo, filename, 'a');
		}
		if (photo.type == 3)
		{
			save_rgb(photo, filename, 'a');
		}
	}
	else if (buff == '\n')
	{
		if (!photo.loaded)
		{
			printf("No image loaded\n");
			return;
		}

		if (photo.type == 4 || photo.type == 5 || photo.type == 6)
			photo.type -= 3;
		if (photo.type == 2 || photo.type == 1)
		{
			save_bw(photo, filename, buff);
		}
		if (photo.type == 3)
		{
			save_rgb(photo, filename, buff);
		}
	}
}
