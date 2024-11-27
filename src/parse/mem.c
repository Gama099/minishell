#include "../../includes/minishell.h"

void	*my_malloc(size_t size)
{
	void		*ptr;
	memoryblock	*block;

	ptr = malloc(size);
	if (ptr == NULL)
		err_n_exit("syscall failed", "malloc", NULL, 1);
	block = (memoryblock*)malloc(sizeof(memoryblock));
	if (block == NULL)
		err_n_exit("syscall failed", "malloc", NULL, 1);
	block->ptr = ptr;
	block->size = size;
	block->next = head;
	head = block;
	return (ptr);
}

void	cleanup(void)
{
	memoryblock	*tmp2;
	memoryblock	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2->ptr);
		tmp2->ptr = NULL;
		free(tmp2);
		tmp2 = NULL;
	}
	tmp = NULL;
	head = NULL;
}
