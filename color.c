#include "color.h"


char* color_to_rgba(Color* color){
    char* ptr = (char*) calloc(200, 1);
    sprintf(ptr, "(r: %hhu, g: %hhu, b: %hhu, a: %hhu)", color->red, color->green, color->blue, color->alpha_channel);
    return ptr;
}
