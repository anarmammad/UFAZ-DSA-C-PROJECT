#if !defined(__HELPER_H__)
#define __HELPER_H__

#define true 1
#define false 0
typedef int bool;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/wait.h>

#include "color.h"

#define ERR_FILE -1
#define ERR_FORMAT -2
#define ERR_SIZE -3
#define ERR_UNKNOWN -4

extern char FILENAME[100], TEXT_TO_WRITE[100],  OUTPUT_FILE[100], ERROR_BUFF[100], LOG_BUFF[600];

extern unsigned POSITION_TO_WRITE[2];

extern int IS_DATE_SET;

extern Color COLOR_TO_WRITE;



void throw_exception(char* body, short status_code);
void get_options(int argc, char *argv[]);
char* get_linux_date();

void print_man_page_and_exit();
void str_logger(char* str);


#endif // __HELPER_H__
