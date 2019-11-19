//
// Created by anarmammad on 17/11/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0
typedef int boolean;

unsigned int FILE_SIZE, IMAGE_STARTS_AT;

void throw_exception(char* body, short status_code){
    printf("%s\n", body);
    printf("Exitting...");
    exit(status_code);
}

void check_first_header(FILE* file){
    unsigned char first_header[14];

    fgets((char*)first_header, 14, file);

    // 2 first bytes: BMP format
    if(strncmp((char*)first_header, "BM", 2) != 0)
        throw_exception("Invalid first header: unknown format!", -2);

    // 4 next bytes: file size
    // TODO: get file size directly from linux libraries and check with the one in the header
    FILE_SIZE = first_header[2] +
            (first_header[3] << (unsigned) 8) +
            (first_header[4] << (unsigned) 16) +
            (first_header[5] << (unsigned) 24);
    if(FILE_SIZE == 0)
        throw_exception("Invalid first header: file size is wrong!", -3);

    // 4 next bytes: reserved for application. Not used.
    // 4 next bytes: the offset - byte the image starts
    IMAGE_STARTS_AT = first_header[10] +
                (first_header[11] << (unsigned) 8) +
                (first_header[12] << (unsigned) 16) +
                (first_header[13] << (unsigned) 24);
    if(IMAGE_STARTS_AT == 0 || IMAGE_STARTS_AT >= FILE_SIZE)
        throw_exception("Invalid first header: image start offset is wrong!", -4);
}

void check_second_header(FILE* file){
    /**/
}



int main(int argc, char *argv[]){
    FILE* file = fopen("../example.bmp", "rb+");
    if(file == NULL)
        throw_exception("File cannot be found!", -1);

    check_first_header(file);
    printf("%x \n", fgetc(file));
    printf("%x \n", fgetc(file));
    printf("%x \n", fgetc(file));
    printf("%x \n", fgetc(file));

    fclose(file);
    return 0;
}