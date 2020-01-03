#if !defined(__PIXEL_H__)
#define __PIXEL_H__

#include <stdio.h>
#include "color.h"
#include "bmp.h"

typedef struct {
    unsigned x;
    unsigned y;
    Color* color;
} Pixel;

Pixel* new_pixel(unsigned x, unsigned y, Color* color);

void print_pixel(Pixel* pixel);

unsigned get_offset(PBMP bmp_image, unsigned x, unsigned y);

#endif // __PIXEL_H__
