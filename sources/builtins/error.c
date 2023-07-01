/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:37:15 by cormiere          #+#    #+#             */
/*   Updated: 2023/07/01 09:00:28 by jghribi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/stat.h>

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
	if (parserror2(nbr, data) == -1)
		return (-1);
	if (nbr == 3)
	{
		write(2, "Syntax error\n", 14);
		data->data5.last_error = 2;
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

void	print_command_not_found(t_data *data)
{
	int	i;

	i = -1;
	if (data->data5.is_pipe == 1)
	{
		printf("%s : Command not found\n", data->cmd_table->cmd);
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
	if (data->cmd_table->cmd)
		printf("%s : Command not found\n", data->cmd_table->cmd);
	else
		write(2, "Command not found\n", 19);
	data->data5.last_error = 127;
}

void	handle_directory_error(t_data *data)
{
	if (data->cmd_table->cmd == NULL)
		return ;
		
	/*struct stat st;
	if (access(data->cmd_table->cmd, F_OK) == 0){
		if( stat( data->cmd_table->cmd, &st) != -1) // Check the return value of stat
		{
		    	if( S_ISREG( st.st_mode ) == 0 ){
				printf( "%s is a directory\n", data->cmd_table->cmd );
				data->data5.last_error = 126;
			}
		 	else if (access(data->cmd_table->cmd, X_OK) != 0){
				printf( "%s access denied\n", data->cmd_table->cmd );
				data->data5.last_error = 126;
			}
		}
	}
	//e/lse{
		//printf( "zsh: no such file or directory: %s\n", data->cmd_table->cmd );
		//data->data5.last_error = 127;
	//}
	
	return;*/
	if (access(data->cmd_table->cmd, F_OK) == 0 && data->data4.unset == 1)
	{
		if (access(data->cmd_table->cmd, X_OK) == 0)
		{
			printf("%s : Is a directory\n", data->cmd_table->cmd);
			data->data5.last_error = 126;
			return ;
		}
	}
	else if (access(data->cmd_table->cmd, X_OK) == 0 && data->data4.unset == 1)
	{
		printf("%s : Is a directory\n", data->cmd_table->cmd);
		data->data5.last_error = 126;
		return ;
	}
}

void	exekerror(int nbr, t_data *data)
{
	(void)data;
	handle_directory_error(data);
	if (nbr == 2)
		exekerror_utils(data);
	if (nbr == 3)
	{
		if (data->data3.houna == 1)
			exekerror2(data);
		else
			exekerror2(data);
		data->data5.last_error = 1;
	}
	if (nbr == 4)
	{
		write(2, "No command after pipe\n", 23);
		data->data5.last_error = 1;
	}
}
