#include "color.h"

Color BLACK = {0, 0, 0, 0};
Color WHITE = {255, 255, 255, 0};

Color* new_color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha_channel){
    Color* new_color = (Color*) malloc(sizeof(Color));
    new_color->red = red;
    new_color->green = green;
    new_color->blue = blue;
    new_color->alpha_channel = alpha_channel;

    return new_color;
}

void print_color(Color* color){
    printf("(r: %hhu, g: %hhu, b: %hhu, a: %hhu)\n", color->red, color->green, color->blue, color->alpha_channel);
}
