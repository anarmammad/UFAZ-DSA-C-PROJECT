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

    // 2 first bytes: BMP format
    unsigned char BM[2];
    fread(BM, 2, 1, bmp_image->file);
    if(strncmp((char*)BM, "BM", 2) != 0)
        throw_exception("Invalid first header: unknown format!", -2);

    // 4 next bytes: file size
    fread(&bmp_image->filesize, 4, 1, bmp_image->file);
    if(bmp_image->filesize == 0)
        throw_exception("Invalid first header: file size is wrong!", -3);

    // 4 next bytes: reserved for application. Not used
    int junk;
    fread(&junk, 4, 1, bmp_image->file);

    // 4 next bytes: the offset - byte the image starts
    fread(&bmp_image->image_starts_at, 4, 1, bmp_image->file);
    if(bmp_image->image_starts_at == 0 || bmp_image->image_starts_at >= bmp_image->filesize)
        throw_exception("Invalid first header: image start offset is wrong!", -4);

    return bmp_image;
}

BMP* read_second_header(BMP* bmp_image){
    
    // 4 Bytes in little endian : size of the header starting counting from this point
    fread(&bmp_image->header_size, 4, 1, bmp_image->file);

    // 4 Bytes in little endian for image width
    fread(&bmp_image->image_width, 4, 1, bmp_image->file);

    // 4 Bytes in little endian for image height
    fread(&bmp_image->image_height, 4, 1, bmp_image->file);

    // 2 Bytes : number of color planes
    fread(&bmp_image->n_color_planes, 2, 1, bmp_image->file);

    // 2 Bytes : number of bits per pixels
    fread(&bmp_image->bits_per_pixel, 2, 1, bmp_image->file);
    
    // remaining Bytes : not important ( size can be different )
    char junk[bmp_image->header_size - 16];
    fread(&junk, bmp_image->header_size - 16, 1, bmp_image->file);

    return bmp_image;
}