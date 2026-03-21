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
    void print_line() {
        printf("=====================================================================\n");
    }


//FCFS scheduling algorithm implementation
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

void display_fcfs_results(struct ProcessControlBlock proc[], int n) {
    float total_waiting = 0;
    float total_turnaround = 0;

    print_line();
    printf("                    FCFS SCHEDULING RESULTS                         \n");
    print_line();
    printf("%-5s %-22s %-8s %-8s %-12s\n",
           "PID", "Task Name", "Waiting", "Turnaround", "State");
    printf("---------------------------------------------------------------------\n");

    for(int i = 0; i < n; i++) {
        printf("%-5d %-22s %-8d %-10d %-12s\n",
               proc[i].pid,
               proc[i].name,
               proc[i].waiting_time,
               proc[i].turnaround_time,
               proc[i].state);

        total_waiting += proc[i].waiting_time;
        total_turnaround += proc[i].turnaround_time;
    }

     print_line();
    printf("Average Waiting Time    : %.2f seconds\n", total_waiting / n);
    printf("Average Turnaround Time : %.2f seconds\n", total_turnaround / n);
     print_line();
}




//SJF scheduling algorithm implementation
void sort_by_burst(struct ProcessControlBlock proc[], int n){

    struct ProcessControlBlock temp;

    for(int i = 0; i < n-1; i++) {
         for(int j = 0; j < n-1; j++){

            //if the burst time of the current process is greater than the next process, swap them
            if (proc[j].burst_time > proc[j+1].burst_time) {
                temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
         }
    }
}

void sjf(struct ProcessControlBlock proc[], int n) {
      int current_time = 0;

      sort_by_burst(proc, n);

      for(int i = 0; i < n; i++) {

        if(current_time < proc[i].arrival_time){
            current_time = proc[i].arrival_time;
        }

        proc[i].waiting_time = current_time - proc[i].arrival_time;
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
        
         current_time += proc[i].burst_time;

         strcpy(proc[i].state, "Terminated");
      }
}


void display_sjf_results(struct ProcessControlBlock proc[], int n) {
    float total_waiting = 0;
    float total_turnaround =0;

    print_line();
    printf("                    SJF SCHEDULING RESULTS                         \n");
    print_line();

    printf("%-5s %-22s %-8s %-10s %-12s\n",
           "PID", "Task Name", "Waiting", "Turnaround", "State");
    printf("---------------------------------------------------------------------\n");

    for(int i = 0; i < n; i++) {
        printf("%-5d %-22s %-8d %-10d %-12s\n",
               proc[i].pid,
               proc[i].name,
               proc[i].waiting_time,
               proc[i].turnaround_time,
               proc[i].state);

        total_waiting += proc[i].waiting_time;
        total_turnaround += proc[i].turnaround_time;
    }

    print_line();
    printf("Average Waiting Time    : %.2f seconds\n", total_waiting / n);
    printf("Average Turnaround Time : %.2f seconds\n", total_turnaround / n);
    print_line();
}




int main() {
    printf("CPU Scheduling module loaded successfully!\n");
    return 0;
}