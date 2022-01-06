#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
void print_image(picture photo)
{
    if (photo.type == 2 || photo.type == 1)
    {
        for (uint_fast32_t i = 0; i < photo.size.height; i++)
        {
            for (uint_fast32_t j = 0; j < photo.size.width; j++)
                printf("%d ", photo.bw[i][j]);

            printf("\n");
        }
    }
    else if (photo.type == 3)
    {
        for (uint_fast32_t i = 0; i < photo.size.height; i++)
        {
            for (uint_fast32_t j = 0; j < photo.size.width; j++)
                printf("%d %d %d  ", photo.red[i][j], photo.green[i][j], photo.blue[i][j]);

            printf("\n");
        }
    }
}
void free_image(picture *photo)
{

    // if (!photo->loaded)
    // {
    //     printf("No image loaded\n");
    //     return;
    // }

    if (photo->type == 2 || photo->type == 1 || photo->type == 4 || photo->type == 5)
    {
        for (uint_fast32_t i = 0; i < photo->size.height; i++)
            free(photo->bw[i]);

        free(photo->bw);
    }
    else if (photo->type == 3 || photo->type == 6)
    {
        for (uint_fast32_t i = 0; i < photo->size.height; i++)
        {
            free(photo->red[i]);
            free(photo->green[i]);
            free(photo->blue[i]);
        }
        free(photo->red);
        free(photo->green);
        free(photo->blue);
    }
}
