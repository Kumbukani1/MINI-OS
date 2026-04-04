#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#define LOG_FILE "emergency_log.txt"

void write_log(char message[]);
void read_log();
void clear_log();

#endif