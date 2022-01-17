#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

void free_image(picture *photo)
{
	// Functions to free an image matrices based on the type
	// with one matrix
	if (photo->type == 2 || photo->type == 1 || photo->type == 4 ||
	    photo->type == 5) {
		for (uint_fast32_t i = 0; i < photo->size.height; i++)
			free(photo->bw[i]);

		free(photo->bw);
	} else if (photo->type == 3 || photo->type == 6) {
		// For 3 matrices
		for (uint_fast32_t i = 0; i < photo->size.height; i++) {
			free(photo->red[i]);
			free(photo->green[i]);
			free(photo->blue[i]);
		}
		free(photo->red);
		free(photo->green);
		free(photo->blue);
	}
}
