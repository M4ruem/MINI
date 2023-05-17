#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	idx;
	size_t	s_len;
	char	*ptr;

	idx = 0;
	s_len = ft_strlen(s) + 1;
	ptr = 0;
	while (idx < s_len)
	{
		if (s[idx] == (char)c)
			ptr = (char *)s + idx;
		idx++;
	}
	return (ptr);
}
