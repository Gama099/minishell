/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echoubby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 01:14:39 by echoubby          #+#    #+#             */
/*   Updated: 2024/11/30 01:14:41 by echoubby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isalnum(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	ft_isalpha(char c)
{
	if (((c >= 'a') && (c <= 'z'))
		|| ((c >= 'A') && (c <= 'Z')))
		return (1);
	return (0);
}

char	*ft_strdup(char *s1)
{
	int		i;
	int		dupsize;
	char	*dup;

	if (s1 == NULL)
		return (NULL);
	dupsize = ft_strlen(s1) + 1;
	dup = (char *)my_malloc(dupsize);
	i = 0;
	while (i < dupsize)
	{
		dup[i] = s1[i];
		i++;
	}
	return (dup);
}

char	*ft_substr_h(char *s, int start, int end)
{
	int		i;
	char	*res;

	if ((end - start + 1) < 1)
		res = (char *)my_malloc((1) * sizeof(char));
	else
		res = (char *)my_malloc((end - start + 1) * sizeof(char));
	i = 0;
	while (start < end)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}

int	ft_strchrr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
