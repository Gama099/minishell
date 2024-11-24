#include "../../includes/minishell.h"

static int	len(int n)
{
	int	i;

	i = 1;
	while (n / 10)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static char	*n_negative(int c)
{
	int		tol;
	long	b;
	char	*a;

	b = (long)c;
	if (b == -2147483648)
		tol = 11;
	else
		tol = len(b) + 1;
	b *= -1;
	a = malloc((tol + 1) * sizeof(char));
	if (a == NULL)
		return (NULL);
	a[0] = '-';
	a[tol--] = '\0';
	while (tol > 0)
	{
		a[tol--] = (b % 10) + '0';
		b /= 10;
	}
	return (a);
}

char	*ft_itoa(int n)
{
	int		tol;
	char	*b;

	tol = 0;
	if (n >= 0)
	{
		tol = len(n);
		b = malloc((tol + 1) * sizeof(char));
		if (b == NULL)
			return (NULL);
		b[tol--] = '\0';
		while (tol >= 0)
		{
			b[tol] = (n % 10) + '0';
			n /= 10;
			tol--;
		}
	}
	else
		b = n_negative(n);
	return (b);
}