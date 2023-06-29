/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:35:51 by cormiere          #+#    #+#             */
/*   Updated: 2023/05/28 10:00:56 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int count_tabel(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	bin_cd(t_data *data)
{
	int		error;
	char 	*home;
	char	cwd[PATH_MAX];

	error = 0;
	data->data5.last_error = 0;
	if (count_tabel(data->data1.arg_tabl) > 2)
	{
		printf("Minisheru: cd: too many arguments\n");
		data->data5.last_error = 1;
		return ;
	}
	if (!data->data1.arg_tabl[1])
	{
		home = ft_chr_var_env(data, "HOME");
		if (home != NULL)
			error = chdir(ft_chr_var_env(data, "HOME"));
		if (error != 0 || home == NULL)
			printf("minishell: cd: No PATH found\n");
		if (error != 0)
			data->data5.last_error = 1;
		ft_update_var_env(data, "OLDPWD", ft_chr_var_env(data, "PWD"));
		ft_update_var_env(data, "PWD", ft_chr_var_env(data, "HOME"));
	}
	else
	{
		error = chdir(data->data1.arg_tabl[1]);
		if (error != 0)
		{
			if (access(data->data1.arg_tabl[1], F_OK) != 0)
				printf("minishell: cd: %s: No such file or directory\n", \
					data->data1.arg_tabl[1]);
			else if (access(data->data1.arg_tabl[1], R_OK) != 0)
				printf("minishell: cd: %s: Permission denied\n", \
					data->data1.arg_tabl[1]);
		}
		if (error != 0)
			data->data5.last_error = 1;
		ft_update_var_env(data, "OLDPWD", ft_chr_var_env(data, "PWD"));
		ft_update_var_env(data, "PWD", getcwd(cwd, sizeof(cwd)));
	}
}

char	*ft_chr_var_env(t_data *data, char *str)
{
	t_env_list	*env_list;

	env_list = data->env_table;
	while (env_list)
	{
		if (ft_strncmp(str, env_list->name) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

void	ft_update_var_env(t_data *data, char *name, char *value)
{
	t_env_list	*p_env_name;

	p_env_name = ft_search_env(data, name);
	if (p_env_name != NULL)
		free(p_env_name->value);
	if (p_env_name)
		p_env_name->value = ft_strdup(value);
}
