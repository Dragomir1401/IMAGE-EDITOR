#pragma once
#include <stdint.h>

typedef struct size
{
	uint_fast32_t width;
	uint_fast32_t height;
} size;

typedef struct picture
{
	uint_fast8_t type;
	uint_fast8_t max;
	uint_fast8_t **bw;
	uint_fast8_t **red;
	uint_fast8_t **green;
	uint_fast8_t **blue;
	size start, stop;
	size size;
	uint_fast8_t loaded;
} picture;
