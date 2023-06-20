/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:37:43 by cormiere          #+#    #+#             */
/*   Updated: 2023/06/16 13:04:08 by cormiere         ###   ########.fr       */
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

void	execkerror_utils(t_data *data)
{
	write(2, "Error with redirections\n", 25);
	data->data5.last_error = 1;
	data->data5.finale = 1;
	free_if_execv_fail(data);
}

void	free_for_exit(t_data *data, int x)
{
	int	i;

	i = -1;
	if (data->str_exit == 1)
	{
		free(data->data4.redir_file);
		free(data->data4.redir_type);
		free(data->data3.pcommand);
		free(data->cmd_table_temp);
		if (x == 0)
		{
			free(data->data5.str_f);
			free(data->data1.arg_tabl);
		}
		else
		{
			while (data->data1.arg_tabl[++i])
				free(data->data1.arg_tabl[i]);
			free(data->data1.arg_tabl);
		}
	}
}

static void	ft_continue(t_data *data)
{
	int	len;

	if (data->data4.nbr_save == 1)
	{
		if (is_number(data->data1.arg_tabl[1]) == 0
			|| ft_atoi(data->data1.arg_tabl[1]) == -2)
		{
			free_for_exit(data, 1);
			printf(" numeric argument required\n");
			exit(255);
		}
		len = ft_atoi((data->data1.arg_tabl[1])) % 256;
		free_for_exit(data, 1);
		exit(len);
	}
	free_for_exit(data, 0);
	printf("\n");
	exit(EXIT_SUCCESS);
}

void	bin_exit(t_data *data, int is_pipe)
{
	int	i;

	i = -1;
	if (data->data4.nbr_save > 1)
		printf("exit: too many arguments\n");
	if (data->data4.nbr_save > 1)
		if (is_pipe == 1)
			exit(1);
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
