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
	int	i;

	i = 0;
	str[index] = malloc(len);
	if (str[index] == NULL)
	{
		while (i < index)
			free(str[i++]);
		free(str);
		return (1);
	}
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

	len = count(s, c);
	if (!len)
		exit(1);
	str = (char **)malloc((len + 1) * sizeof(char *));
	if (!str)
		err_n_exit("syscall failed", "malloc", NULL, 1);
	str[len] = NULL;
	if (ft_write(str, s, c))
		return (NULL);
	return (str);
}
