/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:37:43 by cormiere          #+#    #+#             */
/*   Updated: 2023/06/27 10:56:49 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

void	free_for_redir_fail(t_data *data)
{
	int i;

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
	if (data->data3.fds != NULL)
	{
		while (++i <= data->data2.lst_nbr)
			free(data->data3.fds[i]);
 		free(data->data3.fds);
	}
	i = -1;
	while (data->data1.arg_tabl[++i])
		free(data->data1.arg_tabl[i]);
	free(data->data1.arg_tabl);
	ft_env_lstclear(&data->env_table);
	close(data->data5.stdin_save);
	close(data->data5.stdout_save);
	ft_close_for_fun();
	exit(data->data5.last_error);
}

void	execkerror_utils(t_data *data)
{
	data->data5.last_error = 1;
	data->data5.finale = 1;
	if (data->data4.is_built_in == 0)
		free_for_redir_fail(data);
	if (data->data4.is_built_in == 1)
	{
		free(data->data1.arg_tabl);
		free(data->data5.str_f);
	}
}

void	free_for_exit(t_data *data, int x)
{
	int	i;

	i = -1;
	if (data->str_exit == 1)
	{
		if (data->data2.rdj != 0)
		{
			while (data->data4.redir_file[++i])
				free(data->data4.redir_file[i]);
		}
		free(data->data4.redir_file);
		free(data->data4.redir_type);
		free(data->data3.pcommand);
		free(data->cmd_table_temp);
		if (x == 0)
		{
//			free(data->data5.str_f);
		//	if (data->data1.arg_tabl != NULL)
		//		free(data->data1.arg_tabl);
		}
		else
		{
			if (data->data1.arg_tabl != NULL)
			{
				while (data->data1.arg_tabl[++i])
					free(data->data1.arg_tabl[i]);
				free(data->data1.arg_tabl);
			}
		}
	}
	ft_close_for_fun();
}

static void	ft_continue(t_data *data)
{
	int	len;

	if (data->close_need == 1)
	{
		close(data->data5.stdin_save);
		close(data->data5.stdout_save);
	}
	if (data->data4.nbr_save == 1)
	{
		if (is_number(data->data1.arg_tabl[1]) == 0
			|| ft_atoi(data->data1.arg_tabl[1]) == -2)
		{
			printf("\nnumeric argument required\n");
			free_for_exit(data, 1);
			exit(255);
		}
		len = ft_atoi((data->data1.arg_tabl[1])) % 256;
		free_for_exit(data, 1);
		exit(len);
	}
	if (data->data1.arg_tabl != NULL)
	{
		len = -1;
		while (data->data1.arg_tabl[++len])
			free(data->data1.arg_tabl[len]);
		free(data->data1.arg_tabl);
	}
	printf("\n");
	free_for_exit(data, 0);
	exit(EXIT_SUCCESS);
}

void	free_exit_pipe(t_data *data)
{
	int i;

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
	while (++i <= data->data2.lst_nbr)
		free(data->data3.fds[i]);
	free(data->data3.fds);
	i = -1;
	while (data->data1.arg_tabl[++i])
		free(data->data1.arg_tabl[i]);
	free(data->data1.arg_tabl);
	ft_env_lstclear(&data->env_table);
	close(data->data5.stdin_save);
	close(data->data5.stdout_save);
	ft_close_for_fun();
}

int	check_for_exit(t_data *data)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if (is_number(data->data1.arg_tabl[1]) == 1)
		return (0);
	while (data->data1.arg_tabl[i])
	{
			j++;
		i++;
	}
	if (i <= j)
		return (1);
	else
		return (0);

}

void	free_exit_argument(t_data *data)
{
	int i;

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
	data->data1.arg_tabl = NULL;
	ft_env_lstclear(&data->env_table);
	close(data->data5.stdin_save);
	close(data->data5.stdout_save);
	ft_close_for_fun();

}

void	bin_exit(t_data *data, int is_pipe)
{
	int	i;

	i = -1;
	if (data->data2.lst_nbr > 1)
	{
		if (is_pipe == 1)
		{
			free_exit_pipe(data);
			exit(1);
		}
	}
	if (data->data4.nbr_save > 1)
	{
		printf("exit: too many arguments\n");
		if (is_number(data->data1.arg_tabl[1]) == 0)
		{
			free_exit_argument(data);
			exit(2);
		}
	}
	if (!(data->data4.nbr_save > 1))
	{
		if (is_pipe == 0)
			printf("exit");
		while (data->data1.paths[++i])
			free(data->data1.paths[i]);
		free(data->data1.paths);
		ft_lstclear(data, &data->cmd_table);
		free(data->cmd_table);
		ft_env_lstclear(&data->env_table);
		ft_env_lstclear(&data->env_table_sorted);
		rl_clear_history();
		ft_continue(data);
	}
}
