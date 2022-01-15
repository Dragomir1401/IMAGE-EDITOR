#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include <math.h>
#define LENGHTMAX 100
void save_bw(picture photo, char *filename, char type)
{
	// Open and check if opened correctly the file to write in
	FILE *file = fopen(filename, "w");
	if (!file) {
		printf("Failed to load %s\n", filename);
		return;
	}
	// Write the type correct after the decrease done
	if (type == 'a')
		fprintf(file, "P%d\n", photo.type);
	else
		fprintf(file, "P%d\n", photo.type + 3);
	// Write size of the picture
	fprintf(file, "%ld %ld\n", photo.size.width, photo.size.height);
	if (photo.type == 2)
		fprintf(file, "%d\n", photo.max);

	for (uint_fast32_t i = 0; i < photo.size.height; i++) {
		for (uint_fast32_t j = 0; j < photo.size.width; j++)
			if (type == 'a') {
				// We cast the pixel in a variable to unsigned int after using
				// round in order to handle the pixels modified by filters
				uint_fast8_t tmp = (uint_fast8_t)round(photo.bw[i][j]);
				fprintf(file, "%hhu ", tmp);
			} else {
				// Same method but writting in binary output
				uint_fast8_t tmp = (uint_fast8_t)round(photo.bw[i][j]);
				fwrite(&tmp, sizeof(uint_fast8_t), 1, file);
			}
		// We put '\n' after lines of pixel values if we have ascii type
		if (type == 'a')
			fprintf(file, "%s", "\n");
	}

	printf("Saved %s\n", filename);
	// Close the file
	fclose(file);
}

void save_rgb(picture photo, char *filename, char type)
{
	// Open and check if opened correctly the file to write in
	FILE *file = fopen(filename, "w");
	if (!file) {
		printf("Failed to load %s\n", filename);
		return;
	}

	// Write the type correct after the decrease done
	if (type == 'a')
		fprintf(file, "P%d\n", photo.type);
	else
		fprintf(file, "P%d\n", photo.type + 3);
	// Write size of the picture
	fprintf(file, "%ld %ld\n", photo.size.width, photo.size.height);
	fprintf(file, "%d\n", photo.max);

	for (uint_fast32_t i = 0; i < photo.size.height; i++) {
		for (uint_fast32_t j = 0; j < photo.size.width; j++)
			if (type == 'a') {
				// We cast the pixel in a variable to unsigned int after using
				// round in order to handle the pixels modified by filters
				uint_fast8_t tmp = (uint_fast8_t)round(photo.red[i][j]);
				fprintf(file, "%hhu ", tmp);

				tmp = (uint_fast8_t)round(photo.green[i][j]);
				fprintf(file, "%hhu ", tmp);

				tmp = (uint_fast8_t)round(photo.blue[i][j]);
				fprintf(file, "%hhu ", tmp);
			} else {
				// Same method but writting in binary output
				uint_fast8_t tmp = (uint_fast8_t)round(photo.red[i][j]);
				fwrite(&tmp, sizeof(uint_fast8_t), 1, file);

				tmp = (uint_fast8_t)round(photo.green[i][j]);
				fwrite(&tmp, sizeof(uint_fast8_t), 1, file);

				tmp = (uint_fast8_t)round(photo.blue[i][j]);
				fwrite(&tmp, sizeof(uint_fast8_t), 1, file);
			}
		// We put '\n' after lines of pixel values if we have ascii type
		if (type == 'a')
			fprintf(file, "%s", "\n");
	}

	printf("Saved %s\n", filename);
	// Close the file
	fclose(file);
}

void save_image(picture photo, char *filename)
{
	char buff;
	buff = getchar();
	// We verify if we get something as input after LOAD name.etc
	if (buff == ' ') {
		char buff1;
		buff1 = fgetc(stdin);
		// If we get ascii we will have 'a' as first letter
		if (buff1 != 'a') {
			// If we dont get 'a' as first character it means we got to the next line
			ungetc(buff1, stdin);
			// We put back the character to stdin if we pass to the next line
			if (!photo.loaded) {
				printf("No image loaded\n");
				return;
			}
			// We reduce type to the range [1, 3] to save binary with reusable functions
			if (photo.type == 4 || photo.type == 5 || photo.type == 6)
				photo.type -= 3;

			if (photo.type == 2 || photo.type == 1)
				save_bw(photo, filename, buff);
			if (photo.type == 3)
				save_rgb(photo, filename, buff);
		} else {
			// Read the rest of the word ascii
			char rest[LENGHTMAX];
			scanf("%s", rest);

			if (!photo.loaded) {
				printf("No image loaded\n");
				return;
			}
			// We reduce type to the range [1, 3] to save binary with reusable functions
			if (photo.type == 4 || photo.type == 5 || photo.type == 6)
				photo.type -= 3;

			if (photo.type == 2 || photo.type == 1)
				save_bw(photo, filename, 'a');
			if (photo.type == 3)
				save_rgb(photo, filename, 'a');
		}
	} else if (buff == '\n') {
		// If we get LOAD ex.etc and nothing more we save it binary
		if (!photo.loaded) {
			printf("No image loaded\n");
			return;
		}
		// We reduce type to the range [1, 3] to save binary with reusable functions
		if (photo.type == 4 || photo.type == 5 || photo.type == 6)
			photo.type -= 3;

		if (photo.type == 2 || photo.type == 1)
			save_bw(photo, filename, buff);
		if (photo.type == 3)
			save_rgb(photo, filename, buff);
	}
}
