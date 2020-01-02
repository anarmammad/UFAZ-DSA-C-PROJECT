#include "bmp.h"

void close_bmp(PBMP bmpFile){
    fclose(bmpFile->file);
    //free(bmpFile);
}