#include "../../include/minishell.h"

void	error_handel(t_data *data)
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

void	exekerror3(t_data *data)
{
	int i;
	
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
	int i;
	
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
