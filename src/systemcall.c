/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   systemcall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:11:14 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:11:16 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_dup(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		err_n_ex("syscall failed", "dup2", NULL, 1);
	else
		ft_close(old_fd);
}

void	save_stdfd(void)
{
	ft_bash()->fd_stdin = dup(STDIN_FILENO);
	if (ft_bash()->fd_stdin == -1)
		err_n_ex("syscall failed", "dup", NULL, 1);
	ft_bash()->fd_stdout = dup(STDOUT_FILENO);
	if (ft_bash()->fd_stdout == -1)
		err_n_ex("syscall failed", "dup", NULL, 1);
}

void	revert_stdfd(void)
{
	ft_dup(ft_bash()->fd_stdin, STDIN_FILENO);
	ft_dup(ft_bash()->fd_stdout, STDOUT_FILENO);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		err_n_ex("error with fork", "fork", NULL, 1);
	return (pid);
}

void	ft_close(int fd)
{
	if (close(fd) == -1)
		err_n_ex("syscall failed", "close", NULL, 1);
}
