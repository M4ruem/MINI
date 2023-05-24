/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:37:15 by cormiere          #+#    #+#             */
/*   Updated: 2023/05/24 17:07:07 by jghribi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	syntax_error(t_data *data)
{
	write(2, "Syntax error after > < >> <<\n", 30);
	data->data5.last_error = 258;
	free(data->data4.redir_file);
	free(data->data4.redir_type);
	free(data->data3.pcommand);
	ft_lstclear(&data->cmd_table);
	return (-1);
}

int	parserror(int nbr, t_data *data)
{
	if (nbr == 1)
	{
		write(2, "syntax error near unexpected token `|'\n", 40);
		data->data5.last_error = 258;
		return (-1);
	}
	if (nbr == 2)
	{
		write(2, "Error quote not closed\n", 24);
		data->data5.last_error = 1;
		return (-1);
	}
	if (nbr == 3)
	{
		write(2, "Syntax error\n", 14);
		data->data5.last_error = 258;
		return (-1);
	}
	if (nbr == -2)
		return (syntax_error(data));
	if (nbr == -3)
		write(2, "Malloc went wrong", 17);
	if (nbr == -3)
		exit(0);
	return (0);
}

void	exekerror(int nbr, t_data *data)
{
	int	i;

	i = 0;
	(void)data;
	
	printf("%s : Is a diretory\n" ,data->cmd_table->cmd);
	if (nbr == 2)
	{
		while (i <= data->data4.nbr_save + 1)
			free(data->data1.arg_tabl[i++]);
		free(data->data1.arg_tabl);
		data->data5.last_error = 127;
		if (data->cmd_table->cmd)
			printf("%s : Command not found\n", data->cmd_table->cmd);
		else
			write(2, "Command not found\n", 19);
		if (data->data5.is_pipe == 1)
			exit(127);
	}
	if (nbr == 3)
	{
		write(2, "Error with redirections\n", 25);
		data->data5.last_error = 1;
	}
	if (nbr == 4)
	{
		write(2, "No command after pipe\n", 23);
		data->data5.last_error = 1;
	}
}
