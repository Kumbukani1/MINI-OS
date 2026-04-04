#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#define MAX_BLOCKS 10

struct MemoryBlock {
    int block_id;
    int block_size;
    int is_free;
    char process_name[50];
};

extern struct MemoryBlock memory[MAX_BLOCKS];
extern int block_count;

void add_memory_block();
void display_memory();
void first_fit(char process_name[], int process_size);
void best_fit(char process_name[], int process_size);
void worst_fit(char process_name[], int process_size);

#endif