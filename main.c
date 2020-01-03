//
// Created by anarmammad on 17/11/19.
//

#include <stdio.h>
#include <stddef.h>

#include "bmp.h"
#include "helper.h"
#include "morse.h"
#include "pixel.h"




int main(int argc, char *argv[]){
    get_options(argc, argv);

    printf("Text to be written: %s\n", TEXT_TO_WRITE);
    printf("%s\n", IS_DATE_SET ? "Date will be written":"Date won't be written");
    printf("Position to put watermark: (%u, %u)\n", POSITION_TO_WRITE[0], POSITION_TO_WRITE[1]);
    printf("Output file: %s\n", OUTPUT_FILE);
    printf("Color to be written: "); print_color(&COLOR_TO_WRITE);

    printf("\n\n**********\n\n");

    PBMP bmp_image = open_bmp(FILENAME);
    printf("BMP:\n"
           "\tFileSize: %d\n"
           "\tImage starts at: %d\n"
           "\tSize: %d\n"
           "\tImage Width: %d\n"
           "\tImage Height: %d\n"
           "\t# Color planes: %d\n"
           "\tBits per pixel: %d\n",
           bmp_image->header.filesize,
           bmp_image->header.image_starts_at,
           bmp_image->info_header.header_size,
           bmp_image->info_header.image_width,
           bmp_image->info_header.image_height,
           bmp_image->info_header.n_color_planes,
           bmp_image->info_header.bits_per_pixel);


    printf("\n\n**********\n\n");


    /* DRAFT */

    unsigned offset = get_offset(bmp_image, POSITION_TO_WRITE[0], POSITION_TO_WRITE[1]); 

    FILE* mod_file = fopen(OUTPUT_FILE, "wb+");
    char* morse_txt = str_to_morse(TEXT_TO_WRITE);
    rewind(bmp_image->file);
   
    char* data = (char*) malloc(bmp_image->header.filesize);

    fread(data, offset, 1, bmp_image->file);
    fwrite(data, offset, 1, mod_file);

    fread(data, strlen(morse_txt) * (bmp_image->info_header.bits_per_pixel / 8), 1, bmp_image->file);
    for (int i = 0; morse_txt[i]; i++){
        if(morse_txt[i] == '1'){
            fwrite(bmp_image->info_header.bits_per_pixel == 32 ? (char*)&COLOR_TO_WRITE:(((char*) &COLOR_TO_WRITE)+1) , bmp_image->info_header.bits_per_pixel / 8, 1, mod_file);
        }
        else{
            fwrite(&data[i * bmp_image->info_header.bits_per_pixel / 8], bmp_image->info_header.bits_per_pixel / 8, 1, mod_file);
        }
    }
    
    
    fread(data, bmp_image->header.filesize - strlen(morse_txt) * (bmp_image->info_header.bits_per_pixel / 8) - offset, 1, bmp_image->file);
    fwrite(data, bmp_image->header.filesize - strlen(morse_txt) * (bmp_image->info_header.bits_per_pixel / 8) - offset, 1, mod_file);

    fclose(mod_file);

    close_bmp(bmp_image);
    return 0;
}