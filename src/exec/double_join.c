#include "../minishell.h"

char	*double_strjoin(char *start, char *middle, char *end)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(start, middle);
	if (!tmp)
		ft_error("malloc");
	result = ft_strjoin(tmp, end);
	if (!result)
		ft_error("malloc");
	free(tmp);
	return (result);
}
