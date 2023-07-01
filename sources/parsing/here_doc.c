/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:21:32 by cormiere          #+#    #+#             */
/*   Updated: 2023/06/21 19:41:46 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_data *g_data;

void free_child(t_data *data)
{
	int i;

	i = -1;
	while (data->data1.paths[++i])
		free(data->data1.paths[i]);
	free(data->data1.paths);
	i = -1;
	while (data->data4.redir_file[++i])
		free(data->data4.redir_file[i]);
	free(data->data4.redir_file);
	free(data->data4.redir_type);
	free(data->cmd_table);
	ft_env_lstclear(&data->env_table);
	ft_env_lstclear(&data->env_table_sorted);
	ft_close_for_fun();
}

void	sigint_handler_parent()
{
	printf("\n");
}

void	sigint_handler_child(int sig)
{
	if (sig == SIGINT)
	{
		free_child(g_data);
		free(g_data->data3.file);
		close(g_data->data3.fd);
		exit(6);
	}
}

static char	*create_here_doc_file(t_data *data)
{
	char	*file;
	char	character;

	character = (char)(data->data1.here_doc_nbr + 97);
	file = ft_strjoin_c("/tmp/.here_doc", character);
	return (file);
}

static char	*read_user_input(void)
{
	char	*str2;

	str2 = readline("> ");
	if (str2 == NULL)
	{
		printf("warning: here-document at line 1 ");
		printf("delimited by end-of-file (wanted `EOF')\n");
	}
	return (str2);
}

/*int	here_doc_fct(t_data *data, char *str)
{
    char *file;
    int fd;
    char *str2;

    fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
    str2 = NULL;
    g_sigint = 0;
    while (1)
    {
        if (str2 == NULL)
           break;
        if (str_diff(str, str2) == 0)
            break;
        str2 = ft_search_and_change_env_var(data, str2);
        write(fd, str2, ft_strlen(str2));
        write(fd, "\n", 1);
        free(str2);
    }
    close(fd);
    free(file);
    g_sigint = 0;
	return (0);
}*/


void	child_process(t_data *data, char *str)
{
	char	*str2;

	str2 = NULL;
	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, SIG_IGN);	
	while (1)
	{
    	str2 = read_user_input();
		if (str2 == NULL)
		{
			free(str2);
			free(data->data3.file);
			close(data->data3.fd);
			free_child(data);
			exit(0);
		}
		str2 = ft_search_and_change_env_var(data, str2);
		if (str_diff(str, str2) == 0)
		{
			free(str2);
			free(data->data3.file);
			close(data->data3.fd);
			free_child(data);
			exit(0);
		}
		write(data->data3.fd, str2, ft_strlen(str2));
		write(data->data3.fd, "\n", 1);
		free(str2);
	}
	close(data->data3.fd);
	free(str2);
}

int	here_doc_fct(t_data *data, char *str)
{
	int		pid;
	
	g_data = data;
    data->data3.file = create_here_doc_file(data);
	data->data3.fd = open(data->data3.file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0)
	{	
		child_process(data, str);
	}
	else if (pid > 0)
	{
		signal(SIGINT, sigint_handler_parent);
		wait(&pid);
//		if (g_sigint == 2)
//			return (6);
	if (WIFEXITED(pid))
	{
		int exit_s = WEXITSTATUS(pid);
			if (exit_s == 6)
				return (6);
	}
//	data->data1.ctr_c_herd = 1;
	}
	return (0);
}
