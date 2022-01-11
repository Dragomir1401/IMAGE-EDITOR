#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#define MAX_LINE_SIZE 1000
uint_fast8_t **alloc_image(int height, int width)
{
	uint_fast8_t **image = malloc(height * sizeof(uint_fast8_t *));
	if (!image)
		printf("Cant alloc memory\n");

	for (int i = 0; i < height; i++) {
		image[i] = malloc(width * sizeof(uint_fast8_t));

		if (!image[i])
			printf("Cant alloc memory\n");
	}
	return image;
}

int check_comment(FILE *file, int *first_comment)
{
	char hashtag, trash[MAX_LINE_SIZE];
	if (*first_comment == 0)
		fseek(file, 1, SEEK_CUR);
	fscanf(file, "%c", &hashtag);
	if (hashtag == '#') {
		fgets(trash, MAX_LINE_SIZE, file);
		return 1;
	}
	return 0;
}

int read_image(picture *photo, char *filename)
{
	int height, width, max;
	FILE *file = fopen(filename, "r");
	if (!file) {
		printf("Failed to load %s\n", filename);
		return 0;
	}
	fseek(file, 3, SEEK_CUR);
	//int first_comment = 1;
	//check_comment(file, &first_comment);
	//first_comment = 0;
	fscanf(file, "%d%d", &width, &height);
	//check_comment(file, &first_comment);
	photo->size.height = height;
	photo->size.width = width;
	photo->max = 1;
	if (photo->type == 2 || photo->type == 5) {
		fscanf(file, "%d\n", &max);
		photo->max = max;
	}
	photo->bw = alloc_image(height, width);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (photo->type == 2)
				fscanf(file, "%hhu", &photo->bw[i][j]);
			else if (photo->type == 5)
				fread(&photo->bw[i][j], sizeof(uint_fast8_t), 1, file);

	fclose(file);
	return 1;
}

int read_image_color(picture *photo, char *filename)
{
	int height, width, max;
	FILE *file = fopen(filename, "r");
	if (!file) {
		printf("Failed to load %s\n", filename);
		return 0;
	}
	fseek(file, 3, SEEK_CUR);
	// int first_comment = 1;
	// check_comment(file, &first_comment);
	// first_comment = 0;
	fscanf(file, "%d%d", &width, &height);
	//check_comment(file, &first_comment);
	photo->size.height = height;
	photo->size.width = width;
	photo->max = 1;

	fscanf(file, "%d\n", &max);
	photo->max = max;

	photo->red = alloc_image(height, width);
	photo->green = alloc_image(height, width);
	photo->blue = alloc_image(height, width);

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			if (photo->type == 3) {
				fscanf(file, "%hhu", &photo->red[i][j]);

				fscanf(file, "%hhu", &photo->green[i][j]);

				fscanf(file, "%hhu", &photo->blue[i][j]);
			} else if (photo->type == 6) {
				fread(&photo->red[i][j], sizeof(uint_fast8_t), 1, file);

				fread(&photo->green[i][j], sizeof(uint_fast8_t), 1, file);

				fread(&photo->blue[i][j], sizeof(uint_fast8_t), 1, file);
			}
		}

	fclose(file);
	return 1;
}

int load_command(picture *photo, char *filename)
{
	FILE *file = fopen(filename, "r");
	if (!file) {
		printf("Failed to load %s\n", filename);
		photo->loaded = 0;
		return 0;
	}

	char string[2];
	fscanf(file, "%s", string);
	int type = string[1] - '0';
	photo->type = type;

	if (photo->type == 2 || photo->type == 1 || photo->type == 4 ||
		photo->type == 5) {
		if (read_image(photo, filename))
			printf("Loaded %s\n", filename);
	}

	if (photo->type == 3 || photo->type == 6) {
		if (read_image_color(photo, filename))
			printf("Loaded %s\n", filename);
	}

	photo->loaded = 1;
	fclose(file);
	return 1;
}
