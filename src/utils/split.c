/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:14:25 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:14:26 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_strlcpyy(char *dst, const char *src, int size)
{
	int	i;

	if (size == 0)
		return ;
	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	allocating(char **str, int index, int len)
{
	str[index] = (char *)my_malloc(len);
	return (0);
}

int	ft_write(char **str, char const *s, char c)
{
	int	j;
	int	index;

	index = 0;
	while (*s)
	{
		j = 0;
		while (*s == c)
			s++;
		while (*s && *s != c)
		{
			j++;
			s++;
		}
		if (j > 0)
		{
			if (allocating(str, index, j + 1))
				return (1);
			ft_strlcpyy(str[index], s - j, j + 1);
			index++;
		}
	}
	return (0);
}

int	count(char const *s, char sep)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != sep)
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		len;

	if (s == NULL)
		return (NULL);
	len = count(s, c);
	if (!len)
		clean_exit(1);
	str = (char **)my_malloc((len + 1) * sizeof(char *));
	str[len] = NULL;
	if (ft_write(str, s, c))
		return (NULL);
	return (str);
}
