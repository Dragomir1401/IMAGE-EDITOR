#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#define MAX_LINE_SIZE 1000

void free_lines(double **image, int height)
{
	for (int i = 0; i < height; i++)
		free(image[i]);
}

double **alloc_image(int height, int width)
{
	// Function to alloc a matrix with double elements
	double **image = malloc(height * sizeof(double *));
	if (!image)
		printf("Cant alloc memory\n");

	for (int i = 0; i < height; i++) {
		image[i] = malloc(width * sizeof(double));

		// If we cant alloc each line we dealloc all lines and print a message
		if (!image[i]) {
			printf("Cant alloc memory\n");
			free_lines(image, height);
		}
	}
	return image;
}

int check_comment(FILE *file)
{
	// Function that checks if there is a comment in the header
	char hashtag, trash[MAX_LINE_SIZE] = "";

	hashtag = fgetc(file);
	// Verify if first character of a line is # else put it back for read
	if (hashtag == '#') {
		fgets(trash, MAX_LINE_SIZE, file);
		return 1;
	}

	ungetc(hashtag, file);
	return 0;
}

int read_image(picture *photo, char *filename)
{
	int height, width, max;
	// Open file for read operation
	FILE *file = fopen(filename, "r");
	if (!file) {
		printf("Failed to load %s\n", filename);
		return 0;
	}
	// Move 3 places meaning after 'P3' for example
	fseek(file, 3, SEEK_CUR);
	// Checking for comment
	check_comment(file);

	fscanf(file, "%d%d", &width, &height);
	check_comment(file);

	photo->size.height = height;
	photo->size.width = width;

	photo->max = 1;
	// Reading the max value only for not black and white types
	if (photo->type == 2 || photo->type == 5) {
		fscanf(file, "%d\n", &max);
		check_comment(file);
		photo->max = max;
	}
	// Alloc matrix for grayscale
	photo->bw = alloc_image(height, width);

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (photo->type == 2) {
				// Reading using a tmp which turns double before going
				// in matrix
				uint_fast8_t tmp;

				fscanf(file, "%hhu", &tmp);
				photo->bw[i][j] = (double)tmp;
			} else if (photo->type == 5) {
				// Reading using a tmp which turns double before putting
				// it in matrix but for binary read with fread from file stream
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

	// Checking for comment
	check_comment(file);

	fscanf(file, "%d%d", &width, &height);
	// Checking for comment
	check_comment(file);

	photo->size.height = height;
	photo->size.width = width;
	photo->max = 1;

	fscanf(file, "%d\n", &max);
	// Checking for comment
	check_comment(file);

	photo->max = max;
	// Alloc 3 matrices for each color RGB
	photo->red = alloc_image(height, width);
	photo->green = alloc_image(height, width);
	photo->blue = alloc_image(height, width);

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			if (photo->type == 3) {
				// Reading using a tmp which turns double before putting
				// it in matrix
				uint_fast8_t tmp;

				fscanf(file, "%hhu", &tmp);
				photo->red[i][j] = (double)tmp;

				fscanf(file, "%hhu", &tmp);
				photo->green[i][j] = (double)tmp;

				fscanf(file, "%hhu", &tmp);
				photo->blue[i][j] = (double)tmp;
			} else if (photo->type == 6) {
				// Reading using a tmp which turns double before putting
				// it in matrix but for binary read with fread from file stream
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
	// Reading a string like P5 and getting the type integer pout of it
	char string[2];
	fscanf(file, "%s", string);
	int type = string[1] - '0';
	photo->type = type;

	// Reading for black and white and grayscale
	if (photo->type == 2 || photo->type == 1 || photo->type == 4 ||
		photo->type == 5) {
		if (read_image(photo, filename))
			printf("Loaded %s\n", filename);
	}

	// Reading for RGB images
	if (photo->type == 3 || photo->type == 6) {
		if (read_image_color(photo, filename))
			printf("Loaded %s\n", filename);
	}

	// Marking the photo as loaded
	photo->loaded = 1;
	fclose(file);
	return 1;
}
