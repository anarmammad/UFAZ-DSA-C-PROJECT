#if !defined(__HELPER_H__)
#define __HELPER_H__

#define true 1
#define false 0
typedef int bool;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "color.h"
#include "pixel.h"

extern char FILENAME[100], TEXT_TO_WRITE[100],  OUTPUT_FILE[100], ERROR_BUF[100];

extern unsigned POSITION_TO_WRITE[2];

extern int IS_DATE_SET;

extern Color COLOR_TO_WRITE;



void throw_exception(char* body, short status_code);
void get_options(int argc, char *argv[]);


#endif // __HELPER_H__
