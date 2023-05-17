#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			idx;
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;

	if (n == 0 || dst == src)
		return (dst);
	idx = 0;
	dst_ptr = (unsigned char *)dst;
	src_ptr = (unsigned char *)src;
	while (idx < n)
	{
		dst_ptr[idx] = src_ptr[idx];
		idx++;
	}
	return (dst);
}
