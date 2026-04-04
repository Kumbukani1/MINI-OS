#ifndef PROCESS_MANAGEMENT_H
#define PROCESS_MANAGEMENT_H

#define MAX_PROCESSES 10

struct ProcessControlBlock {
    int pid;
    char name[50];
    char state[15];
    int priority;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int memory_size;
};

extern struct ProcessControlBlock table[MAX_PROCESSES];
extern int count;
extern int next_pid;

void create_process();
void display_processes();
void terminate_process();

#endif