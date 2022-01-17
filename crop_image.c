#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "structures.h"
#include "headers.h"

void crop_image(picture *photo)
{
	// If we have no photo loaded
	if (!photo->loaded) {
		printf("No image loaded\n");
		return;
	}
	// Make a copy to work with
	picture copy = {};
	copy.type = photo->type;

	// Case grayscale and black & white
	if (photo->type == 2 || photo->type == 1 ||
	    photo->type == 4 || photo->type == 5) {
		// Copying the size of the selection
		copy.size.width = photo->stop.width - photo->start.width;
		copy.size.height = photo->stop.height - photo->start.height;
		// Alloc memory
		copy.bw = alloc_image(copy.size.height, copy.size.width);

		// Copy only the selection to the copy
		for (uint_fast32_t i = photo->start.height; i < photo->stop.height;
		     i++)
			for (uint_fast32_t j = photo->start.width; j < photo->stop.width;
			     j++)
				copy.bw[i - photo->start.height][j - photo->start.width] =
				photo->bw[i][j];

		// Free initial photo
		free_image(photo);
		// Getting the size and max in the new photo
		photo->size = copy.size;
		copy.max = photo->max;

		// Shallow copying back in the image
		*photo = copy;
		photo->loaded = 1;
	} else if (photo->type == 3 || photo->type == 6) {
		// Case RGB
		// Copying the size of the selection
		copy.size.width = photo->stop.width - photo->start.width;
		copy.size.height = photo->stop.height - photo->start.height;

		// Alloc memory
		copy.red = alloc_image(copy.size.height, copy.size.width);
		copy.green = alloc_image(copy.size.height, copy.size.width);
		copy.blue = alloc_image(copy.size.height, copy.size.width);

		// Copy only the selection to the copy
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
		// Free initial photo
		free_image(photo);
		// Getting the size and max in the new photo
		photo->size = copy.size;
		copy.max = photo->max;

		// Shallow copying back in the image
		*photo = copy;
		photo->loaded = 1;
	}
	printf("Image cropped\n");
}
