#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	idx;

	src_len = ft_strlen(src);
	idx = 0;
	if (dstsize > 0)
	{
		while (src[idx] != '\0' && idx + 1 < dstsize)
		{
			dst[idx] = src[idx];
			idx++;
		}
		dst[idx] = '\0';
	}
	return (src_len);
}
