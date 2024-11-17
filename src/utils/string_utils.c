#include "../../includes/minishell.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	if (n == 0 || s1 == NULL)
		return (-1);
	i = 0;
	while ((s1[i] && s2[i]) && i < n - 1)
	{
		if (s1[i] == s2[i])
			i++;
		else
			break ;
	}
	return (s1[i] - s2[i]);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		len;
	int		j;
	char	*b;

	i = 0;
	j = 0;
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	b = malloc((len + 1) * sizeof(char));
	if (b == NULL)
		return (NULL);
	while (s1[i] && i < len)
	{
		b[i] = s1[i];
		i++;
	}
	while (s2[j] && i < len)
		b[i++] = s2[j++];
	b[i] = '\0';
	return (b);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(src);
	if (dstsize != 0)
	{
		i = 0;
		while (i < dstsize - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

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
	dup = (char *)malloc(dupsize);
	if (dup == NULL)
		return (0);
	i = 0;
	while (i < dupsize)
	{
		dup[i] = s1[i];
		i++;
	}
	return (dup);
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

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*((unsigned char *) b + i) = c;
		i++;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

int	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (ft_putchar_fd(s[i++], fd))
			return (1);
	}
	return (0);
}

int	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		return (1);
	return (0);
}

int	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (ft_putchar_fd(s[i++], fd))
			return (1);
	}
	if (ft_putchar_fd('\n', fd))
		return (1);
	return (0);
}
