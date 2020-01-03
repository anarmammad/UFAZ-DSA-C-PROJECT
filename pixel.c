#include "pixel.h"

Pixel* new_pixel(unsigned x, unsigned y, Color* color){
    Pixel* new_pixel = (Pixel*) calloc(sizeof(Pixel), 1);
    new_pixel->x = x;
    new_pixel->y = y;
    new_pixel->color = color;

    return new_pixel;
}

char* pixel_to_string(Pixel* pixel){
    char* ptr;
    sprintf(ptr, "Coordinate: (x: %u, y: %u)\t Color: %s\n", pixel->x, pixel->y, color_to_rgba(pixel->color));
    return ptr;
}

unsigned get_offset(BMP* bmp_image, unsigned x, unsigned y){
    if(x >= bmp_image->info_header.image_width || y >= bmp_image->info_header.image_height)
        throw_exception("Coordiate out of image", ERR_UNKNOWN);
    
    unsigned pixel_coordinate = (bmp_image->info_header.image_height - y - 1) * bmp_image->info_header.image_width + x ;
    return pixel_coordinate * (bmp_image->info_header.bits_per_pixel / 8) + bmp_image->header.image_starts_at;
}