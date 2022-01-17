#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#define ERROR_ANGLE "Unsupported rotation angle\n"
#define SELECTION_ERROR "The selection must be square\n"

void free_matrix(double **p, uint32_t rows)
{
	// Simple function for freeing a matrix
	for (uint_fast32_t i = 0; i < rows; i++)
		free(p[i]);

	free(p);
	// It works by freeing each line then the matrix itself
}

double **rotate90clockwise(double **a, uint_fast32_t N)
{
	for (uint_fast32_t i = 0; i < N / 2; i++) {
		for (uint_fast32_t j = i; j < N - i - 1; j++) {
			// Swap elements of each cycle
			// in clockwise direction
			double temp = a[i][j];
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
	// We make a copy for each kernel and alloc memory for each with
	// the size of the selection
	double **copy_r, **copy_g, **copy_b, **copy;
	if (photo->type == 2 || photo->type == 1 || photo->type == 4 ||
		photo->type == 5) {
		copy = alloc_image(photo->stop.height - photo->start.height,
						   photo->stop.width - photo->start.width);
	} else if (photo->type == 3 || photo->type == 6) {
		copy_r = alloc_image(photo->stop.height - photo->start.height,
							 photo->stop.width - photo->start.width);

		copy_g = alloc_image(photo->stop.height - photo->start.height,
							 photo->stop.width - photo->start.width);

		copy_b = alloc_image(photo->stop.height - photo->start.height,
							 photo->stop.width - photo->start.width);
	}
	// We copy the selection from the original matrix to a copy with only the
	// selection inside
	for (uint_fast32_t i = photo->start.height; i < photo->stop.height; i++)
		for (uint_fast32_t j = photo->start.width; j < photo->stop.width; j++)
			if (photo->type == 2 || photo->type == 1 || photo->type == 4 ||
				photo->type == 5) {
				copy[i - photo->start.height][j - photo->start.width] =
				photo->bw[i][j];

			} else if (photo->type == 3 || photo->type == 6) {
				copy_r[i - photo->start.height][j - photo->start.width] =
				photo->red[i][j];

				copy_g[i - photo->start.height][j - photo->start.width] =
				photo->green[i][j];

				copy_b[i - photo->start.height][j - photo->start.width] =
				photo->blue[i][j];
			}
	//We proceed to rotate each kernel by 90 degrees
	if (photo->type == 2 || photo->type == 1 || photo->type == 4 ||
	    photo->type == 5) {
		copy = rotate90clockwise(copy, photo->stop.height -
								 photo->start.height);

		} else if (photo->type == 3 || photo->type == 6) {
			copy_r = rotate90clockwise(copy_r, photo->stop.height -
								   photo->start.height);
			copy_g = rotate90clockwise(copy_g, photo->stop.height -
								   photo->start.height);
			copy_b = rotate90clockwise(copy_b, photo->stop.height -
								   photo->start.height);
	}
	// We copy only the pixels from the selection back in the original matrix
	for (uint_fast32_t i = photo->start.height; i < photo->stop.height; i++)
		for (uint_fast32_t j = photo->start.width; j < photo->stop.width; j++)
			if (photo->type == 2 || photo->type == 1 || photo->type == 4 ||
			    photo->type == 5) {
				photo->bw[i][j] = copy[i - photo->start.height][j -
				photo->start.width];
			} else if (photo->type == 3 || photo->type == 6) {
				photo->red[i][j] =
				copy_r[i - photo->start.height][j - photo->start.width];

				photo->green[i][j] =
				copy_g[i - photo->start.height][j - photo->start.width];

				photo->blue[i][j] =
				copy_b[i - photo->start.height][j - photo->start.width];
			}

	// We free the copies made in order not to have memory leaks
	if (photo->type == 2 || photo->type == 1 || photo->type == 4 ||
		photo->type == 5) {
		free_matrix(copy, photo->stop.height - photo->start.height);
	} else if (photo->type == 3 || photo->type == 6) {
		free_matrix(copy_r, photo->stop.height - photo->start.height);

		free_matrix(copy_g, photo->stop.height - photo->start.height);

		free_matrix(copy_b, photo->stop.height - photo->start.height);
	}
}

void rotate_entire_matrix(picture *photo)
{
	// We make a copy for each kernel and alloc memory for each with
	// the size of the selection
	double **copy_r, **copy_g, **copy_b, **copy;
	if (photo->type == 2 || photo->type == 1 || photo->type == 4 ||
	    photo->type == 5) {
		copy = alloc_image(photo->size.height, photo->size.width);
	} else if (photo->type == 3 || photo->type == 6) {
		copy_r = alloc_image(photo->size.height, photo->size.width);

		copy_g = alloc_image(photo->size.height, photo->size.width);

		copy_b = alloc_image(photo->size.height, photo->size.width);
	}
	// We make a copy of the entire matrix
	for (uint_fast32_t i = 0; i < photo->size.height; i++)
		for (uint_fast32_t j = 0; j < photo->size.width; j++)
			if (photo->type == 2 || photo->type == 1 || photo->type == 4 ||
				photo->type == 5) {
				copy[i][j] = photo->bw[i][j];
			} else if (photo->type == 3 || photo->type == 6) {
				copy_r[i][j] = photo->red[i][j];

				copy_g[i][j] = photo->green[i][j];

				copy_b[i][j] = photo->blue[i][j];
			}
	// We free the initial photo
	free_image(photo);
	// We alloc a new photo with the coordinates swapped
	if (photo->type == 2 || photo->type == 1 || photo->type == 4 ||
		photo->type == 5) {
		photo->bw = alloc_image(photo->size.width, photo->size.height);
	} else if (photo->type == 3 || photo->type == 6) {
		photo->red = alloc_image(photo->size.width, photo->size.height);

		photo->green = alloc_image(photo->size.width, photo->size.height);

		photo->blue = alloc_image(photo->size.width, photo->size.height);
	}
	// We rotate the matrix in the initial photo based on the values on
	// the copy made before
	for (uint_fast32_t i = 0; i < photo->size.width; i++)
		for (uint_fast32_t j = 0; j < photo->size.height; j++)
			if (photo->type == 2 || photo->type == 1 || photo->type == 4 ||
				photo->type == 5) {
				photo->bw[i][j] = copy[photo->size.height - j - 1][i];

			} else if (photo->type == 3 || photo->type == 6) {
				photo->red[i][j] = copy_r[photo->size.height - j - 1][i];

				photo->green[i][j] = copy_g[photo->size.height - j - 1][i];

				photo->blue[i][j] = copy_b[photo->size.height - j - 1][i];
			}
	// We proceed to free the copies used
	if (photo->type == 2 || photo->type == 1 || photo->type == 4 ||
		photo->type == 5) {
		free_matrix(copy, photo->size.height);

	} else if (photo->type == 3 || photo->type == 6) {
		free_matrix(copy_r, photo->size.height);

		free_matrix(copy_g, photo->size.height);

		free_matrix(copy_b, photo->size.height);
	}
	// We swap the coordinates for selection and entire photo
	// using bitwise swap
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
	// If we dont have a photo loaded we print accordingly
	if (!photo->loaded) {
		printf("No image loaded\n");
		return;
	}
	// Make the angle integer
	int angle = atoi(rotation);

	// If we dont have a supported angle we print the message
	if (angle % 90) {
		fprintf(stdout, ERROR_ANGLE);
		return;
	}

	// We make the angle positive if we have it negative
	int negative_angle = 0;
	if (angle < 0) {
		angle += 360;
		negative_angle = 1;
	}
	// We count how many rotations we have to do
	int count_rotations = angle / 90;
	uint_fast32_t height = photo->stop.height - photo->start.height;
	uint_fast32_t width = photo->stop.width - photo->start.width;

	//If the selection is not square we print a message
	if (height != width && height != photo->size.height &&
		width != photo->size.width) {
		fprintf(stdout, SELECTION_ERROR);
		return;
	}

	// We make a number of rotations if we have a selection from the matrix
	if (height != photo->size.height || width != photo->size.width) {
		while (count_rotations) {
			rotate_matrix(photo);
			count_rotations--;
		}
	} else {
		// We rotate the entire matrix a number of times
		while (count_rotations) {
			rotate_entire_matrix(photo);
			count_rotations--;
		}
	}
	// We print a message based on the angle
	if (!negative_angle)
		printf("Rotated %d\n", angle);
	else
		printf("Rotated -%d\n", 360 - angle);
}
