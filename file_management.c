#include <stdio.h>
#include <string.h>
#include <time.h>

#define LOG_FILE "Emergency_log.txt"

void print_line() {
    printf("======================================================================================\n");
}


void write_log(char message[]) {
    FILE *log_file;
    time_t current_time;
    char time_string[50];

    log_file = fopen(LOG_FILE, "a");

    if(log_file == NULL) {
        printf("\nERROR, Could not open log file!\n");
        return;
    }

    time(&current_time);
    strcpy(time_string, ctime(&current_time));

    time_string[strlen(time_string) - 1] = '\0';

    fprintf(log_file, "[%s] %s\n", time_string, message);

    fclose(log_file);

    printf("\nSUCCESS, Log entry saved!\n");
}


void read_log() {
    FILE *log_file;
    char line[200];

    log_file = fopen(LOG_FILE, "r");

    if(log_file == NULL) {
        printf("\nINFO, No log file found. No events recorded yet.\n");
        return;
    }

    print_line();
    printf("                    EMERGENCY SYSTEM LOG                            \n");
    print_line();

    while(fgets(line, sizeof(line), log_file) != NULL) {
        printf("%s", line);
    }

    print_line();
    fclose(log_file);
}


void clear_log() {
    FILE *log_file;

    log_file = fopen(LOG_FILE, "w");

    if(log_file == NULL) {
        printf("\nERROR, Could not clear log file!\n");
        return;
    }

    fclose(log_file);
    printf("\nSUCCESS, Log file cleared!\n");
}