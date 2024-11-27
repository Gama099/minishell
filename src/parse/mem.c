#include "../../includes/minishell.h"

void* my_malloc(size_t size)
{
    void* ptr = malloc(size);
	if (ptr == NULL)
		err_n_exit("syscall failed", "malloc", NULL, 1);
	memoryblock* block = (memoryblock*)malloc(sizeof(memoryblock));
	if (block == NULL)
		err_n_exit("syscall failed", "malloc", NULL, 1);
	block->ptr = ptr;
	block->size = size;
	block->next = head; // Add to the front of the list
	head = block;
    return ptr;
}

void cleanup(void)
{
    memoryblock* current = head;
    while (current != NULL) {
        memoryblock* next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
    head = NULL; // Reset the list
}
