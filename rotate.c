#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#define ERROR_ANGLE "Unsupported rotation angle\n"
#define SELECTION_ERROR "The selection must be square\n"

void free_matrix(uint_fast8_t **p, uint32_t rows)
{
	//simple function for freeing a matrix
	for (uint_fast32_t i = 0; i < rows; i++)
		free(p[i]);

	free(p);
	//it works by freeing each line then the matrix itself
}

uint_fast8_t **rotate90clockwise(uint_fast8_t **a, uint_fast32_t N)
{

	// Traverse each cycle
	for (uint_fast32_t i = 0; i < N / 2; i++)
	{
		for (uint_fast32_t j = i; j < N - i - 1; j++)
		{

			// Swap elements of each cycle
			// in clockwise direction
			uint_fast8_t temp = a[i][j];
			a[i][j] = a[N - 1 - j][i];
			a[N - 1 - j][i] = a[N - 1 - i][N - 1 - j];
			a[N - 1 - i][N - 1 - j] = a[j][N - 1 - i];
			a[j][N - 1 - i] = temp;
		}
	}
	return a;
}

void rotate_matrix(picture *photo)
{
	uint_fast8_t **copy_r, **copy_g, **copy_b, **copy;
	if (photo->type == 2 || photo->type == 1 || photo->type == 4 || photo->type == 5)
	{
		copy = alloc_image(photo->stop.height - photo->start.height, photo->stop.width - photo->start.width);
	}
	else if (photo->type == 3 || photo->type == 6)
	{
		copy_r = alloc_image(photo->stop.height - photo->start.height, photo->stop.width - photo->start.width);
		copy_g = alloc_image(photo->stop.height - photo->start.height, photo->stop.width - photo->start.width);
		copy_b = alloc_image(photo->stop.height - photo->start.height, photo->stop.width - photo->start.width);
	}
	for (uint_fast32_t i = photo->start.height; i < photo->stop.height; i++)
		for (uint_fast32_t j = photo->start.width; j < photo->stop.width; j++)
			if (photo->type == 2 || photo->type == 1 || photo->type == 4 || photo->type == 5)
				copy[i - photo->start.height][j - photo->start.width] = photo->bw[i][j];
			else if (photo->type == 3 || photo->type == 6)
			{
				copy_r[i - photo->start.height][j - photo->start.width] = photo->red[i][j];
				copy_g[i - photo->start.height][j - photo->start.width] = photo->green[i][j];
				copy_b[i - photo->start.height][j - photo->start.width] = photo->blue[i][j];
			}
	if (photo->type == 2 || photo->type == 1 || photo->type == 4 || photo->type == 5)
		copy = rotate90clockwise(copy, photo->stop.height - photo->start.height);
	else if (photo->type == 3 || photo->type == 6)
	{
		copy_r = rotate90clockwise(copy_r, photo->stop.height - photo->start.height);
		copy_g = rotate90clockwise(copy_g, photo->stop.height - photo->start.height);
		copy_b = rotate90clockwise(copy_b, photo->stop.height - photo->start.height);
	}
	for (uint_fast32_t i = photo->start.height; i < photo->stop.height; i++)
		for (uint_fast32_t j = photo->start.width; j < photo->stop.width; j++)
			if (photo->type == 2 || photo->type == 1 || photo->type == 4 || photo->type == 5)
				photo->bw[i][j] = copy[i - photo->start.height][j - photo->start.width];
			else if (photo->type == 3 || photo->type == 6)
			{
				photo->red[i][j] = copy_r[i - photo->start.height][j - photo->start.width];
				photo->green[i][j] = copy_g[i - photo->start.height][j - photo->start.width];
				photo->blue[i][j] = copy_b[i - photo->start.height][j - photo->start.width];
			}
	if (photo->type == 2 || photo->type == 1 || photo->type == 4 || photo->type == 5)
		free_matrix(copy, photo->stop.height - photo->start.height); //sDADA
	else if (photo->type == 3 || photo->type == 6)
	{
		free_matrix(copy_r, photo->stop.height - photo->start.height);
		free_matrix(copy_g, photo->stop.height - photo->start.height);
		free_matrix(copy_b, photo->stop.height - photo->start.height);
	}
}

void rotate_entire_matrix(picture *photo)
{
	uint_fast8_t **copy_r, **copy_g, **copy_b, **copy;
	if (photo->type == 2 || photo->type == 1 || photo->type == 4 || photo->type == 5)
	{
		copy = alloc_image(photo->size.height, photo->size.width);
	}
	else if (photo->type == 3 || photo->type == 6)
	{
		copy_r = alloc_image(photo->size.height, photo->size.width);
		copy_g = alloc_image(photo->size.height, photo->size.width);
		copy_b = alloc_image(photo->size.height, photo->size.width);
	}
	for (uint_fast32_t i = 0; i < photo->size.height; i++)
		for (uint_fast32_t j = 0; j < photo->size.width; j++)
			if (photo->type == 2 || photo->type == 1 || photo->type == 4 || photo->type == 5)
				copy[i][j] = photo->bw[i][j];
			else if (photo->type == 3 || photo->type == 6)
			{
				copy_r[i][j] = photo->red[i][j];
				copy_g[i][j] = photo->green[i][j];
				copy_b[i][j] = photo->blue[i][j];
			}

	free_image(photo);
	//printf("~~~~%d~~~~%d~~~~~", photo->size.height, photo->size.width);
	if (photo->type == 2 || photo->type == 1 || photo->type == 4 || photo->type == 5)
	{
		photo->bw = alloc_image(photo->size.width, photo->size.height);
	}
	else if (photo->type == 3 || photo->type == 6)
	{
		photo->red = alloc_image(photo->size.width, photo->size.height);
		photo->green = alloc_image(photo->size.width, photo->size.height);
		photo->blue = alloc_image(photo->size.width, photo->size.height);
	}
	for (uint_fast32_t i = 0; i < photo->size.width; i++)
		for (uint_fast32_t j = 0; j < photo->size.height; j++)
			if (photo->type == 2 || photo->type == 1 || photo->type == 4 || photo->type == 5)
				photo->bw[i][j] = copy[photo->size.height - j - 1][i];
			else if (photo->type == 3 || photo->type == 6)
			{
				photo->red[i][j] = copy_r[photo->size.height - j - 1][i];
				photo->green[i][j] = copy_g[photo->size.height - j - 1][i];
				photo->blue[i][j] = copy_b[photo->size.height - j - 1][i];
			}
	if (photo->type == 2 || photo->type == 1 || photo->type == 4 || photo->type == 5)
		free_matrix(copy, photo->size.height);
	else if (photo->type == 3 || photo->type == 6)
	{
		free_matrix(copy_r, photo->size.height);
		free_matrix(copy_g, photo->size.height);
		free_matrix(copy_b, photo->size.height);
	}

	photo->size.height = photo->size.height ^ photo->size.width;
	photo->size.width = photo->size.height ^ photo->size.width;
	photo->size.height = photo->size.height ^ photo->size.width;

	photo->stop.height = photo->stop.height ^ photo->stop.width;
	photo->stop.width = photo->stop.height ^ photo->stop.width;
	photo->stop.height = photo->stop.height ^ photo->stop.width;

	photo->start.height = photo->start.height ^ photo->start.width;
	photo->start.width = photo->start.height ^ photo->start.width;
	photo->start.height = photo->start.height ^ photo->start.width;
}

void rotate_image(picture *photo, char *rotation)
{
	if (!photo->loaded)
	{
		printf("No image loaded\n");
		return;
	}
	int angle = atoi(rotation);

	if (angle % 90)
	{
		fprintf(stdout, ERROR_ANGLE);
		return;
	}
	int negative_angle = 0;
	if (angle < 0)
	{
		angle += 360;
		negative_angle = 1;
	}
	int count_rotations = angle / 90;
	uint_fast32_t height = photo->stop.height - photo->start.height;
	uint_fast32_t width = photo->stop.width - photo->start.width;

	if (height != width && height != photo->size.height && width != photo->size.width)
	{
		fprintf(stdout, SELECTION_ERROR);
		return;
	}
	if (height != photo->size.height || width != photo->size.width)
	{
		while (count_rotations)
		{
			rotate_matrix(photo);
			count_rotations--;
		}
	}
	else
	{
		while (count_rotations)
		{
			rotate_entire_matrix(photo);
			count_rotations--;
		}
	}

	if (!negative_angle)
		printf("Rotated %d\n", angle);
	else
	{
		printf("Rotated -%d\n", 360 - angle);
	}
}