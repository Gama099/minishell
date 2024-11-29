/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hadd <sel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:38:16 by sel-hadd          #+#    #+#             */
/*   Updated: 2024/11/30 00:12:20 by sel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strcpy(char *dest, char *src)
{
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest);
}

int	is_white_space(char charac)
{
	if (charac == ' ' || (charac >= '\t' && charac <= '\r'))
		return (1);
	return (0);
}

void	trim_spaces(char **buffer)
{
	char	*start;
	char	*end;
	int		len;
	char	*new_str;

	if (!*buffer[0])
		return ;
	start = *buffer;
	len = ft_strlen(start);
	if ((!is_white_space(*start) && !is_white_space(start[len - 1])) || !len)
		return ;
	end = &start[len - 1];
	while (is_white_space(*start))
		start++;
	if (!start)
		return ;
	while (is_white_space(*end) && end > start)
		end--;
	new_str = (char *)my_malloc(end - start + 2);
	ft_strlcpy(new_str, start, (end - start) + 2);
	*buffer = new_str;
}
