#include "../../includes/minishell.h"


MemoryBlock* head = NULL;

void* my_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr) {
        MemoryBlock* block = (MemoryBlock*)malloc(sizeof(MemoryBlock));
        block->ptr = ptr;
        block->size = size;
        block->next = head; // Add to the front of the list
        head = block;
        printf("Allocated: %zu bytes\n", size);
    }
    return ptr;
}

void my_free(void* ptr) {
    MemoryBlock* current = head;
    MemoryBlock* previous = NULL;

    while (current != NULL) {
        if (current->ptr == ptr) {
            // Found the block
            if (previous) {
                previous->next = current->next;
            } else {
                head = current->next; // Remove from head
            }
            free(current->ptr); // Free the actual memory
            free(current); // Free the block
            printf("Freed memory\n");
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Pointer not found\n");
}

void cleanup(void) {
    MemoryBlock* current = head;
    while (current != NULL) {
        MemoryBlock* next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
    head = NULL; // Reset the list
}
