#include "libft.h"

int	numlen(long long num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		len++;
		num *= -1;
	}
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

char	*ft_itoa(long long n)
{
	long long	num;
	char		*str;
	int			idx;

	num = (long long)n;
	idx = numlen(num);
	str = (char *)malloc((idx + 1) * sizeof(char));
	if (!(str))
		return (0);
	str[0] = '0';
	str[idx--] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	while (num > 0)
	{
		str[idx--] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}
