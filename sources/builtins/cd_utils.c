
#include "../../include/minishell.h"

int	count_tabel(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
