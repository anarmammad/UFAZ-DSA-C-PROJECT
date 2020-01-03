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

    FILE* mod_file = OUTPUT_FILE[0] != '\0' ? fopen(OUTPUT_FILE, "wb+"):stdout;
    char* morse_txt = str_to_morse(TEXT_TO_WRITE);
    rewind(image_old->file);
   
    char* data = (char*) calloc(image_old->header.filesize, 1);

    fread(data, offset, 1, image_old->file);
    fwrite(data, offset, 1, mod_file);

    fread(data, strlen(morse_txt) * (image_old->info_header.bits_per_pixel / 8), 1, image_old->file);
    for (int i = 0; morse_txt[i]; i++){
        if(morse_txt[i] == '1'){
            fwrite(image_old->info_header.bits_per_pixel == 32 ? (char*)&COLOR_TO_WRITE : (((char*) &COLOR_TO_WRITE)+1) , image_old->info_header.bits_per_pixel / 8, 1, mod_file);
        }
        else{
            fwrite(&data[i * image_old->info_header.bits_per_pixel / 8], image_old->info_header.bits_per_pixel / 8, 1, mod_file);
        }
    }
    
    
    fread(data, image_old->header.filesize - strlen(morse_txt) * (image_old->info_header.bits_per_pixel / 8) - offset, 1, image_old->file);
    fwrite(data, image_old->header.filesize - strlen(morse_txt) * (image_old->info_header.bits_per_pixel / 8) - offset, 1, mod_file);

    fclose(mod_file);
    return morse_txt;
}

void close_bmp(PBMP bmpFile){
    fclose(bmpFile->file);
    free(bmpFile);
}