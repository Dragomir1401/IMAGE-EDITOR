#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
void swap(uint_fast32_t *pa, uint_fast32_t *pb)
{
	int temp = *pa;
	*pa = *pb;
	*pb = temp;
}
void select_pixels(picture *photo, char *buff)
{
	int x11, x22, y11, y22;
	uint_least32_t x1, x2, y1, y2;
	//CHECK VALIDITY OF INPUT.....
	x11 = atoi(buff);
	scanf("%d%d%d", &y11, &x22, &y22);
	if (!photo->loaded)
	{
		printf("No image loaded\n");
		return;
	}
	// uint_fast32_t x1, x2, y1, y2;
	// //CHECK VALIDITY OF INPUT.....
	// x1 = atoi(buff);
	// scanf("%lu%lu%lu", &y1, &x2, &y2);
	if (x11 < 0 || x22 < 0 || y11 < 0 || y22 < 0)
	{
		printf("Invalid set of coordinates\n");
		select_all_pixels(photo, 1, 0);
		return;
	}
	else
	{
		x1 = x11;
		y1 = y11;
		x2 = x22;
		y2 = y22;
	}

	if (x2 > photo->size.width || y2 > photo->size.height || x1 == x2 || y1 == y2)
	{
		printf("Invalid set of coordinates\n");
		select_all_pixels(photo, 1, 0);
		return;
	}
	if (x1 > x2)
		swap(&x1, &x2);
	if (y1 > y2)
		swap(&y1, &y2);
	photo->start.width = x1;
	photo->stop.width = x2;
	photo->start.height = y1;
	photo->stop.height = y2;
	printf("Selected %ld %ld %ld %ld\n", x1, y1, x2, y2);
}

void select_all_pixels(picture *photo, int just_loaded, int just_cropped)
{
	if (!photo->loaded && !just_cropped)
	{
		printf("No image loaded\n");
		return;
	}
	photo->start.width = 0;
	photo->stop.width = photo->size.width;
	photo->start.height = 0;
	photo->stop.height = photo->size.height;
	if (!just_loaded)
		printf("Selected ALL\n");
}