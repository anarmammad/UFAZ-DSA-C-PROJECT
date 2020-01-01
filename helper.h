#if !defined(__HELPER_H__)
#define __HELPER_H__

#define true 1
#define false 0
typedef int bool;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

extern char ERROR_BUF[100];


void throw_exception(char* body, short status_code);
void prepare_options(int argc, char *argv[]);


#endif // __HELPER_H__
