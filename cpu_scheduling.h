#ifndef CPU_SCHEDULING_H
#define CPU_SCHEDULING_H

#define MAX_PROCESSES 10

struct ProcessControlBlock;

void sort_by_arrival(struct ProcessControlBlock proc[], int n);
void sort_by_burst(struct ProcessControlBlock proc[], int n);
void sort_by_priority(struct ProcessControlBlock proc[], int n);
void fcfs(struct ProcessControlBlock proc[], int n);
void sjf(struct ProcessControlBlock proc[], int n);
void priority_scheduling(struct ProcessControlBlock proc[], int n);
void display_fcfs_results(struct ProcessControlBlock proc[], int n);
void display_sjf_results(struct ProcessControlBlock proc[], int n);
void display_priority_results(struct ProcessControlBlock proc[], int n);

#endif