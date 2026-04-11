//system libraries
#include <stdio.h>
#include <string.h>

// our own files
#include "process_management.h"
#include "cpu_scheduling.h"
#include "memory_management.h"
#include "file_management.h"


void process_management_menu() {
    int choice;

    do {
        printf("\n----- PROCESS MANAGEMENT MENU -----\n");
        printf("1. Create Emergency Task\n");
        printf("2. View Process Table\n");
        printf("3. Execute a Task\n");
        printf("4. Suspend a Task\n");
        printf("5. Terminate a Task\n");
        printf("0. Back to Main Menu\n");
        printf("-----------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                create_process();
                write_log("New emergency task created");
                break;
            case 2:
                display_processes();
                break;
            case 3:
                execute_process();
                write_log("Emergency task executed");
                break;
            case 4:
                suspend_process();
                write_log("Emergency task suspended");
                break;
            case 5:
                terminate_process();
                write_log("Emergency task terminated");
                break;
            case 0:
                printf("\n Returning to Main Menu.......\n");
                break;
            default:
                printf("\nError, Invalid choice. Try again.\n");
        }

    } while(choice != 0);
}

void cpu_scheduling_menu() {
    struct ProcessControlBlock proc[MAX_PROCESSES];
    int n = 0;
    int choice;

    do {
        printf("\n----- CPU SCHEDULING MENU -----\n");
        printf("1. Add Emergency Task\n");
        printf("2. Run FCFS Scheduling\n");
        printf("3. Run SJF Scheduling\n");
        printf("4. Run Priority Scheduling\n");
        printf("0. Back to Main Menu\n");
        printf("-------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                if(n >= MAX_PROCESSES) {
                    printf("\nError, System full!\n");
                } else {
                    printf("\nEnter task name: ");
                    scanf(" %[^\n]", proc[n].name);
                    printf("Enter priority (1=High, 2=Medium, 3=Low): ");
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
                    printf("\nSuccess, Task added!\n");
                    write_log("CPU scheduling task added");
                }
                break;
            case 2:
                if(n == 0) {
                    printf("\nError, No tasks added yet!\n");
                } else {
                    fcfs(proc, n);
                    display_fcfs_results(proc, n);
                    write_log("FCFS Scheduling executed");
                }
                break;
            case 3:
                if(n == 0) {
                    printf("\nError, No tasks added yet!\n");
                } else {
                    sjf(proc, n);
                    display_sjf_results(proc, n);
                    write_log("SJF Scheduling executed");
                }
                break;
            case 4:
                if(n == 0) {
                    printf("\nError, No tasks added yet!\n");
                } else {
                    priority_scheduling(proc, n);
                    display_priority_results(proc, n);
                    write_log("Priority Scheduling executed");
                }
                break;
            case 0:
                printf("\nReturning to Main Menu........\n");
                break;
            default:
                printf("\nError, Invalid choice. Try again.\n");
        }

    } while(choice != 0);
}


void memory_management_menu() {
    int choice;
    char process_name[50];
    int process_size;

    do {
        printf("\n----- MEMORY MANAGEMENT MENU -----\n");
        printf("1. Add Memory Block\n");
        printf("2. Display Memory Table\n");
        printf("3. Allocate Memory - First Fit\n");
        printf("4. Allocate Memory - Best Fit\n");
        printf("5. Allocate Memory - Worst Fit\n");
        printf("0. Back to Main Menu\n");
        printf("----------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                add_memory_block();
                write_log("Memory block added");
                break;
            case 2:
                display_memory();
                break;
            case 3:
                printf("\nEnter process name: ");
                scanf(" %[^\n]", process_name);
                printf("Enter memory required in MB: ");
                scanf("%d", &process_size);
                first_fit(process_name, process_size);
                write_log("Memory allocated using First Fit");
                break;
            case 4:
                printf("\nEnter process name: ");
                scanf(" %[^\n]", process_name);
                printf("Enter memory required in MB: ");
                scanf("%d", &process_size);
                best_fit(process_name, process_size);
                write_log("Memory allocated using Best Fit");
                break;
            case 5:
                printf("\nEnter process name: ");
                scanf(" %[^\n]", process_name);
                printf("Enter memory required in MB: ");
                scanf("%d", &process_size);
                worst_fit(process_name, process_size);
                write_log("Memory allocated using Worst Fit");
                break;
            case 0:
                printf("\nReturning to Main Menu.......\n");
                break;
            default:
                printf("\nError, Invalid choice. Try again.\n");
        }

    } while(choice != 0);
}


void file_management_menu() {
    int choice;
    char message[200];

    do {
        printf("\n----- FILE MANAGEMENT MENU -----\n");
        printf("1. Write Log Entry\n");
        printf("2. View System Log\n");
        printf("3. Clear System Log\n");
        printf("0. Back to Main Menu\n");
        printf("--------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("\nEnter log message: ");
                scanf(" %[^\n]", message);
                write_log(message);
                break;
            case 2:
                read_log();
                break;
            case 3:
                clear_log();
                break;
            case 0:
                printf("\nReturning to Main Menu...\n");
                break;
            default:
                printf("\nError, Invalid choice. Try again.\n");
        }

    } while(choice != 0);
}


// global print line function
void print_line() {
    printf("=====================================================================\n");
}


int main() {
    int choice;

    print_line();
    printf("       SMART EMERGENCY RESPONSE CENTER      \n");
    printf("             Kitwe City Council            \n");
    print_line();

    write_log("Mini-OS System Started");

    do {
        printf("\n========= MAIN MENU =========\n");
        printf("1. Process Management\n");
        printf("2. CPU Scheduling\n");
        printf("3. Memory Management\n");
        printf("4. File Management\n");
        printf("0. Exit System\n");
        printf("=============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                process_management_menu();
                break;
            case 2:
                cpu_scheduling_menu();
                break;
            case 3:
                memory_management_menu();
                break;
            case 4:
                file_management_menu();
                break;
            case 0:
                write_log("Mini-OS System Shutdown");
                printf("\n Shutting down Mini-OS. Goodbye!\n");
                print_line();
                break;
            default:
                printf("\nError, Invalid choice. Try again.\n");
        }

    } while(choice != 0);

    return 0;
}