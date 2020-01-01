#include "helper.h"

char ERROR_BUF[100];

void throw_exception(char* body, short status_code){
    printf("\033[91m[ERROR] %s\n", body);
    printf("\033[91mExitting...\n");
    exit(status_code);
}
