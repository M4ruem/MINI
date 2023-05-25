/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:37:22 by cormiere          #+#    #+#             */
/*   Updated: 2023/05/23 19:16:41 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_one_cmd(t_data *data, char **env)
{
	int	pid;

	pid = 0;
	data->data4.bin_nbr = 0;
	data->data1.arg_tabl = get_cmd(data);
	if (ft_is_builtin(data->data1.arg_tabl[0]) == 0)
	{
		if (built_in(data, env, data->data4.bin_nbr) != 0)
			return (5);
		return (0);
	}
	if (put_path(data) == 2)
		return (2);
	pid = fork();
	if (pid == 0)
		if (cmd_redir(data, env, 0) != 0)
			return (3);
	wait_loop(data);
	if (access("/tmp/.here_doca", F_OK) == 0)
		unlink("/tmp/.here_doca");
	pid = 0;
	while (pid <= data->data4.nbr_save + 1)
		free(data->data1.arg_tabl[pid++]);
	free(data->data1.arg_tabl);
	return (0);
}

int	get_argnbr(char *str, t_data *data)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	data->data1.squote = 0;
	data->data1.dquote = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		quotes_switch(data, str, i);
		if (str[i] == ' ' && data->data1.squote == 0 && data->data1.dquote == 0)
		{
			nbr++;
			while (str[i] == ' ' && data->data1.squote == 0 && \
				data->data1.dquote == 0)
				i++;
		}
		else
			i++;
	}
	return (nbr);
}

char	**put_cmd_in_arg(int i, t_data *data, char *str, char **tabl)
{
	while (i > 0)
	{
		quotes_switch(data, str, i);
		if (str[i] == ' ' && data->data1.squote == 0 && \
			data->data1.dquote == 0)
		{
			tabl[data->data2.nbr] = ft_malloc_str(&str[i + 1]);
			while (str[i] == ' ' && data->data1.squote == 0 && \
				data->data1.dquote == 0)
				i--;
			str[i + 1] = '\0';
			data->data2.nbr--;
		}
		else
			i--;
	}
	tabl[data->data2.nbr] = ft_malloc_str(str);
	tabl = rm_quote(tabl, data);
	return (tabl);
}

char	**get_cmd(t_data *data)
{
	char	*str;
	char	**tabl;
	int		i;

	str = data->cmd_table->cmd;
	str = ft_strtrim(str, " ");
	data->data2.nbr = get_argnbr(str, data);
	i = strlen(str) - 1;
	if (i == -1)
		i = 0;
	if (str[i] == ' ' && data->data1.squote == 0
		&& data->data1.dquote == 0)
	{
		data->data2.nbr--;
		while (str[i] == ' ' && data->data1.squote == 0
			&& data->data1.dquote == 0)
			i--;
		str[i + 1] = '\0';
	}
	data->data4.nbr_save = data->data2.nbr;
	tabl = malloc(sizeof(char *) * (data->data2.nbr + 2));
	if (!tabl)
		exit(EXIT_FAILURE);
	tabl[data->data2.nbr + 1] = NULL;
	tabl = put_cmd_in_arg(i, data, str, tabl);
	return (tabl);
}
