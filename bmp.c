#include "bmp.h"
#include "pixel.h"

PBMP open_bmp(char* filename){
    PBMP image = memset((PBMP)malloc(sizeof(BMP)), 0, sizeof(BMP));

    image->file = fopen(filename, "rb+");

    if( ! image->file ){
        sprintf(ERROR_BUFF, "File '%s' not found or cannot be read!", filename);
        throw_exception(ERROR_BUFF, -5);
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

/* function that watermarks the bmp image and returns the morse code */
char* watermark_bmp(PBMP image_old){
    unsigned offset = get_offset(image_old, POSITION_TO_WRITE[0], POSITION_TO_WRITE[1]); 
    int bytes_per_pixel = image_old->info_header.bits_per_pixel / 8;

    char* morse_txt = str_to_morse(TEXT_TO_WRITE);
    rewind(image_old->file);
   
    char* data = (char*) calloc(image_old->header.filesize, 1);
    char* mod_data = (char*) calloc(image_old->header.filesize, 2);

    fread(data, offset, 1, image_old->file);
    // fwrite(data, offset, 1, mod_file);
    memcpy(mod_data, data, offset);

    unsigned x = POSITION_TO_WRITE[0];
    fread(data, strlen(morse_txt) * (bytes_per_pixel), 1, image_old->file);
    for (int i = 0; morse_txt[i]; i++, x++){
        if(morse_txt[i] == '1' && x < image_old->info_header.image_width ){
            // fwrite(image_old->info_header.bits_per_pixel == 32 ? (char*)&COLOR_TO_WRITE : (((char*) &COLOR_TO_WRITE)+1) , bytes_per_pixel, 1, mod_file);
            memcpy(mod_data + offset + i*bytes_per_pixel, image_old->info_header.bits_per_pixel == 32 ? (char*)&COLOR_TO_WRITE : (((char*) &COLOR_TO_WRITE)+1), bytes_per_pixel);
        }
        else{
            // fwrite(&data[i * bytes_per_pixel], bytes_per_pixel, 1, mod_file);
            memcpy(mod_data + offset + i * bytes_per_pixel, &data[i * bytes_per_pixel], bytes_per_pixel);
            if(x >= image_old->info_header.image_width && morse_txt[i] == '1'){\
                memcpy(mod_data + offset + i * bytes_per_pixel - image_old->info_header.image_width * bytes_per_pixel * (x / image_old->info_header.image_width * 2), image_old->info_header.bits_per_pixel == 32 ? (char*) &COLOR_TO_WRITE : (((char*) &COLOR_TO_WRITE) + 1), bytes_per_pixel);
        }
    }
    
    
    fread(data, image_old->header.filesize - strlen(morse_txt) * (bytes_per_pixel) - offset, 1, image_old->file);
    // fwrite(data, image_old->header.filesize - strlen(morse_txt) * (bytes_per_pixel) - offset, 1, mod_file);
    memcpy(mod_data + offset + strlen(morse_txt)*bytes_per_pixel, data, image_old->header.filesize - strlen(morse_txt) * (bytes_per_pixel) - offset);

    FILE* mod_file = OUTPUT_FILE[0] != '\0' ? fopen(OUTPUT_FILE, "wb+"):stdout;
    fwrite(mod_data, image_old->header.filesize, 1, mod_file);
    fclose(mod_file);
    return morse_txt;
}

void close_bmp(PBMP bmpFile){
    fclose(bmpFile->file);
    free(bmpFile);
}