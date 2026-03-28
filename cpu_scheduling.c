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

            // CPU utilization calculations
        int total_burst = 0;
        for(int i = 0; i < n; i++) {
            total_burst += proc[i].burst_time;
        }
        int total_time = proc[n-1].turnaround_time + proc[0].arrival_time;
        printf("CPU Utilization         : %.2f%%\n",
            (float)total_burst / total_time * 100);

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

      // CPU utilization calculations
        int total_burst = 0;
        for(int i = 0; i < n; i++) {
            total_burst += proc[i].burst_time;
        }
        int total_time = proc[n-1].turnaround_time + proc[0].arrival_time;
        printf("CPU Utilization         : %.2f%%\n",
            (float)total_burst / total_time * 100);
    print_line();
}



void sort_by_priority(struct ProcessControlBlock proc[], int n) {

    struct ProcessControlBlock temp;

    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-1; j++){

            //if the priority of the current process is LOWER than the next process, swap them
            if(proc[j].priority < proc[j+1].priority) {
                temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }
}

void priority_scheduling( struct ProcessControlBlock proc[], int n) {

    int current_time = 0;

    sort_by_priority(proc, n);

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

void display_priority_results(struct ProcessControlBlock proc[], int n) {
    float total_waiting = 0;
    float total_turnaround = 0;

    print_line();
    printf("                PRIORITY SCHEDULING RESULTS                         \n");
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

      // CPU utilization calculations
        int total_burst = 0;
        for(int i = 0; i < n; i++) {
            total_burst += proc[i].burst_time;
        }
        int total_time = proc[n-1].turnaround_time + proc[0].arrival_time;
        printf("CPU Utilization         : %.2f%%\n",
            (float)total_burst / total_time * 100);
    print_line();
}




int main() {
    struct ProcessControlBlock proc[MAX_PROCESSES];
    int n = 0;
    int choice;

    print_line();
    printf("       SMART EMERGENCY RESPONSE CENTER      \n");
    printf("            Copperbelt University            \n");
    print_line();

    do {
        printf("\n----- CPU SCHEDULING MENU -----\n");
        printf("1. Add Emergency Task\n");
        printf("2. Run FCFS Scheduling\n");
        printf("3. Run SJF Scheduling\n");
        printf("4. Run Priority Scheduling\n");
        printf("0. Exit\n");
        printf("-------------------------------\n\n");
        
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                if(n >= MAX_PROCESSES) {
                    printf("\nERROR, system full!\n");
                } else {
                    printf("\nEnter task name: ");
                    scanf(" %[^\n]", proc[n].name);
                    printf("Enter priority (1=Low, 2=Medium, 3=High): ");
                    scanf("%d", &proc[n].priority);
                    printf("Enter burst time in seconds: ");
                    scanf("%d", &proc[n].burst_time);
                    printf("Enter arrival time in seconds: ");
                    scanf("%d", &proc[n].arrival_time);
                    printf("Enter memory size in MB: ");
                    scanf("%d", &proc[n].memory_size);
                    proc[n].pid = n + 1;
                    proc[n].waiting_time = 0;
                    proc[n].turnaround_time = 0;
                    strcpy(proc[n].state, "Ready");
                    n++;
                    printf("\nTask added successfully!\n");
                }
                break;
            case 2:
                if(n == 0) {
                    printf("\nERROR, no tasks added yet!\n");
                } else {
                    fcfs(proc, n);
                    display_fcfs_results(proc, n);
                }
                break;
            case 3:
                if(n == 0) {
                    printf("\nERROR, no tasks added yet!\n");
                } else {
                    sjf(proc, n);
                    display_sjf_results(proc, n);
                }
                break;
            case 4:
                if(n == 0) {
                    printf("\nERROR, no tasks added yet!\n");
                } else {
                    priority_scheduling(proc, n);
                    display_priority_results(proc, n);
                }
                break;
            case 0:
                printf("\n Exiting the system. Goodbye!\n");
                break;
            default:
                printf("\nERROR, invalid choice. Try again.\n");
        }

    } while(choice != 0);

    return 0;
}