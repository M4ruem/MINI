#include "../include/minishell.h"

int	ft_intlen(int n)
{
	unsigned int	nb;
	int				len;

	len = 0;
	if (n < 0)
	{
		n = n * -1;
		len = 1;
	}
	nb = n;
	while (nb > 9)
	{
		nb = nb / 10;
		len++;
	}
	return (len + 1);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nb;
	int				len;

	len = ft_intlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	nb = n;
	while (nb > 0 && len >= 0)
	{
		str[len--] = '0' + nb % 10;
		nb = nb / 10;
	}
	return (str);
}

int	ft_atoi(const char *str)
{
	int			nbr;
	int			neg;
	long int	result;

	nbr = 0;
	neg = 1;
	result = 0;
	while ((str[nbr] >= 9 && str[nbr] <= 13) || str[nbr] == 32)
		nbr++;
	if (str[nbr] == '+' || str[nbr] == '-')
	{
		if (str[nbr] == '-')
			neg *= -1;
		nbr++;
	}
	while (str[nbr] >= 48 && str[nbr] <= 57)
	{
		if (result * 10 + (str[nbr] - 48) < result)
			return (-2);
		result = result * 10 + (str[nbr] - 48);
		nbr++;
	}
	return ((result * neg));
}
