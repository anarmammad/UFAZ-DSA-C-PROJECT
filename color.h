#if !defined(__COLOR_H__)
#define __COLOR_H__

#include <stdio.h>
#include <stdlib.h>

#define BLACK { 0, 0, 0, 0 }
#define WHITE { 255, 255, 255, 0 }

typedef struct {
    unsigned char alpha_channel;
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} Color;

char* color_to_rgba(Color* color);


#endif // __COLOR_H__

