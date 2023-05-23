/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:38:36 by cormiere          #+#    #+#             */
/*   Updated: 2023/05/23 18:14:12 by jghribi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_term(int save)
{
	struct termios			t;
	static int				ifsave;
	static struct termios	saved;

	if (!ifsave)
	{
		tcgetattr(STDOUT_FILENO, &saved);
		ifsave = 1;
	}
	tcgetattr(STDOUT_FILENO, &t);
	t.c_lflag &= ~ECHOCTL;
	t.c_cc[VQUIT] = 0;
	if (save == 1)
		tcsetattr(STDOUT_FILENO, TCSANOW, &saved);
	else
		tcsetattr(STDOUT_FILENO, TCSANOW, &t);
}

int	str_is_empty(char *str)
{
	int	i;

	i = 0;
	if (str[i])
		return (1);
	return (0);
}

void	ft_free_all(t_data *data)
{
	int	i;

	i = -1;
	while (data->paths[++i])
		free(data->paths[i]);
	close(data->stdin_save);
	close(data->stdout_save);
	free(data->paths);
	free(data->main_str);
}

void	exec_cmds_two(t_data *data)
{
	while (data->exec_i < data->lst_nbr - 1)
	{
		close(data->fds[data->exec_i][0]);
		close(data->fds[data->exec_i][1]);
		data->exec_i++;
	}
	data->exec_i = 0;
	close(data->stdin_save);
	close(data->stdout_save);
}
