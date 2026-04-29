#include <stdio.h>
#include <string.h>
#include <time.h>


void print_line();

#define LOG_FILE "Emergency_log.txt"


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

    fclose(log_file); // Always close the file after writing to it.

    printf("\nSuccess, Log entry saved!\n");
}


void read_log() {
    FILE *log_file;
    char line[200];

    log_file = fopen(LOG_FILE, "r");

    if(log_file == NULL) {
        printf("\nNo log file found. No events recorded yet.\n");
    
        return;
    }

    print_line();
    printf("                    EMERGENCY SYSTEM LOG                            \n");
    print_line();

    int lines_read = 0;

    while(fgets(line, sizeof(line), log_file) != NULL) {
        printf("%s", line);
        lines_read++;
    }

    if(lines_read == 0) {
        printf("   Log is empty. No events recorded yet.\n");
    }

    print_line();
    fclose(log_file);
    }


void clear_log() {
    FILE *log_file;

    log_file = fopen(LOG_FILE, "w");

    if(log_file == NULL) {
        printf("\nError, Could not clear log file!\n");
        return;
    }

    fclose(log_file);
    printf("\nSuccess, Log file cleared!\n");
}

