#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#define COMM_MAX 10
void swap(uint_fast32_t *pa, uint_fast32_t *pb)
{
	//function to swap two values
	int temp = *pa;
	*pa = *pb;
	*pb = temp;
}

int string_is_digit(char tmp[COMM_MAX])
{
	//function that verifies if a string contains only digits and '-' or not
	unsigned long j = 0;
	while (j < strlen(tmp)) {
		if ((tmp[j] > 57 || tmp[j] < 48) && tmp[j] != '-')
			return 0;
		j++;
	}
	return 1;
}

void select_pixels(picture *photo, char *buff)
{
	char x222[COMM_MAX], y111[COMM_MAX], y222[COMM_MAX], buff1;
	int x11, x22, y11, y22; uint_fast32_t x1, x2, y1, y2;
	// we check if we have all 4 coordinates or not
	// we use strings to ease input	
	buff1 = getchar();
	if (buff1 == ' ') {
		scanf("%s", y111);
	} else {
		printf("Invalid command\n");
		return;
	}
	buff1 = getchar();
	if (buff1 == ' ') {
		scanf("%s", x222);
	} else {
		printf("Invalid command\n");
		return;
	}
	buff1 = getchar();
	if (buff1 == ' ') {
		scanf("%s", y222);
	} else {
		printf("Invalid command\n");
		return;
	}
	// if there is no photo loaded
	if (!photo->loaded) {
		printf("No image loaded\n");
		return;
	}
	if (!string_is_digit(y111) || !string_is_digit(x222) ||
		!string_is_digit(y222)) {
		printf("Invalid command\n");
		return;
	}
	if (strstr(buff, "-")) { //if we have negative coordinates of any sort
		printf("Invalid set of coordinates\n");
		return;
	}
	x11 = atoi(buff); // transform string coordinate in int
	if (strstr(y111, "-")) {
		printf("Invalid set of coordinates\n");
		return;
	}
	y11 = atoi(y111);
	if (strstr(x222, "-")) {
		printf("Invalid set of coordinates\n");
		return;
	}
	x22 = atoi(x222);
	if (strstr(y222, "-")) {
		printf("Invalid set of coordinates\n");
		return;
		}
	y22 = atoi(y222);
	if (!photo->loaded) {
		printf("No image loaded\n");
		return;
	}
	// put the coordinates in place varibles we will use next
	x1 = x11;
	y1 = y11;
	x2 = x22;
	y2 = y22;

	if (x1 > x2)
		swap(&x1, &x2);
	if (y1 > y2)
		swap(&y1, &y2);
	if (x2 > photo->size.width || y2 > photo->size.height || x1 == x2 ||
		y1 == y2) {
		printf("Invalid set of coordinates\n");
		return;
	}
	// Put coordinates in structure
	photo->start.width = x1;
	photo->stop.width = x2;
	photo->start.height = y1;
	photo->stop.height = y2;
	printf("Selected %ld %ld %ld %ld\n", x1, y1, x2, y2);
}

void select_all_pixels(picture *photo, int just_loaded, int just_cropped)
{
	// If there is no photo loaded or is not recently cropped beacause then
	// we already have selected all pixels
	if (!photo->loaded && !just_cropped) {
		printf("No image loaded\n");
		return;
	}
	// Select the entire photo
	photo->start.width = 0;
	photo->stop.width = photo->size.width;
	photo->start.height = 0;
	photo->stop.height = photo->size.height;
	// We print this message if we selected all manually not automatically after
	// loading a photo
	if (!just_loaded)
		printf("Selected ALL\n");
}
