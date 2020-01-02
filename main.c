//
// Created by anarmammad on 17/11/19.
//

#include <stdio.h>

#include "bmp.h"
#include "helper.h"
#include "morse.h"
#include <stddef.h>




int main(int argc, char *argv[]){
//    get_options(argc, argv);
//
//    printf("Text to be written: %s\n", TEXT_TO_WRITE);
//    printf("%s\n", IS_DATE_SET ? "Date will be written":"Date won't be written");
//    printf("Position to put watermark: (%u, %u)\n", POSITION_TO_WRITE[0], POSITION_TO_WRITE[1]);
//    printf("Output file: %s\n", OUTPUT_FILE);
//    printf("Color to be written: "); print_color(&COLOR_TO_WRITE);
//
//
//    BMP* bmp_image = open_bmp(FILENAME);
//
//    printf("\n\n**********\n\n");
//    read_first_header(bmp_image);
//    printf("Image starts at: %u\n", bmp_image->image_starts_at);
//    printf("File size is: %u\n", bmp_image->filesize);
//
//    read_second_header(bmp_image);
//    printf("Header size is: %u\n", bmp_image->header_size);
//    printf("Image width is: %u\n", bmp_image->image_width);
//    printf("Image height is: %u\n", bmp_image->image_height);
//    printf("Number of color planes is: %u\n", bmp_image->n_color_planes);
//    printf("Bits per pixel is: %u\n", bmp_image->bits_per_pixel);

    PBMP file = open_bmp("/home/harry/example.bmp");

    printf("BMP:\n"
           "\tFileSize: %d\n"
           "\tDataOffset: %d\n"
           "\tSize: %d\n"
           "\tWidth: %d\n"
           "\tHeight: %d\n",
           file->Header.FileSize,
           file->Header.DataOffset,
           file->InfoHeader.Size,
           file->InfoHeader.Width,
           file->InfoHeader.Height);
    return 0;
}