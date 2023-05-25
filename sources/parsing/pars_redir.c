/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:38:19 by cormiere          #+#    #+#             */
/*   Updated: 2023/05/25 12:47:48 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_rl(void)
{
	if (g_sigint == 1)
		rl_done = 1;
	return (0);
}

void	sig_handler_hd(int sig)
{
	if (sig == SIGINT)
	{
		g_sigint = 1;
	}
}

void	here_doc_fct(t_data *data, char *str)
{
	char	*file;
	int		fd;
	char	*str2;

	g_sigint = 0;
	str2 = NULL;
	file = ft_strjoin_c("/tmp/.here_doc", \
	(char)(data->data1.here_doc_nbr + 97));
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(file);
	signal(SIGINT, sig_handler_hd);
	rl_event_hook = check_rl;
	while (g_sigint != 1)
	{
		str2 = readline("> ");
		if (str2 == NULL)
		{
			write(fd, "\n", 1);
			break ;
		}
		//	signal(SIGQUIT, handler2);
		//	free(str2);
		//	break;
		//}
		//signal(SIGINT, handler2);
		//str2 = ft_search_and_change_env_var(data, str2);
		if (str_diff(str, str2) == 0)
			break ;
		str2 = ft_search_and_change_env_var(data, str2);
		write(fd, str2, ft_strlen(str2));
		write(fd, "\n", 1);
		free(str2);
	}
	close(fd);
	free(str2);
	g_sigint = 0;
}

int	redir_parsing2(t_data *data, char *str)
{
	data->data2.rdj = data->data3.rdi;
	if (str[data->data2.rdj] == '>' && str[data->data2.rdj + 1] == '>')
	{
		data->data4.redir_type[data->data1.r_tabl] = 1;
		data->data2.rdj++;
	}
	else if (str[data->data2.rdj] == '>')
		data->data4.redir_type[data->data1.r_tabl] = 2;
	else if (str[data->data2.rdj] == '<' && str[data->data2.rdj + 1] == '<')
	{
		data->data4.redir_type[data->data1.r_tabl] = 3;
		data->data2.rdj++;
	}
	else if (str[data->data2.rdj] == '<')
		data->data4.redir_type[data->data1.r_tabl] = 4;
	data->data2.rdj++;
	while (str[data->data2.rdj] == ' ')
		data->data2.rdj++;
	return (0);
}

int	ft_is_chr(char c, t_data *data)
{
	if ((c == 33 || c == 35 || c == 42 || c == 40 || c == 41
			|| c == 59 || c == 47 || c == 63 || c == 124)
		&& data->data1.squote == 0 && data->data1.dquote == 0)
		return (1);
	return (0);
}

int	redir_parsing(char *str, t_data *data)
{
	data->data4.rd_error = redir_parsing2(data, str);
	if (data->data4.rd_error != 0)
		return (data->data4.rd_error);
	while (str[data->data2.rdj])
	{
		quotes_switch(data, str, data->data2.rdj);
		if ((str[data->data2.rdj] == ' ' || str[data->data2.rdj] == '<'
				|| str[data->data2.rdj] == '>') && data->data1.squote == 0
			&& data->data1.dquote == 0)
			break ;
		if (ft_is_chr(str[data->data2.rdj], data) == 1)
			return (-2);
		data->data4.redir_file[data->data1.r_tabl] = ft_strmjoin(data->data4. \
		redir_file[data->data1.r_tabl], str[data->data2.rdj]);
		data->data2.rdj++;
	}
	if (!(data->data4.redir_file[data->data1.r_tabl]))
		return (-2);
	data->data4.redir_file = rm_quote(data->data4.redir_file, data);
	if (str[data->data3.rdi] == '<' && str[data->data3.rdi + 1] == '<')
		here_doc_fct(data, data->data4.redir_file[data->data1.r_tabl]);
	data->data1.r_tabl = data->data1.r_tabl + 1;
	while (str[data->data2.rdj] == ' ')
		data->data2.rdj++;
	return (data->data2.rdj - data->data3.rdi);
}

int	count_redir(char *str, t_data *data)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		quotes_switch(data, str, i);
		if ((str[i] == '>' || str[i] == '<') && data->data1.squote == 0
			&& data->data1.dquote == 0)
		{
			if (str[i] == '>' && str[i + 1] == '>')
				i++;
			if (str[i] == '<' && str[i + 1] == '<')
				i++;
			if (str[i] == '>' && str[i + 1] == '<')
				return (-1);
			if (str[i] == '<' && str[i + 1] == '>')
				return (-1);
			count++;
			if (str[i + 1] == '>' && str[i + 1] == '<')
				return (-1);
		}
	}
	return (count);
}
