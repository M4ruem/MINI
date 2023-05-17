#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	idx;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	idx = 0;
	if (dst_len + 1 > dstsize)
		return (src_len + dstsize);
	while (src[idx] != '\0' && dst_len + idx + 1 < dstsize)
	{
		dst[dst_len + idx] = src[idx];
		idx++;
	}
	dst[dst_len + idx] = '\0';
	return (dst_len + src_len);
}
