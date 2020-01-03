#include "pixel.h"

Pixel* new_pixel(unsigned x, unsigned y, Color* color){
    Pixel* new_pixel = (Pixel*) malloc(sizeof(Pixel));
    new_pixel->x = x;
    new_pixel->y = y;
    new_pixel->color = color;

    return new_pixel;
}

void print_pixel(Pixel* pixel){
    printf("Coordinate: (x: %u, y: %u)\t Color: ", pixel->x, pixel->y);
    print_color(pixel->color);
}

unsigned get_offset(BMP* bmp_image, unsigned x, unsigned y){
    if(x >= bmp_image->info_header.image_width || y >= bmp_image->info_header.image_height)
        throw_exception("Coordiate out of image", ERR_UNKNOWN);
    
    unsigned pixel_coordinate = (bmp_image->info_header.image_height - y - 1) * bmp_image->info_header.image_width + x ;
    return pixel_coordinate * (bmp_image->info_header.bits_per_pixel / 8) + bmp_image->header.image_starts_at;
}