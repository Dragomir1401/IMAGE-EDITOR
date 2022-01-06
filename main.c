#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "structures.h"
#include "headers.h"
#define LENGHTMAX 100
#define COMMANDMAX 10
#define USELESS_NUMBER 45
int main(void)
{
    char filename[LENGHTMAX], command[COMMANDMAX];
    picture photo = {};
    photo.loaded = 0;
    scanf("%s", command);
    while (USELESS_NUMBER)
    {
        if (!strcmp(command, "LOAD"))
        {
            scanf("%s", filename);
            free_image(&photo);
            load_command(&photo, filename);
            if (photo.loaded)
                select_all_pixels(&photo);
        }
        else if (!strcmp(command, "SELECT"))
        {
            select_pixels(&photo);
        }
        else if (!strcmp(command, "SELECT ALL"))
        {
            select_all_pixels(&photo);
        }
        else if (!strcmp(command, "CROP"))
        {
            crop_image(&photo);
        }
        else if (!strcmp(command, "PRINT"))
        {
            print_image(photo);
        }
        else if (!strcmp(command, "APPLY"))
        {
            char filter[LENGHTMAX];
            scanf("%s", filter);
            apply_filter(&photo, filter);
        }
        else if (!strcmp(command, "ROTATE"))
        {
            char rotation[LENGHTMAX];
            scanf("%s", rotation);
            rotate_image(&photo, rotation);
        }
        else if (!strcmp(command, "SAVE"))
        {
            scanf("%s", filename);
            save_image(photo, filename);
        }
        else if (!strcmp(command, "EXIT"))
        {
            if (photo.loaded)
            {
                free_image(&photo);
                break;
            }
            else
                printf("No image loaded.\n");
        }
        else
            printf("Invalid command\n");
        scanf("%s", command);
    }
    return 0;
}