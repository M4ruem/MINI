/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:37:15 by cormiere          #+#    #+#             */
/*   Updated: 2023/06/16 13:04:20 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	syntax_error(t_data *data)
{
	write(2, "Syntax error after > < >> <<\n", 30);
	data->data5.last_error = 2;
	free(data->data4.redir_file);
	free(data->data4.redir_type);
	free(data->data3.pcommand);
	ft_lstclear(data, &data->cmd_table);
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
	if (nbr == 6)
	{
		printf("here_doc");
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

static void	print_command_not_found(t_data *data)
{
	int	i;

	i = -1;
	if (data->cmd_table->cmd)
		printf("%s : Command not found\n", data->cmd_table->cmd);
	else
		write(2, "Command not found\n", 19);
	if (data->data5.is_pipe == 1)
	{
		while (data->data1.paths[++i])
			free(data->data1.paths[i]);
		free(data->data1.paths);
		i = 0;
		free_fds_error(data);
		ft_lstclear(data, &data->cmd_table_temp);
		free(data->cmd_table_temp);
		close(data->data5.stdin_save);
 		close(data->data5.stdout_save);
		ft_env_lstclear(&data->env_table);
		free(data->data3.fds);
		exit(127);
	}
}

static void	handle_directory_error(t_data *data)
{
	if (access(data->cmd_table->cmd, F_OK) == 0)
		return ;
	else if (access(data->cmd_table->cmd, X_OK) == 0)
	{	
		printf("%s : Is a directory\n", data->cmd_table->cmd);
		data->data5.last_error = 126;
		return ;
	}
}

void	error_handel(t_data *data, int key)
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
	ft_env_lstclear(&data->env_table);
	if (key == 1)
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
void	exekerror(int nbr, t_data *data)
{
	int	i;

	(void)data;
	i = 0;

	handle_directory_error(data);
	if (nbr == 2)
	{
		while (i <= data->data4.nbr_save + 1)
			free(data->data1.arg_tabl[i++]);
		free(data->data1.arg_tabl);
		data->data5.last_error = 127;
		if (data->hell == 0)
			print_command_not_found(data);
		close(data->data5.stdin_save);
 		close(data->data5.stdout_save);
	}
	if (nbr == 3)
	{
//		write(2, "Error with redirections\n", 25);
		if (data->data3.houna == 1)
		{
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
				error_handel(data ,1);
				exit(0);
				data->data3.houna = 0;
			}
		}
		else
		{
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
		}
//		else
//		{	
///			if (data->data5.is_pipe == 1)
///				error_handel(data , 0);
//		}
	//	if (data->data5.is_pipe == 1)
	//		exit(data->data5.last_error);
		data->data5.last_error = 1;
	}
	if (nbr == 4)
	{
		write(2, "No command after pipe\n", 23);
		data->data5.last_error = 1;
	}
	if (nbr != 4 && nbr != 3 && nbr != 2)
		data->data5.last_error = 0;
}
