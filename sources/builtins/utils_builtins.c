#include "../../include/minishell.h"

void	export_msg(char *str ,t_data *data)
{
	write(2, "Minisheru: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": not a valid identifier\n", 25);
	data->data5.last_error = 1;
}

int con(char **arg, t_data *data, int key)
{
	if (key == 1)
	{
		if (arg[data->data4.f][data->data4.e])
				data->data4.e++;
			if (data->data3.export_num > 0)
				export_msg(arg[data->data4.f], data);
	}
	return(0);
}

int	continue_6(char **arg, t_data *data, int key)
{
	if (key == 0)
	{
		while (ft_isalnum(arg[data->data4.f][data->data4.e]) == 1 \
				|| arg[data->data4.f][data->data4.e] == '_')
		{
			data->data3.export_num++;
			data->data4.e++;
		}
		if ((arg[data->data4.f][data->data4.e] == '=' || arg[data->data4.f] \
				[data->data4.e] == '\0') && data->data4.e > 0)
		{
			ft_correct_env_name(arg, data);
			return (1);
		}
		else
		{
			ft_wrong_env_name(arg, data);
			return (1);
		}
	}
	return (con(arg, data, key));
}
