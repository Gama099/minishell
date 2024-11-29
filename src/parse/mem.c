/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hadd <sel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:28:57 by sel-hadd          #+#    #+#             */
/*   Updated: 2024/11/29 22:28:59 by sel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*my_malloc(size_t size)
{
	void			*ptr;
	t_memoryblock	*block;

	ptr = malloc(size);
	if (ptr == NULL)
		err_n_ex("syscall failed", "malloc", NULL, 1);
	block = (t_memoryblock *)malloc(sizeof(t_memoryblock));
	if (block == NULL)
		err_n_ex("syscall failed", "malloc", NULL, 1);
	block->ptr = ptr;
	block->size = size;
	block->next = ft_bash()->head;
	ft_bash()->head = block;
	return (ptr);
}

void	cleanup(void)
{
	t_memoryblock	*tmp2;
	t_memoryblock	*tmp;

	tmp = ft_bash()->head;
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
	ft_bash()->head = NULL;
}
