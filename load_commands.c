#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#define MAX_LINE_SIZE 1000
// TO DO COMMENTS
double **alloc_image(int height, int width)
{
	double **image = malloc(height * sizeof(double *));
	if (!image)
		printf("Cant alloc memory\n");

	for (int i = 0; i < height; i++) {
		image[i] = malloc(width * sizeof(double));

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
	// TO DO CHECK COMMENTS
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
			if (photo->type == 2) {
				uint_fast8_t tmp;

				fscanf(file, "%hhu", &tmp);
				photo->bw[i][j] = (double)tmp;
			} else if (photo->type == 5) {
				uint_fast8_t tmp;
				fread(&tmp, sizeof(uint_fast8_t), 1, file);
				photo->bw[i][j] = (double)tmp;
			}

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
				uint_fast8_t tmp;

				fscanf(file, "%hhu", &tmp);
				photo->red[i][j] = (double)tmp;

				fscanf(file, "%hhu", &tmp);
				photo->green[i][j] = (double)tmp;

				fscanf(file, "%hhu", &tmp);
				photo->blue[i][j] = (double)tmp;
			} else if (photo->type == 6) {
				uint_fast8_t tmp;
				fread(&tmp, sizeof(uint_fast8_t), 1, file);
				photo->red[i][j] = (double)tmp;

				fread(&tmp, sizeof(uint_fast8_t), 1, file);
				photo->green[i][j] = (double)tmp;

				fread(&tmp, sizeof(uint_fast8_t), 1, file);
				photo->blue[i][j] = (double)tmp;
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
