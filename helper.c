#include "helper.h"

char FILENAME[100] = {0}, TEXT_TO_WRITE[100] = {0},  OUTPUT_FILE[100] = {0}, ERROR_BUFF[100] = {0}, LOG_BUFF[600] = {0};

unsigned POSITION_TO_WRITE[2] = { 0, 0 }; // position expressed as: { x, y } starting from the top left of the image

bool IS_DATE_SET = false;

Color COLOR_TO_WRITE = BLACK; // default color is black


void throw_exception(char* body, short status_code){
    fprintf(stderr, "\033[91m[ERROR] %s\n", body);
    fprintf(stderr, "\033[91mExitting...\n");
    exit(status_code);
}

void get_options(int argc, char *argv[]){
    if(argv[1])
        strcpy(FILENAME, argv[1]);
    else
        print_man_page_and_exit();

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
                sscanf(optarg, "%2hhx%2hhx%2hhx%2hhx", &COLOR_TO_WRITE.red, &COLOR_TO_WRITE.green, &COLOR_TO_WRITE.blue, &COLOR_TO_WRITE.alpha_channel);
                COLOR_TO_WRITE.alpha_channel = 0; // We set default value for alpha channel as 0
                break;
            case ':':
                sprintf(ERROR_BUFF, "Option '%s' has missing argument", argv[optind - 1]);
                throw_exception(ERROR_BUFF, -5);
                break;
            case '?':
                if (optopt == 0) 
                    sprintf(ERROR_BUFF, "Unknown option '%s'", argv[optind - 1]);
                else 
                    sprintf(ERROR_BUFF, "Error parsing option '%s'", argv[optind - 1]);

                throw_exception(ERROR_BUFF, -6);
                break;
        }
    }
    if (IS_DATE_SET)
        strcat(TEXT_TO_WRITE, get_linux_date());
    
    for (int i = 0; i < strlen(TEXT_TO_WRITE); i++)
        TEXT_TO_WRITE[i] = tolower(TEXT_TO_WRITE[i]);

}


char* get_linux_date(){
    int pipedes[2];
    char* string_date = (char*) calloc(50, 1);

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
        close(pipedes[0]);
        wait(NULL);
    }
    return string_date;
}

void print_man_page_and_exit(){
    FILE* man_file;
    if ( ! (man_file = fopen("man.txt", "r")) )
        throw_exception("Cannot open man file", ERR_FILE);
  
    // Read contents from file 
    char ch = fgetc(man_file); 
    while (ch != EOF) { 
        printf ("%c", ch); 
        ch = fgetc(man_file); 
    } 
  
    fclose(man_file); 
    exit(0);
}

void str_logger(char* str){
    FILE* log_file;
    if ( ! (log_file = fopen("log.txt", "a+")) )
        throw_exception("Cannot write to log file", ERR_FILE);
    
    fwrite(str, strlen(str), 1, log_file);
    fputc('\n', log_file);

    fclose(log_file);
}