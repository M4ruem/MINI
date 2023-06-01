/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:37:43 by cormiere          #+#    #+#             */
/*   Updated: 2023/05/23 19:04:55 by cormiere         ###   ########.fr       */
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


void	bin_exit(t_data *data, int is_pipe)
{
	int i;

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
		free(data->cmd_table);
		ft_env_lstclear(&data->env_table);
		ft_env_lstclear(&data->env_table_sorted);
		rl_clear_history();
		if (data->data4.nbr_save == 1)
		{
			if (is_number(data->data1.arg_tabl[1]) == 0
				|| ft_atoi(data->data1.arg_tabl[1]) == -2)
			{
				printf(" numeric argument required\n");
				exit(255);
			}
			exit(ft_atoi((data->data1.arg_tabl[1])) % 256);
		}
		printf("\n");
		exit(EXIT_SUCCESS);
	}
}
