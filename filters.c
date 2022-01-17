#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#include <math.h>
#define LENGHTMAX 100

double clamp(double x, double max)
{
	// Function to keep a value in an interval
	int min = 0;
	if (x < min)
		x = min;
	else if (x > max)
		x = max;
	return x;
}

void apply_edge(picture photo, picture *copy, uint_fast32_t i, uint_fast32_t j)
{
	// Functions which applies edge filter to a single pixel
	// selected by coordinates
	double edge[] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
	double new_pixel_red = 0, new_pixel_green = 0, new_pixel_blue = 0;
	for (int k = -1; k < 2; k++)
		for (int l = -1; l < 2; l++) {
			// Putting the new values in 3 variables by multiplying
			// each neighbour pixel with the value from the vector
			// of the filter
			new_pixel_red += photo.red[i + k][j + l] *
							 edge[k + l + 2 * (k + 2)];

			new_pixel_green += photo.green[i + k][j + l] *
							   edge[k + l + 2 * (k + 2)];

			new_pixel_blue += photo.blue[i + k][j + l] *
							  edge[k + l + 2 * (k + 2)];
		}
	// Reduce to an interval
	copy->red[i][j] = clamp(new_pixel_red, photo.max);
	copy->green[i][j] = clamp(new_pixel_green, photo.max);
	copy->blue[i][j] = clamp(new_pixel_blue, photo.max);
}

void apply_sharpen(picture photo, picture *copy, uint_fast32_t i,
				   uint_fast32_t j)
{
	// Functions which applies sharpen filter to a single pixel
	// selected by coordinates
	double sharpen[] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
	double new_pixel_red = 0, new_pixel_green = 0, new_pixel_blue = 0;

	for (int k = -1; k < 2; k++)
		for (int l = -1; l < 2; l++) {
			// Putting the new values in 3 variables by multiplying
			// each neighbour pixel with the value from the vector
			// of the filter
			new_pixel_red += photo.red[i + k][j + l] *
							 sharpen[k + l + 2 * (k + 2)];

			new_pixel_green += photo.green[i + k][j + l] *
							   sharpen[k + l + 2 * (k + 2)];

			new_pixel_blue += photo.blue[i + k][j + l] *
							  sharpen[k + l + 2 * (k + 2)];
		}
	// Reduce to an interval
	copy->red[i][j] = clamp(new_pixel_red, photo.max);
	copy->green[i][j] = clamp(new_pixel_green, photo.max);
	copy->blue[i][j] = clamp(new_pixel_blue, photo.max);
}

void apply_blur(picture photo, picture *copy, uint_fast32_t i, uint_fast32_t j)
{
	// Functions which applies blur filter to a single pixel
	// selected by coordinates
	double box_blur[] = {0.1111, 0.1111, 0.1111, 0.1111, 0.1111, 0.1111,
						 0.1111, 0.1111, 0.1111};
	double new_pixel_red = 0, new_pixel_green = 0, new_pixel_blue = 0;

	for (int k = -1; k < 2; k++)
		for (int l = -1; l < 2; l++) {
			// Putting the new values in 3 variables by multiplying
			// each neighbour pixel with the value from the vector
			// of the filter
			new_pixel_red += photo.red[i + k][j + l] *
							 box_blur[k + l + 2 * (k + 2)];

			new_pixel_green += photo.green[i + k][j + l] *
							   box_blur[k + l + 2 * (k + 2)];

			new_pixel_blue += photo.blue[i + k][j + l] *
							  box_blur[k + l + 2 * (k + 2)];
		}
	// Reduce to an interval
	copy->red[i][j] = clamp(new_pixel_red, photo.max);
	copy->green[i][j] = clamp(new_pixel_green, photo.max);
	copy->blue[i][j] = clamp(new_pixel_blue, photo.max);
}

void apply_gaussian_blur(picture photo, picture *copy, uint_fast32_t i,
						 uint_fast32_t j)
{
	// Functions which applies gaussian_blur filter to a single pixel
	// selected by coordinates
	double gaussian_blur[] = {0.0625, 0.125, 0.0625, 0.125, 0.25, 0.125,
							  0.0625, 0.125, 0.0625};
	double new_pixel_red = 0, new_pixel_green = 0, new_pixel_blue = 0;
	for (int k = -1; k < 2; k++)
		for (int l = -1; l < 2; l++) {
			// Putting the new values in 3 variables by multiplying
			// each neighbour pixel with the value from the vector
			// of the filter
			new_pixel_red += photo.red[i + k][j + l] *
							 gaussian_blur[k + l + 2 * (k + 2)];

			new_pixel_green += photo.green[i + k][j + l] *
							   gaussian_blur[k + l + 2 * (k + 2)];

			new_pixel_blue += photo.blue[i + k][j + l] *
							  gaussian_blur[k + l + 2 * (k + 2)];
		}
	// Reduce the new pixels to an interval based on max value
	copy->red[i][j] = clamp(new_pixel_red, photo.max);
	copy->green[i][j] = clamp(new_pixel_green, photo.max);
	copy->blue[i][j] = clamp(new_pixel_blue, photo.max);
}

void apply_filter(picture *photo, char command[])
{
	char buff;
	buff = getchar(); // If we have a filter after APPLY we proceed else not
	if (buff != ' ') {
		if (!photo->loaded) { // If we have no photo loaded and no filter
			printf("No image loaded\n");
			return;
		}
	// If we have no filter specified
	printf("Invalid command\n");
	return;
	}
	char filter[LENGHTMAX]; // Read the filter
	scanf("%s", filter);

	if (!photo->loaded) { // If we have no photo loaded
		printf("No image loaded\n");
		return;
	}
	if (strcmp(command, "APPLY")) { // If APPLY is written wrong
		printf("Invalid command\n");
		return;
	}
	int charlie_chaplin = 0; // If we try to apply filters b&w or grayscale
	if (photo->type != 3 && photo->type != 6)
		charlie_chaplin = 1;

	if ((!strcmp(filter, "EDGE") || !strcmp(filter, "SHARPEN") ||
		 !strcmp(filter, "BLUR") || !strcmp(filter, "GAUSSIAN_BLUR")) &&
		 !charlie_chaplin) { // If the filter is correct we make a copy
		picture copy = {};
		copy.size = photo->size;
		copy.type = photo->type;
		copy.max = photo->max;
		// Alloc each kernel for the copy
		copy.red = alloc_image(photo->size.height, photo->size.width);
		copy.green = alloc_image(photo->size.height, photo->size.width);
		copy.blue = alloc_image(photo->size.height, photo->size.width);

		for (uint_fast32_t i = 0; i < photo->size.height; i++)
			for (uint_fast32_t j = 0; j < photo->size.width; j++)
				// If we are in the selection
				if (i >= photo->start.height && j >= photo->start.width &&
					i < photo->stop.height && j < photo->stop.width &&
					i > 0 && j > 0 && i < photo->size.height - 1 &&
					j < photo->size.width - 1) {
					// Apply the requested filter for every pixel
					if (!strcmp(filter, "EDGE"))
						apply_edge(*photo, &copy, i, j);

					else if (!strcmp(filter, "SHARPEN"))
						apply_sharpen(*photo, &copy, i, j);

					else if (!strcmp(filter, "BLUR"))
						apply_blur(*photo, &copy, i, j);

					else if (!strcmp(filter, "GAUSSIAN_BLUR"))
						apply_gaussian_blur(*photo, &copy, i, j);
				} else { // If not in the selection we put the same pixels
					copy.red[i][j] = photo->red[i][j];
					copy.green[i][j] = photo->green[i][j];
					copy.blue[i][j] = photo->blue[i][j];
				}
		// Moving each element from the copy to the initial photo
		for (uint_fast32_t i = 0; i < photo->size.height; i++)
			for (uint_fast32_t j = 0; j < photo->size.width; j++) {
				photo->red[i][j] = copy.red[i][j];
				photo->green[i][j] = copy.green[i][j];
				photo->blue[i][j] = copy.blue[i][j];
			}
		free_image(&copy); // free the copy used
		photo->loaded = 1;
		printf("APPLY %s done\n", filter);
	} else {
		if (photo->type != 3 && photo->type != 6) {
			printf("Easy, Charlie Chaplin\n"); // Message for not using RGB img
			return;
		}
		printf("APPLY parameter invalid\n"); // If we spelled a filter wrong
	}
}

