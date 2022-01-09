#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#include <math.h>
#define LENGHTMAX 100
uint_fast8_t clamp(double x, uint_fast8_t max)
{
	int min = 0;
	if (x < min)
		x = min;
	else if (x > max)
		x = max;
	return x;
}

void apply_edge(picture photo, picture copy, uint_fast32_t i, uint_fast32_t j)
{
	double edge[] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
	double new_pixel_red = 0, new_pixel_green = 0, new_pixel_blue = 0;
	for (int k = -1; k < 2; k++)
		for (int l = -1; l < 2; l++)
		{
			new_pixel_red += (double)photo.red[i + k][j + l] * edge[k + l + 2 * (k + 2)];
			new_pixel_green += (double)photo.green[i + k][j + l] * edge[k + l + 2 * (k + 2)];
			new_pixel_blue += (double)photo.blue[i + k][j + l] * edge[k + l + 2 * (k + 2)];
		}
	copy.red[i][j] = clamp(new_pixel_red, photo.max);
	copy.green[i][j] = clamp(new_pixel_green, photo.max);
	copy.blue[i][j] = clamp(new_pixel_blue, photo.max);
}

void apply_sharpen(picture photo, picture copy, uint_fast32_t i, uint_fast32_t j)
{
	double sharpen[] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
	double new_pixel_red = 0, new_pixel_green = 0, new_pixel_blue = 0;
	for (int k = -1; k < 2; k++)
		for (int l = -1; l < 2; l++)
		{
			new_pixel_red += (double)photo.red[i + k][j + l] * sharpen[k + l + 2 * (k + 2)];
			new_pixel_green += (double)photo.green[i + k][j + l] * sharpen[k + l + 2 * (k + 2)];
			new_pixel_blue += (double)photo.blue[i + k][j + l] * sharpen[k + l + 2 * (k + 2)];
		}
	copy.red[i][j] = clamp(new_pixel_red, photo.max);
	copy.green[i][j] = clamp(new_pixel_green, photo.max);
	copy.blue[i][j] = clamp(new_pixel_blue, photo.max);
}

void apply_blur(picture photo, picture copy, uint_fast32_t i, uint_fast32_t j)
{
	double box_blur[] = {0.1111, 0.1111, 0.1111, 0.1111, 0.1111, 0.1111, 0.1111, 0.1111, 0.1111};
	double new_pixel_red = 0, new_pixel_green = 0, new_pixel_blue = 0;
	for (int k = -1; k < 2; k++)
		for (int l = -1; l < 2; l++)
		{
			new_pixel_red += (double)photo.red[i + k][j + l] * box_blur[k + l + 2 * (k + 2)];
			new_pixel_green += (double)photo.green[i + k][j + l] * box_blur[k + l + 2 * (k + 2)];
			new_pixel_blue += (double)photo.blue[i + k][j + l] * box_blur[k + l + 2 * (k + 2)];
		}
	copy.red[i][j] = clamp(new_pixel_red, photo.max);
	copy.green[i][j] = clamp(new_pixel_green, photo.max);
	copy.blue[i][j] = clamp(new_pixel_blue, photo.max);
}

void apply_gaussian_blur(picture photo, picture copy, uint_fast32_t i, uint_fast32_t j)
{
	double gaussian_blur[] = {0.0625, 0.125, 0.0625, 0.125, 0.25, 0.125, 0.0625, 0.125, 0.0625};
	double new_pixel_red = 0, new_pixel_green = 0, new_pixel_blue = 0;
	for (int k = -1; k < 2; k++)
		for (int l = -1; l < 2; l++)
		{
			new_pixel_red += (double)photo.red[i + k][j + l] * gaussian_blur[k + l + 2 * (k + 2)];
			new_pixel_green += (double)photo.green[i + k][j + l] * gaussian_blur[k + l + 2 * (k + 2)];
			new_pixel_blue += (double)photo.blue[i + k][j + l] * gaussian_blur[k + l + 2 * (k + 2)];
		}
	copy.red[i][j] = clamp(new_pixel_red, photo.max);
	copy.green[i][j] = clamp(new_pixel_green, photo.max);
	copy.blue[i][j] = clamp(new_pixel_blue, photo.max);
}

void apply_filter(picture *photo, char command[])
{
	if (!photo->loaded)
	{
		printf("No image loaded\n");
		return;
	}
	if (photo->type != 3 && photo->type != 6)
	{
		printf("Invalid command\n"); //where is easy charlie chaplin
		return;
	}
	char buff;
	buff = getchar();
	if (buff == ' ')
	{
		char filter[LENGHTMAX];
		scanf("%s", filter);
		if (strcmp(command, "APPLY"))
		{
			printf("Invalid command\n");
			return;
		}
		if (!strcmp(filter, "EDGE") || !strcmp(filter, "SHARPEN") || !strcmp(filter, "BLUR") || !strcmp(filter, "GAUSSIAN_BLUR"))
		{

			picture copy = {};
			copy.size = photo->size;
			copy.type = photo->type;
			copy.type = photo->type;
			copy.red = alloc_image(photo->size.height, photo->size.width);
			copy.green = alloc_image(photo->size.height, photo->size.width);
			copy.blue = alloc_image(photo->size.height, photo->size.width);
			int broke = 0;
			for (uint_fast32_t i = 0; i < photo->size.height; i++)
				for (uint_fast32_t j = 0; j < photo->size.width; j++)
					if (i >= photo->start.height && j >= photo->start.width && i < photo->stop.height && j < photo->stop.width && i > 0 && j > 0 && i < photo->size.height - 1 && j < photo->size.width - 1)
					{
						if (!strcmp(filter, "EDGE"))
							apply_edge(*photo, copy, i, j);
						else if (!strcmp(filter, "SHARPEN"))
							apply_sharpen(*photo, copy, i, j);
						else if (!strcmp(filter, "BLUR"))
							apply_blur(*photo, copy, i, j);
						else if (!strcmp(filter, "GAUSSIAN_BLUR"))
							apply_gaussian_blur(*photo, copy, i, j);
					}
					else
					{
						copy.red[i][j] = photo->red[i][j];
						copy.green[i][j] = photo->green[i][j];
						copy.blue[i][j] = photo->blue[i][j];
					}
			free_image(photo);
			photo->size = copy.size;
			copy.max = photo->max;
			*photo = copy;
			photo->loaded = 1;
			if (!broke)
				printf("APPLY %s done\n", filter);
		}
		else
		{
			printf("Invalid filter name\n");
		}
	}
	else
	{
		printf("Invalid command\n");
	}
}