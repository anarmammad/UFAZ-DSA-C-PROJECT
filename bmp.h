#if !defined(__BMP_H__)
#define __BMP_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helper.h"

typedef struct __attribute__((__packed__)) {
    struct __attribute__((__packed__)) {
        char Signature[2];
        int FileSize;
        int reserved;
        int DataOffset;
    } Header;

    struct {
        int Size;
        int Width;
        int Height;
        short Planes;
        short Bits;
        int Compression;
        int ImageSize;
        int XpixelsPerM;
        int YpixelsPerM;
        int ColorsUsed;
        int ImportantColors;
    } InfoHeader;

    FILE* file;

} BMP, *PBMP;

PBMP open_bmp(char* filename);
void close_bmp(PBMP);

#endif // __BMP_H__