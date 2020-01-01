#if !defined(__COLOR_H__)
#define __COLOR_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha_channel;
} Color;

extern Color BLACK;
extern Color WHITE;

Color* new_color(
    unsigned char red, 
    unsigned char green, 
    unsigned char blue, 
    unsigned char alpha_channel
);

void print_color(Color* color);

#endif // __COLOR_H__

