#if !defined(__BMP_H__)
#define __BMP_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helper.h"

typedef struct{
    FILE* file;
    unsigned filesize; // 4 bytes
    unsigned image_starts_at; // 4 bytes
    unsigned header_size; // 4 bytes
    unsigned image_width; // 4 bytes
    unsigned image_height; // 4 bytes
    unsigned short n_color_planes; // 2 bytes
    unsigned short bits_per_pixel; // 2 bytes
} BMP;

BMP* open_bmp(char* filename);

BMP* read_first_header(BMP* bmp_image);
BMP* read_second_header(BMP* bmp_image);

#endif // __BMP_H__