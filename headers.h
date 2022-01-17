#include <stdint.h>
// Headers file for all functions
int load_command(picture * photo, char *filename);
void free_image(picture *photo);
void print_image(picture photo);
void crop_image(picture *photo);
void select_pixels(picture *photo, char *buff);
double **alloc_image(int height, int width);
void select_all_pixels(picture *photo, int just_loaded, int just_cropped);
void save_image(picture image, char *filename);
void apply_filter(picture *photo, char command[]);
void rotate_image(picture *photo, char *rotation);
