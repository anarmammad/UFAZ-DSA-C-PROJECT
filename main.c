//
// Created by anarmammad on 17/11/19.
//

#include <stdio.h>

#include "bmp.h"
#include "helper.h"
#include "pixel.h"


int main(int argc, char *argv[]){
    get_options(argc, argv);
    /* logging */
    str_logger(get_linux_date());
    PBMP bmp_image = open_bmp(FILENAME);
    char* morse_txt = watermark_bmp(bmp_image);


    sprintf(LOG_BUFF, "OPTIONS:\n"
        "\tFile name: %s\n"
        "\t%s\n"
        "\tFull text to be written: %s\n"
        "\tPosition to put watermark: (%u, %u)\n"
        "\tOutput file: %s\n"
        "\tColor to be written: %s\n",
        FILENAME,
        IS_DATE_SET ? "Date will be written!":"Date won't be written!",
        TEXT_TO_WRITE,
        POSITION_TO_WRITE[0], POSITION_TO_WRITE[1],
        OUTPUT_FILE,
        color_to_rgba(&COLOR_TO_WRITE));

    str_logger(LOG_BUFF); 


    sprintf(LOG_BUFF, "BMP:\n"
           "\tSize of the file: %d bytes\n"
           "\tImage offset: %d bytes\n"
           "\tSize of the DIB header: %d bytes\n"
           "\tImage Width: %d pixels\n"
           "\tImage Height: %d pixels\n"
           "\tNumber of color planes: %d\n"
           "\tBits per pixel: %d\n",
           bmp_image->header.filesize,
           bmp_image->header.image_starts_at,
           bmp_image->info_header.header_size,
           bmp_image->info_header.image_width,
           bmp_image->info_header.image_height,
           bmp_image->info_header.n_color_planes,
           bmp_image->info_header.bits_per_pixel);

    str_logger(LOG_BUFF); 


    sprintf(LOG_BUFF, "WATERMARK:\n"
        "\tPosition offset: %u bytes\n"
        "\tLength of morse encoded text: %lu pixels\n",
        get_offset(bmp_image, POSITION_TO_WRITE[0], POSITION_TO_WRITE[1]),
        strlen(morse_txt));        
    str_logger(LOG_BUFF);

    str_logger("******************************************\n");

    close_bmp(bmp_image);
    return 0;
}