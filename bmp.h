#if !defined(__BMP_H__)
#define __BMP_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helper.h"
#include "morse.h"

typedef struct __attribute__((__packed__)) {
    struct __attribute__((__packed__)) { // 14 bytes
        char signature[2];
        int filesize;
        int reserved;
        int image_starts_at;
    } header;

    struct { // 40 bytes
        /* 16 bytes */
        int header_size;
        int image_width;
        int image_height;
        short n_color_planes;
        short bits_per_pixel;
        /* 40 bytes: not important */
        int compression;
        int image_size;
        int x_pixel_per_m;
        int y_pixel_per_m;
        int colors_used;
        int important_colors;
    } info_header;

    FILE* file;

} BMP, *PBMP;

PBMP open_bmp(char* filename);
char* watermark_bmp(PBMP image_old);
void close_bmp(PBMP);

#endif // __BMP_H__