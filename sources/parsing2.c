#include "../include/minishell.h"

void	quotes_switch(t_data *data, char *str, int i)
{
	if (str[i] == '\'' && data->dquote == 0)
	{
		if (data->squote == 0)
			data->squote = 1;
		else
			data->squote = 0;
	}
	if (str[i] == '"' && data->squote == 0)
	{
		if (data->dquote == 0)
			data->dquote = 1;
		else
			data->dquote = 0;
	}
}
