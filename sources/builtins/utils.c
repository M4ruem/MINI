/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jghribi <jghribi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 13:50:36 by jghribi           #+#    #+#             */
/*   Updated: 2023/07/01 13:50:37 by jghribi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_handel(t_data *data)
{
	int	i;

	i = -1;
	ft_lstclear(data, &data->cmd_table_temp);
	while (data->data1.paths[++i])
		free(data->data1.paths[i]);
	free(data->data1.paths);
	i = 0;
	while (i < data->data2.lst_nbr - 1)
	{
		close(data->data3.fds[i][0]);
		close(data->data3.fds[i][1]);
		i++;
	}
	i = -1;
	while (data->data1.arg_tabl[++i])
		free(data->data1.arg_tabl[i]);
	free(data->data1.arg_tabl);
	error_handel_tow(data);
}

void	exekerror3(t_data *data)
{
	int	i;

	handle_directory_error(data);
	i = -1;
	while (data->data4.redir_file[++i])
	{
		if (access(data->data4.redir_file[i], F_OK) != 0)
		{
			write(2, "minishell: ", 12);
			write(2, data->data4.redir_file[i],
				ft_strlen(data->data4.redir_file[i]));
			write(2, ": No such file or directory\n", 28);
		}
		else if (access(data->data4.redir_file[i], R_OK) != 0)
		{
			write(2, "minishell: ", 12);
			write(2, data->data4.redir_file[i],
				ft_strlen(data->data4.redir_file[i]));
			write(2, ": Permission denied\n", 20);
		}
	}
	execkerror_utils(data);
	data->data5.last_error = 127;
}

void	exekerror2(t_data *data)
{
	int	i;

	i = -1;
	while (data->cmd_table->redir_file[++i])
	{
		if (access(data->cmd_table->redir_file[i], F_OK) != 0)
		{
			write(2, "minishell: ", 12);
			write(2, data->cmd_table->redir_file[i],
				ft_strlen(data->cmd_table->redir_file[i]));
			write(2, ": No such file or directory\n", 28);
		}
		else if (access(data->cmd_table->redir_file[i], R_OK) != 0)
		{
			write(2, "minishell: ", 12);
			write(2, data->cmd_table->redir_file[i],
				ft_strlen(data->cmd_table->redir_file[i]));
			write(2, ": Permission denied\n", 20);
		}
		error_handel(data);
		exit(0);
		data->data3.houna = 0;
	}
}

void	co_8(char *name, char *value, char **arg, t_data *data)
{
	name = ft_substr(arg[data->data4.f], 0, data->data4.e);
	if (arg[data->data4.f][data->data4.e] == '=' &&
		arg[data->data4.f][data->data4.e + 1])
		value = ft_substr(arg[data->data4.f], data->data4.e + 1, \
			ft_strlen(arg[data->data4.f]) - (data->data4.e + 1));
}

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}
