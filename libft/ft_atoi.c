#include "libft.h"
#include <limits.h>

int	ft_isspace_or_issign(const char *str, int *sign)
{
	int	idx;

	idx = 0;
	while (str[idx] == ' ' || str[idx] == '\f' || str[idx] == '\n'
		|| str[idx] == '\r' || str[idx] == '\t' || str[idx] == '\v')
		idx++;
	if (str[idx] == '+' || str[idx] == '-')
	{
		if (str[idx] == '-')
			(*sign) *= (-1);
		idx++;
	}
	return (idx);
}

int	ft_atoi(const char *str)
{
	unsigned long	num;
	int				sign;
	char			*ptr;

	num = 0;
	sign = 1;
	ptr = (char *)str;
	ptr += ft_isspace_or_issign(str, &sign);
	while (ft_isdigit(*ptr) == 1 && *ptr != '\0')
	{
		num += (*ptr) - '0';
		if (ft_isdigit(*(ptr + 1)) == 1 && *(ptr + 1) != '\0')
			num *= 10;
		ptr++;
	}
	if (num > LONG_MAX)
	{
		if (sign == 1)
			return (-1);
		else
			return (0);
	}
	return ((int)num * sign);
}
