#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*b_ptr;
	size_t			idx;

	b_ptr = (unsigned char *)b;
	idx = 0;
	while (idx < len)
		b_ptr[idx++] = (unsigned char)c;
	return (b);
}
