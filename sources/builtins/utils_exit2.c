/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jghribi <jghribi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 12:32:24 by jghribi           #+#    #+#             */
/*   Updated: 2023/07/01 12:32:27 by jghribi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execkerror_utils(t_data *data)
{
	int	i;

	data->data5.last_error = 1;
	data->data5.finale = 1;
	if (data->data4.is_built_in == 0)
		free_for_redir_fail(data);
	if (data->data4.is_built_in == 1)
	{
		if (data->data4.sit == 1)
		{
			i = -1;
			while (data->data1.arg_tabl[++i])
				free(data->data1.arg_tabl[i]);
			free(data->data1.arg_tabl);
		}
		else
			free(data->data1.arg_tabl);
	}
}

void	bin_exit_next(t_data *data, int flag)
{
	if (flag == 1)
	{
		free_exit_pipe(data);
		exit(1);
	}
	if (flag == 2)
	{
		free(data->data1.paths);
		ft_lstclear(data, &data->cmd_table);
		free(data->cmd_table);
		ft_env_lstclear(&data->env_table);
		ft_env_lstclear(&data->env_table_sorted);
		rl_clear_history();
		ft_continue_exit(data);
	}
}

void	error_handel_tow(t_data *data)
{
	int	i;

	ft_env_lstclear(&data->env_table);
	if (data->data3.fds != NULL)
	{
		i = -1;
		while (++i <= data->data2.lst_nbr)
			free(data->data3.fds[i]);
		free(data->data3.fds);
	}
	close(data->data5.stdin_save);
	close(data->data5.stdout_save);
	ft_close_for_fun();
}
