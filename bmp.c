#include "bmp.h"

BMP* open_bmp(char* filename){
    BMP* bmp_image = (BMP*) malloc(sizeof(BMP));
    bmp_image->file = fopen(filename, "rb+");
    if( ! bmp_image->file ){
        sprintf(ERROR_BUF, "File '%s' not found or cannot be read!", filename);
        throw_exception(ERROR_BUF, -5);
    }

    return bmp_image;
}

BMP* read_first_header(BMP* bmp_image){
    unsigned char first_header[15]; // extra byte allocated for \0 at the end 
    fgets((char*) first_header, 15, bmp_image->file);

    // 2 first bytes: BMP format
    if(strncmp((char*)first_header, "BM", 2) != 0)
        throw_exception("Invalid first header: unknown format!", -2);

    // 4 next bytes: file size
    bmp_image->filesize = first_header[2] +
            (first_header[3] << (unsigned) 8) +
            (first_header[4] << (unsigned) 16) +
            (first_header[5] << (unsigned) 24);
    if(bmp_image->filesize == 0)
        throw_exception("Invalid first header: file size is wrong!", -3);

    // 4 next bytes: reserved for application. Not used

    // 4 next bytes: the offset - byte the image starts
    bmp_image->image_starts_at = first_header[10] +
                    (first_header[11] << (unsigned) 8) +
                    (first_header[12] << (unsigned) 16) +
                    (first_header[13] << (unsigned) 24);
    if(bmp_image->image_starts_at == 0 || bmp_image->image_starts_at >= bmp_image->filesize)
        throw_exception("Invalid first header: image start offset is wrong!", -4);

    return bmp_image;
}

BMP* read_second_header(BMP* bmp_image){
    unsigned char second_header[57]; // extra byte allocated for \0 at the end 
    fgets((char*)second_header, 57, bmp_image->file);

    // 4 Bytes in little endian : size of the header
    bmp_image->header_size = second_header[0] +
                (second_header[1] << (unsigned) 8) +
                (second_header[2] << (unsigned) 16) +
                (second_header[3] << (unsigned) 24);

    // 4 Bytes in little endian for image width
    bmp_image->image_width = second_header[4] +
                (second_header[5] << (unsigned) 8) +
                (second_header[6] << (unsigned) 16) +
                (second_header[7] << (unsigned) 24);

    // 4 Bytes in little endian for image height
    bmp_image->image_height = second_header[8] +
                (second_header[9] << (unsigned) 8) +
                (second_header[10] << (unsigned) 16) +
                (second_header[11] << (unsigned) 24);

    // 2 Bytes : number of color planes
    bmp_image->n_color_planes = second_header[12] + (second_header[13] << 8);

    // 2 Bytes : number of bits per pixels
    bmp_image->bits_per_pixel = second_header[14] + (second_header[15] << 8);
    
    // 24 remaining Bytes : not important
            
    return bmp_image;
}