#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
void select_pixels(picture *photo)
{
    if (!photo->loaded)
    {
        printf("No image loaded\n");
        return;
    }
    uint_fast32_t x1, x2, y1, y2;
    //CHECK VALIDITY OF INPUT.....
    scanf("%lu%lu%lu%lu", &x1, &y1, &x2, &y2);
    if (x1 > x2 || y1 > y2 || x2 > photo->size.width || y2 > photo->size.height)
    {
        printf("Invalid coordinates\n");
        return;
    }
    photo->start.width = x1;
    photo->stop.width = x2;
    photo->start.height = y1;
    photo->stop.height = y2;
    printf("Selected %ld %ld %ld %ld\n", x1, y1, x2, y2);
}

void select_all_pixels(picture *photo)
{
    if (!photo->loaded)
    {
        printf("No image loaded\n");
        return;
    }
    photo->start.width = 0;
    photo->stop.width = photo->size.width;
    photo->start.height = 0;
    photo->stop.height = photo->size.height;
    printf("Selected ALL\n");
}