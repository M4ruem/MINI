/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:53:34 by cormiere          #+#    #+#             */
/*   Updated: 2023/05/29 14:55:11 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**allocate_tabl(t_data **data)
{
	char	**tabl;

	tabl = malloc(sizeof(char *) * ((*data)->data2.nbr + 2));
	if (!tabl)
		exit(EXIT_FAILURE);
	tabl[(*data)->data2.nbr + 1] = NULL;
	return (tabl);
}

char	**fill_tabl(t_data **data, char *str, char **tabl)
{
	int	i;

	i = ft_strlen(str) - 1;
	tabl = put_cmd_in_arg(i, *data, str, tabl);
	return (tabl);
}

void	free_if_execv_fail(t_data *data)
{
	int	i;

	ft_lstclear(data, &data->cmd_table);
	free(data->data4.redir_file);
	free(data->data4.redir_type);
	free(data->cmd_table_temp);
	free(data->data3.pcommand);
	ft_env_lstclear(&data->env_table);
	i = -1;
	while (data->data1.arg_tabl[++i])
		free(data->data1.arg_tabl[i]);
	free(data->data1.arg_tabl);
	i = -1;
	while (data->data1.paths[++i])
		free(data->data1.paths[i]);
	free(data->data1.paths);
}
