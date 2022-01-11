#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "structures.h"
#include "headers.h"

void crop_image(picture *photo)
{
	if (!photo->loaded) {
		printf("No image loaded\n");
		return;
	}
	picture copy = {};
	copy.type = photo->type;
	if (photo->type == 2 || photo->type == 1 ||
	    photo->type == 4 || photo->type == 5) {
		copy.size.width = photo->stop.width - photo->start.width;
		copy.size.height = photo->stop.height - photo->start.height;
		copy.bw = alloc_image(copy.size.height, copy.size.width);
		for (uint_fast32_t i = photo->start.height; i < photo->stop.height;
		     i++)
			for (uint_fast32_t j = photo->start.width; j < photo->stop.width;
			     j++)
				copy.bw[i - photo->start.height][j - photo->start.width] =
				photo->bw[i][j];
		free_image(photo);
		photo->size = copy.size;
		copy.max = photo->max;
		*photo = copy;
		photo->loaded = 1;
	} else if (photo->type == 3 || photo->type == 6) {
		copy.size.width = photo->stop.width - photo->start.width;
		copy.size.height = photo->stop.height - photo->start.height;
		copy.red = alloc_image(copy.size.height, copy.size.width);
		copy.green = alloc_image(copy.size.height, copy.size.width);
		copy.blue = alloc_image(copy.size.height, copy.size.width);
		for (uint_fast32_t i = photo->start.height; i < photo->stop.height;
		     i++)
			for (uint_fast32_t j = photo->start.width; j < photo->stop.width;
			     j++) {
				copy.red[i - photo->start.height][j - photo->start.width] =
				photo->red[i][j];
				copy.green[i - photo->start.height][j - photo->start.width] =
				photo->green[i][j];
				copy.blue[i - photo->start.height][j - photo->start.width] =
				photo->blue[i][j];
			}
		free_image(photo);
		photo->size = copy.size;
		copy.max = photo->max;
		*photo = copy;
		photo->loaded = 1;
	}
	printf("Image cropped\n");
}
