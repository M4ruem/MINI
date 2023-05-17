#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			idx;
	unsigned char	*ptr;

	idx = 0;
	ptr = (unsigned char *)s;
	while (idx < n)
	{
		if (ptr[idx] == (unsigned char)c)
			return ((void *)(s + idx));
		idx++;
	}
	return (0);
}
