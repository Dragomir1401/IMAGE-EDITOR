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
	while (USELESS_NUMBER) {
		if (!strcmp(command, "LOAD")) {
			scanf("%s", filename);

			if (photo.loaded)
				free_image(&photo);
			load_command(&photo, filename);

			if (photo.loaded)
				select_all_pixels(&photo, 1, 0);
		} else if (!strcmp(command, "SELECT")) {
			char buff[LENGHTMAX];
			scanf("%s", buff);

			if (!strcmp(buff, "ALL"))
				select_all_pixels(&photo, 0, 0);
			else
				select_pixels(&photo, buff);
		} else if (!strcmp(command, "CROP")) {
			crop_image(&photo);
			select_all_pixels(&photo, 1, 1);
		} else if (!strcmp(command, "PRINT")) {
			print_image(photo);
		} else if (!strcmp(command, "APPLY") || !strcmp(command, "A")) {
			apply_filter(&photo, command);
		} else if (!strcmp(command, "ROTATE")) {
			char rotation[LENGHTMAX];
			scanf("%s", rotation);

			rotate_image(&photo, rotation);
		} else if (!strcmp(command, "SAVE")) {
			scanf("%s", filename);

			save_image(photo, filename);
		} else if (!strcmp(command, "EXIT")) {
			if (photo.loaded) {
				free_image(&photo);
				break;
			}

			printf("No image loaded\n");
			break;

		} else {
			char buff, junk[LENGHTMAX];
			buff = getchar();

			if (buff == ' ') {
				scanf("%s", junk);
				printf("Invalid command\n");
			} else {
				printf("Invalid command\n");
			}
		}
		scanf("%s", command);
	}
	return 0;
}
