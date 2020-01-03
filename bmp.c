#include "bmp.h"

PBMP open_bmp(char* filename){
    PBMP image = memset((PBMP)malloc(sizeof(BMP)), 0, sizeof(BMP));

    image->file = fopen(filename, "rb+");

    if( ! image->file ){
        sprintf(ERROR_BUF, "File '%s' not found or cannot be read!", filename);
        throw_exception(ERROR_BUF, -5);
    }

    if(!fgets((char*)image, sizeof(BMP) - sizeof(image->file), image->file)){
        throw_exception("Fgets Error\n", ERR_UNKNOWN);
    }

    if(strncmp(image->header.signature, "BM", 2))
        throw_exception("Format mismatch!\n", ERR_FORMAT);

    if(!image->header.filesize)
        throw_exception("File Size is not valid!\n", ERR_FILE);

    if(!image->header.image_starts_at || image->header.image_starts_at >= image->header.filesize)
        throw_exception("Data Offset mismatch\n", ERR_FILE);

    return image;
}

void close_bmp(PBMP bmpFile){
    fclose(bmpFile->file);
    //free(bmpFile);
}