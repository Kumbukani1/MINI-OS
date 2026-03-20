#include <stdio.h>
#include <string.h>

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


void sort_by_arrival(struct ProcessControlBlock proc[], int n) {
    struct ProcessControlBlock temp;

    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-1; j++){

            //if the arrival time of the current process is greater than the next process, swap them
            if(proc[j].arrival_time > proc[j+1].arrival_time) {
                temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }
}


void fcfs(struct ProcessControlBlock proc[], int n) {
    int current_time = 0;

    sort_by_arrival(proc, n);

    for(int i = 0; i < n; i++) {

        if(current_time < proc[i].arrival_time) {
            current_time = proc[i].arrival_time;
        }

        proc[i].waiting_time = current_time - proc[i].arrival_time;
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;

        current_time += proc[i].burst_time;

        strcpy(proc[i].state, "Terminated");
    }
}



void display_results(struct ProcessControlBlock proc[], int n) {
    int i;
    float total_waiting = 0;
    float total_turnaround = 0;

    printf("\n=====================================================================\n");
    printf("                    SCHEDULING RESULTS                         \n");
    printf("=====================================================================\n");
    printf("%-5s %-22s %-8s %-8s %-12s\n",
           "PID", "Task Name", "Waiting", "Turnaround", "State");
    printf("---------------------------------------------------------------------\n");

    for(i = 0; i < n; i++) {
        printf("%-5d %-22s %-8d %-10d %-12s\n",
               proc[i].pid,
               proc[i].name,
               proc[i].waiting_time,
               proc[i].turnaround_time,
               proc[i].state);

        total_waiting += proc[i].waiting_time;
        total_turnaround += proc[i].turnaround_time;
    }

    printf("=====================================================================\n");
    printf("Average Waiting Time    : %.2f seconds\n", total_waiting / n);
    printf("Average Turnaround Time : %.2f seconds\n", total_turnaround / n);
    printf("=====================================================================\n");
}