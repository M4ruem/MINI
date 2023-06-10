/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:38:23 by cormiere          #+#    #+#             */
/*   Updated: 2023/05/29 14:21:56 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_lexer2(t_data *data, char *str)
{
	while (str[data->data2.li])
	{
		data->data2.ly = data->data2.li;
		quotes_switch(data, str, data->data2.li);
		if (str[data->data2.li] == '|' && data->data1.squote == 0
			&& data->data1.dquote == 0)
		{
			data->data2.ly++;
			while (str[data->data2.ly] && (str[data->data2.ly] == ' '
					|| str[data->data2.ly] == '\n'))
				data->data2.ly++;
			if (str[data->data2.ly] == '|')
				return (3);
			data->data3.rdi = 0;
			data->data3.lexer_error = ft_parser(&str[data->data3.lexer_start],
					data, data->data2.li - data->data3.lexer_start);
			if (data->data3.lexer_error != 0)
				return (data->data3.lexer_error);
			ft_addpipe(data);
			data->data3.lexer_start = data->data2.li + 1;
			data->data1.r_tabl = 0;
		}
		data->data2.li++;
	}
	return (0);
}

int finsh_stupid(t_data *data, char *str, int x, int j)
{
	int i;
	int len;

	len  = ft_strlen(str);
	i = 0;
	while (str[i] == '/')
		i++;
	if (i == len)
		return (1);
	while (str[i])
	{
		if (str[i] == '/')
			x++;
		if (str[i] == '.')
			j++;
		i++;
	}
	if (x + j == len)
	{
		printf("bash: %s: Is a directory\n", str);
		data->data5.last_error = 126;
		return (1);
	}
	return (0);

}

int	stupid_problem(t_data *data, char *str)
{
	int i;
	int j;
	int x;
	int len;
	
	i = 0;
	x = 0;
	j = 0;
	len = ft_strlen(str);
	if (str == NULL)
		return (2);
	if (ft_strncmp(str, ".") == 0)
	{
		printf("Minisheru: .: filename argument required]\n");
		printf(".: usage: . filename [arguments]\n");
		data->data5.last_error = 2;
		return (1);
	}
	while  (str[i] == '.')
		i++;
	if (i == len)
	{
		printf("%s: command not found\n", str);	
		data->data5.last_error = 127;
		return (1);
	}
	if (finsh_stupid(data, str, x, j) == 1)
		return (1);
	return (0);
}

int	ft_lexer(char *str, t_data *data)
{
	data->data1.squote = 0;
	data->data1.dquote = 0;
	data->data1.r_tabl = 0;
	data->data2.li = 0;
	data->data3.lexer_start = 0;
	data->data2.ly = 0;
	while (str[data->data2.ly] && (str[data->data2.ly] == ' '
			|| str[data->data2.ly] == '\n' || str[data->data2.ly] == '\t'))
		data->data2.ly++;
	if (str[data->data2.ly] == '|')
		return (1);
	data->data3.lexer_error = ft_lexer2(data, str);
	if (data->data3.lexer_error != 0)
		return (data->data3.lexer_error);
	if (data->data1.squote == 1 || data->data1.dquote == 1)
		return (2);
	data->data3.rdi = 0;
	data->data3.lexer_error = ft_parser(&str[data->data3.lexer_start],
			data, data->data2.li - data->data3.lexer_start);
	if (data->data3.lexer_error != 0)
		return (data->data3.lexer_error);
	return (0);
}

void	ft_addpipe(t_data *data)
{
	char	*str;
	int		*redir_type;
	char	**redir_file;

	redir_type = (int *)malloc(sizeof(int) * 2);
	redir_file = malloc(sizeof(char *) * 2);
	str = malloc(sizeof(char) * 2);
	if (!(str) || !(redir_type) || !(redir_file))
		exit(EXIT_FAILURE);
	redir_type[0] = 5;
	redir_file[0] = NULL;
	str[0] = '|';
	str[1] = '\0';
	ft_lstadd_back(&data->cmd_table, ft_lstnew(str, redir_type, redir_file));
}

int	ft_parser2(t_data *data, char *str)
{
	while (str[data->data3.rdi] == ' ' || str[data->data3.rdi] == '\t')
		data->data3.rdi++;
	while (str[data->data3.rdi])
	{
		quotes_switch(data, str, data->data3.rdi);
		if ((str[data->data3.rdi] == '>' || str[data->data3.rdi] == '<')
			&& data->data1.squote == 0 && data->data1.dquote == 0)
		{
			data->data3.pskip = redir_parsing(str, data);
			if (data->data3.pskip < 0)
				return (data->data3.pskip);
			data->data3.rdi = data->data3.rdi + data->data3.pskip;
		}
		else
			ft_continue2(data, str);
	}
	return (0);
}

int	ft_parser(char *str, t_data *data, int end)
{
	if (str[end])
		str[end] = '\0';
	
	data->data3.pcommand = NULL;
	data->data4.tabl_s = count_redir(str, data);
	if (data->data4.tabl_s == -1)
		return (3);
	data->data4.redir_type = (int *)malloc(sizeof(int) \
	* (data->data4.tabl_s + 1));
	data->data4.redir_file = malloc(sizeof(char *) * (data->data4.tabl_s + 1));
	if (!(data->data4.redir_type) || !(data->data4.redir_file))
		exit(EXIT_FAILURE);
	while (data->data3.rdi < data->data4.tabl_s + 1)
	{
		data->data4.redir_type[data->data3.rdi] = 0;
		data->data4.redir_file[data->data3.rdi] = NULL;
		data->data3.rdi++;
	}
	data->data3.rdi = 0;
	data->data4.parser_error = ft_parser2(data, str);
	if (data->data4.parser_error != 0)
		return (data->data4.parser_error);
	ft_continue3(data);
	return (0);
}
