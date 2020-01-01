#if !defined(__COLOR_H__)
#define __COLOR_H__

#include <stdio.h>
#include <stdlib.h>

#define BLACK { 0, 0, 0, 0 }
#define WHITE { 255, 255, 255, 0 }

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha_channel;
} Color;

Color* new_color(
    unsigned char red, 
    unsigned char green, 
    unsigned char blue, 
    unsigned char alpha_channel
);

void print_color(Color* color);

#endif // __COLOR_H__

