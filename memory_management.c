#include <stdio.h>
#include <string.h>


#define MAX_BLOCKS 5
#define MAX_PROCESSES 10


struct MemoryBlock {
    int block_id;
    int block_size;
    int is_free;  //1 = free, 0 = occupied
    char process_name[50];
};

struct MemoryBlock memory[MAX_BLOCKS];
    int block_counter = 0;




void print_line() {
    printf("=====================================================================================\n");
}

void add_memory_block() {
    if(block_counter >= MAX_BLOCKS) {
        printf("\nERROR, Maximum memory blocks reached!\n");
        return;
    }

    struct MemoryBlock new_block;

    new_block.block_id = block_counter + 1;
    new_block.is_free = 1;
    strcpy(new_block.process_name, "None");

    printf("\n--- Add Memory Block ---\n");
    printf("Enter block size in MB: ");
    scanf("%d", &new_block.block_size);

    memory[block_counter] = new_block;
    block_counter++;

    printf("\n Memory block %d of %dMB successfully added!\n",
           new_block.block_id, new_block.block_size);
}


void display_memory() {
    if(block_counter == 0) {
        printf("\n No memory blocks created yet!\n");
        return;
    }


    print_line();
    printf("                            MEMORY BLOCKS STATUS                                   \n");    
    print_line();

    printf("%-10s %-15s %-10s %-20s\n",
         "Block ID", "Block Size (MB)", "Status", "Occupied By");
    printf("-------------------------------------------------------------------------------------\n");

        for(int i = 0; i < block_counter; i++) {
            printf("%-8d %-12d %-10s %-20s\n",
                   memory[i].block_id,
                   memory[i].block_size,
                   memory[i].is_free ? "Free" : "Occupied",
                   memory[i].process_name);
        }

    print_line();

    int free_blocks = 0;
    int occupied_blocks = 0;
    int free_memory = 0;
    int occupied_memory = 0;

        for(int i = 0; i< block_counter; i++) {
            if (memory[i].is_free == 1) {
                free_blocks++;
                free_memory += memory[i].block_size;
            }
            else{
                occupied_blocks++;
                occupied_memory += memory[i].block_size;
            
            }
        }
         printf("Free Blocks    : %d  (%d MB)\n", free_blocks, free_memory);
         printf("Occupied Blocks: %d  (%d MB)\n", occupied_blocks, occupied_memory);
         printf("Fragmentation  : %d MB of memory is fragmented/wasted\n", free_memory);
         print_line();
    }


void first_fit( char process_name[], int process_size) {

     printf("\nINFO, %s is in WAITING state - searching for memory...\n", process_name);


    for (int i = 0; i < block_counter; i++) {

        if( memory[i].is_free == 1 && memory[i].block_size >= process_size) {
            memory[i].is_free = 0; // mark block as occupied
            strcpy(memory[i].process_name, process_name);
            printf("\nSUCCESS, process %s allocated to Block %d (%d MB)\n",
                 process_name, memory[i].block_id, memory[i].block_size);
        }
    }
        printf("\n ERROR, no suitable memory block found for process %s (%dMB)\n",process_name, process_size);
}

void best_fit( char process_name[], int process_size) {

         printf("\nINFO, %s is in WAITING state - searching for memory...\n", process_name);

    int best_index = -1;


    for (int i = 0; i < block_counter; i++) {
        if (memory[i].is_free ==1 && memory[i].block_size >= process_size) {
            if(best_index == -1 || memory[i].block_size < memory[best_index].block_size) {
                best_index = i;
            }
        }
    }

    if(best_index != -1) {
        memory[best_index].is_free = 0;
        strcpy(memory[best_index].process_name, process_name);
        printf("\n SUCCESS, Process %s allocated to Block %d (%d MB)\n",
               process_name, memory[best_index].block_id, memory[best_index].block_size);
    }
    else {
        printf("\n ERROR, no suitablbe memory block found for process %s (%d MB ) \n", process_name, process_size);
    }
}


void worst_fit(char process_name[], int process_size) {

    printf("\nINFO, %s is in WAITING state - searching for memory...\n", process_name);

    int worst_index = -1;

    for(int i = 0; i < block_counter; i++) {
        if(memory[i].is_free == 1 && memory[i].block_size >= process_size) {
            if(worst_index == -1 || memory[i].block_size > memory[worst_index].block_size) {
                worst_index = i;
            }
        }
    }

    if(worst_index != -1) {
        memory[worst_index].is_free = 0;
        strcpy(memory[worst_index].process_name, process_name);
        printf("\nSUCCESS, %s allocated to Block %d (%dMB)\n",
               process_name, memory[worst_index].block_id,
               memory[worst_index].block_size);
    } 
    else {
        printf("\nERROR, No suitable block found for %s (%dMB)\n",
               process_name, process_size);
    }
}



int main() {
    int choice;
    char process_name[50];
    int process_size;

    print_line();
    printf("       SMART EMERGENCY RESPONSE CENTER     \n");
    printf("            Copperbelt University           \n");
    print_line();

    do {
        printf("\n----- MEMORY MANAGEMENT MENU -----\n");
        printf("1. Add Memory Block\n");
        printf("2. Display Memory Table\n");
        printf("3. Allocate Memory - First Fit\n");
        printf("4. Allocate Memory - Best Fit\n");
        printf("5. Allocate Memory - Worst Fit\n");
        printf("0. Exit\n");
        printf("----------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                add_memory_block();
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
                break;
            case 4:
                printf("\nEnter process name: ");
                scanf(" %[^\n]", process_name);
                printf("Enter memory required in MB: ");
                scanf("%d", &process_size);
                best_fit(process_name, process_size);
                break;
            case 5:
                printf("\nEnter process name: ");
                scanf(" %[^\n]", process_name);
                printf("Enter memory required in MB: ");
                scanf("%d", &process_size);
                worst_fit(process_name, process_size);
                break;
            case 0:
                printf("\nExiting Memory. Goodbye!\n");
                break;
            default:
                printf("\nERROR, Invalid choice. Try again.\n");
        }

    } while(choice != 0);

    return 0;
}