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
    char ch;
    for (int i = 0, j = 0; i < bmp_image->header.filesize; i++){
        if( i > offset && morse_txt[j]){
            Color background_color;
                fread(&background_color, (bmp_image->info_header.bits_per_pixel / 8), 1, bmp_image->file);
            if(morse_txt[j] == '1')
                fwrite(&COLOR_TO_WRITE, (bmp_image->info_header.bits_per_pixel / 8), 1, mod_file);
            else 
                fwrite(&background_color, (bmp_image->info_header.bits_per_pixel / 8), 1, mod_file);       
            j++;
            i+=3;
        }
        else{
            ch = fgetc(bmp_image->file);
            fputc(ch, mod_file);
        }
        
    }

    // for (int i = 0; i < strlen(morse_txt); i++){
    //     Color background_color;
    //     fread(&background_color, (bmp_image->info_header.bits_per_pixel / 8), 1, bmp_image->file);
    //     if(morse_txt[i] == '1')
    //         fwrite(&COLOR_TO_WRITE, (bmp_image->info_header.bits_per_pixel / 8), 1, mod_file);
    //     else 
    //         fwrite(&background_color, (bmp_image->info_header.bits_per_pixel / 8), 1, mod_file);
    // }

    // while((ch = fgetc(bmp_image->file)) != EOF)
    //     fputc(ch, mod_file);    

    fclose(mod_file);

    close_bmp(bmp_image);
    return 0;
}