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

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		len;
	int		j;
	char	*b;

	i = 0;
	j = 0;
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

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char    *ft_strcpy(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i]; // so this will make s1 = to whatever s2 is looping through the string
		i++;
	}
	s1[i] = s2[i];  // now that we are finsihing looping though s1[i] will equal s2[i]
	return (s1);
}
