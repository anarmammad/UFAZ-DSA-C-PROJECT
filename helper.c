#include "helper.h"

char FILENAME[100], TEXT_TO_WRITE[100] = "",  OUTPUT_FILE[100] = "stdout", ERROR_BUF[100];

unsigned POSITION_TO_WRITE[2] = { 0, 0 }; // position expressed as: { x, y } from left to right and from bottom to top

bool IS_DATE_SET = false;

Color COLOR_TO_WRITE = BLACK; // default color is black


void throw_exception(char* body, short status_code){
    printf("\033[91m[ERROR] %s\n", body);
    printf("\033[91mExitting...\n");
    exit(status_code);
}

void get_options(int argc, char *argv[]){
    if(argv[1])
        strcpy(FILENAME, argv[1]);

    static struct option longopts[] = {
        { "text", required_argument, NULL, 't' },
        { "date", no_argument, NULL, 'd' },
        { "pos", required_argument, NULL, 'p' },
        { "o", required_argument, NULL, 'o' },
        { "color", required_argument, NULL, 'c'},
        { 0,         0,           0, 0 }
    };
    char ch;
    while ((ch = getopt_long_only(argc, argv, ":td:p:o:", longopts, NULL)) != -1) {
        switch (ch) {
            case 't':
                strcpy(TEXT_TO_WRITE, optarg);
                break;
            case 'd':
                IS_DATE_SET = true;
                break;
            case 'p':
                sscanf(optarg, "%u,%u", &POSITION_TO_WRITE[0], &POSITION_TO_WRITE[1]);
                break;
            case 'o':
                strcpy(OUTPUT_FILE, optarg);
                break;
            case 'c':
                sscanf(optarg, "%2hhx%2hhx%2hhx", &COLOR_TO_WRITE.red, &COLOR_TO_WRITE.green, &COLOR_TO_WRITE.blue);
                COLOR_TO_WRITE.alpha_channel = 0; // We set default value for alpha channel as 0
                break;
            case ':':
                sprintf(ERROR_BUF, "Option '%s' has missing argument", argv[optind - 1]);
                throw_exception(ERROR_BUF, -5);
                break;
            case '?':
                if (optopt == 0) 
                    sprintf(ERROR_BUF, "Unknown option '%s'", argv[optind - 1]);
                else 
                    sprintf(ERROR_BUF, "Error parsing option '%s'", argv[optind - 1]);

                throw_exception(ERROR_BUF, -6);
                break;
        }
    }
}


char* get_linux_date(){
    int pipedes[2];
    char* string_date = (char*) malloc(50);

    if (pipe(pipedes) == -1)
        throw_exception("Pipe error", -10);


    pid_t f_pid = fork();
    if ( f_pid == -1)
        throw_exception("Fork error", -11);

    if(f_pid == 0) { // child process
        dup2 (pipedes[1], STDOUT_FILENO);
        close(pipedes[0]);
        close(pipedes[1]);
        execl("/bin/date", "date", NULL);
        exit(0);
    } 
    else { // parent process
        close(pipedes[1]);
        int nbytes = read(pipedes[0], string_date, 50);
        string_date[nbytes - 1] = '\0'; // (nbytes - 1) is line feed which is present in output of linux command
        wait(NULL);
    }
    return string_date;
}