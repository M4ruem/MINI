/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:21:32 by cormiere          #+#    #+#             */
/*   Updated: 2023/05/29 15:21:38 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sig_handler_hd(int sig)
{
	if (sig == SIGINT)
	{
		g_sigint = 1;
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
		signal(SIGQUIT, handler2);
		printf("warning: here-document at line 1 \
				delimited by end-of-file (wanted `EOF')\n");
	}
	return (str2);
}

void	here_doc_fct(t_data *data, char *str)
{
	char	*file;
	int		fd;
	char	*str2;

	file = create_here_doc_file(data);
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	str2 = NULL;
	g_sigint = 0;
	signal(SIGINT, sig_handler_hd);
	rl_event_hook = check_rl;
	while (g_sigint != 1)
	{
		str2 = read_user_input();
		if (str2 == NULL)
			break ;
		if (str_diff(str, str2) == 0)
			break ;
		str2 = ft_search_and_change_env_var(data, str2);
		write(fd, str2, ft_strlen(str2));
		write(fd, "\n", 1);
	}
	close(fd);
	free(file);
	free(str2);
	g_sigint = 0;
}
