#include <stdint.h>
int load_command(picture *photo, char *filename);
void free_image(picture *photo);
void print_image(picture photo);
void crop_image(picture *photo);
void select_pixels(picture *photo);
uint_fast8_t **alloc_image(int height, int width);
void select_all_pixels(picture *photo);
void save_image(picture image, char *filename);
void apply_filter(picture *photo, char *filter);
void rotate_image(picture *photo, char *rotation);