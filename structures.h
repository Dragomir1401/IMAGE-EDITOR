#pragma once
#include <stdint.h>

typedef struct size {
	uint_fast32_t width;
	uint_fast32_t height;
} dimensions;

typedef struct picture {
	uint_fast8_t type;
	uint_fast8_t max;
	double **bw;
	double **red;
	double **green;
	double **blue;
	dimensions start, stop;
	dimensions size;
	uint_fast8_t loaded;
} picture;
