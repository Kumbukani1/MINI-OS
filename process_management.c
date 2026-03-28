#include <stdio.h>
#include <string.h>

#define MAX_PROCESSES 10 //This is the maximum number of processes our system can handle.

//PCB structure, which holds information about each process.

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

struct ProcessControlBlock table[MAX_PROCESSES];
        int count = 0; // This count variable keeps track of the number of processes in the table.
        int next_pid = 1; // This variable is used to assign unique PIDs to new processes.
    


        /* Function to create a new process. It prompts the user for process details, checks if the system can accommodate more processes, and then adds the new process to the process table.
        */
void create_process(){
            if (count >= MAX_PROCESSES){
                printf("\nERROR! System is full. Cannot create new process.\n");
                return;
            }

            struct ProcessControlBlock new_process;
            new_process.pid = next_pid++;
            new_process.waiting_time = 0;
            new_process.turnaround_time = 0;
            strcpy(new_process.state, "New");


            printf("\n--- New Emergency Task ---\n");

            printf("Enter task name: ");
            scanf(" %[^\n]", new_process.name);

            printf("Enter priority (1=Low, 2=Medium, 3=High): ");
            scanf("%d", &new_process.priority);

            printf("Enter burst time in seconds: ");
            scanf("%d", &new_process.burst_time);

            printf("Enter arrival time in seconds: ");
            scanf("%d", &new_process.arrival_time);

            printf("Enter memory required in MB: ");
            scanf("%d", &new_process.memory_size);
            strcpy(new_process.state, "Ready");

            table[count] = new_process;
            count++;

            printf("\nSUCCESS, Task %s created with PID %d\n",
                 new_process.name, new_process.pid);
        }


        
        //Function to display all processes in the system.
        
void display_processes() {
            if(count == 0) {
                printf("\n No tasks created yet.\n");
                return;
            }

                print_line();
            printf("                    PROCESS TABLE                                   \n");
                print_line();
            printf("%-5s %-22s %-5s %-6s %-8s %-7s %-12s\n",
                "PID", "Task Name", "Pri", "Burst", "Arrival", "Mem MB", "State");
            printf("---------------------------------------------------------------------\n");

            int i;
            for(i = 0; i < count; i++) {
                printf("%-5d %-22s %-5d %-6d %-8d %-7d %-12s\n",
                    table[i].pid,
                    table[i].name,
                    table[i].priority,
                    table[i].burst_time,
                    table[i].arrival_time,
                    table[i].memory_size,
                    table[i].state);
            }

             print_line();
            printf("Total tasks: %d\n", count);
        }


        /* Function to terminate a process based on its PID. It checks if the process exists and is not already terminated before marking it as terminated.*/
 void terminate_process() {
            if(count == 0) {
                printf("\n No tasks available to terminate.\n");
                return;
            }

            int target_pid;
            printf("\nEnter PID of task to terminate: ");
            scanf("%d", &target_pid);

            int i;
            for(i = 0; i < count; i++) {
                if(table[i].pid == target_pid) {

                    // check if already terminated
                    if(strcmp(table[i].state, "Terminated") == 0) {
                        printf("\n Task PID %d is already terminated.\n", target_pid);
                        return;
                    }

                    strcpy(table[i].state, "Terminated");
                    printf("\nSUCCESS, Task '%s' with PID %d has been terminated.\n",
                        table[i].name, target_pid);
                    return;
                }
            }

            printf("\nERROR, no task found with PID %d\n", target_pid);
        }




        int main() {
    int choice;

      print_line();
    printf("   SMART EMERGENCY RESPONSE CENTER      \n");
    printf("       Copperbelt University             \n");
      print_line();

    do {
        printf("\n----- PROCESS MANAGEMENT MENU -----\n");
        printf("1. Create Emergency Task\n");
        printf("2. View Process Table\n");
        printf("3. Terminate a Task\n");
        printf("0. Exit\n");
        printf("-----------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:                         
                create_process();
                break;
            case 2:
                display_processes();
                break;
            case 3:
                terminate_process();
                break;
            case 0:
                printf("\nExiting System. Goodbye!\n");
                break;
            default:
                printf("\nERROR, invalid choice. Try again.\n");
        }

    } while(choice != 0);

    return 0;
}