#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	idx;

	if (!s || !f)
		return ;
	idx = 0;
	while (s[idx] != '\0')
	{
		f(idx, &s[idx]);
		idx++;
	}
}
