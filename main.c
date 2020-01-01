//
// Created by anarmammad on 17/11/19.
//

#include <stdio.h>

#include "bmp.h"
#include "helper.h"
#include "morse.h"

char FILENAME[100] = "example.bmp", TEXT_TO_WRITE[100],  OUTPUT_FILE[100];
int IS_DATE_SET = false;


void prepare_options(int argc, char *argv[]){
    static struct option longopts[] = {
        { "text", required_argument, NULL, 't' },
        { "date", no_argument, NULL, 'd' },
        { "pos", required_argument, NULL, 'p' },
        { "o", required_argument, NULL, 'o' },
        { "color", required_argument, NULL, 'c'},
        { 0,         0,           0, 0 }
    };
    char ch;
    while ((ch = getopt_long_only(argc, argv, ":td:p:o:", longopts, NULL)) != -1) {
        switch (ch) {
            case 't':
                strcpy(TEXT_TO_WRITE, optarg);
                printf("Text: %s\n", TEXT_TO_WRITE);
                break;
            case 'd':
                IS_DATE_SET = true;
                printf("Date will be written!\n");
                break;
            case 'p':
                printf("Position: (%s)\n", optarg);
                break;
            case 'o':
                strcpy(OUTPUT_FILE, optarg);
                printf("Output file: %s\n", optarg);
                break;
            case 'c':
                // COLOR 
                printf("Color: %s\n", optarg);
                break;
            case ':':
                sprintf(ERROR_BUF, "Option '%s' has missing argument", argv[optind - 1]);
                throw_exception(ERROR_BUF, -5);
                break;
            case '?':
                if (optopt == 0) 
                    sprintf(ERROR_BUF, "Unknown option '%s'", argv[optind - 1]);
                else 
                    sprintf(ERROR_BUF, "Error parsing option '%s'", argv[optind - 1]);

                throw_exception(ERROR_BUF, -6);
                break;
        }
    }
}


int main(int argc, char *argv[]){
    prepare_options(argc, argv);

    BMP* bmp_image = open_bmp("example.bmp");

    read_first_header(bmp_image);
    printf("Image starts at: %u\n", bmp_image->image_starts_at);
    printf("File size is: %u\n", bmp_image->filesize);

    read_second_header(bmp_image);
    printf("Header size is: %u\n", bmp_image->header_size);
    printf("Image width is: %u\n", bmp_image->image_width);
    printf("Image height is: %u\n", bmp_image->image_height);
    printf("Number of color planes is: %u\n", bmp_image->n_color_planes);
    printf("Bits per pixel is: %u\n", bmp_image->bits_per_pixel);
    return 0;
}