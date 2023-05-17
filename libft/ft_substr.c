#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*substr;
	size_t	sub_idx;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (s_len <= start)
		substr = (char *)malloc(1 * sizeof(char));
	else if (s_len - start >= len)
		substr = (char *)malloc((len + 1) * sizeof(char));
	else
		substr = (char *)malloc((s_len - start + 1) * sizeof(char));
	if (!(substr))
		return (0);
	sub_idx = 0;
	while (s[start] != '\0' && sub_idx < len && start < s_len)
		substr[sub_idx++] = s[start++];
	substr[sub_idx] = '\0';
	return (substr);
}
