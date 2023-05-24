/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:37:49 by cormiere          #+#    #+#             */
/*   Updated: 2023/05/23 19:07:15 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	bin_export(char **arg, t_data *data)
{
	data->data4.f = 0;
	if (!arg[data->data4.f])
	{
		ft_sort_list(data);
		ft_display_env(data->env_table_sorted);
		return ;
	}
	while (arg[data->data4.f])
	{
		data->data4.e = 0;
		while (arg[data->data4.f][data->data4.e])
		{
			while (ft_isalnum(arg[data->data4.f][data->data4.e]) == 1 \
				|| arg[data->data4.f][data->data4.e] == '_')
				data->data4.e++;
			if ((arg[data->data4.f][data->data4.e] == '=' || arg[data->data4.f] \
				[data->data4.e] == '\0') && data->data4.e > 0)
				ft_correct_env_name(arg, data);
			else
				ft_wrong_env_name(arg, data);
			if (arg[data->data4.f][data->data4.e])
				data->data4.e++;
		}
		data->data4.f++;
	}
}

void	ft_display_env(t_env_list *list)
{
	t_env_list	*begin;

	begin = list;
	while (begin)
	{
		printf("declare -x %s", begin->name);
		if (begin->value)
			printf("=\"%s\"\n", begin->value);
		else
			printf("\n");
		begin = begin->next;
	}
}

t_env_list	*ft_search_env(t_data *data, char *name)
{
	t_env_list	*current_elmt;

	current_elmt = data->env_table;
	while (current_elmt)
	{
		if (ft_strncmp(name, current_elmt->name) == 0)
			return (current_elmt);
		current_elmt = current_elmt->next;
	}
	return (NULL);
}

void	ft_correct_env_name(char **arg, t_data *data)
{
	char		*name;
	char		*value;
	t_env_list	*p_env_name;

	name = ft_substr(arg[data->data4.f], 0, data->data4.e);
	if (arg[data->data4.f][data->data4.e] == '=' &&
		arg[data->data4.f][data->data4.e + 1])
		value = ft_substr(arg[data->data4.f], data->data4.e + 1, \
			ft_strlen(arg[data->data4.f]) - (data->data4.e + 1));
	if (arg[data->data4.f][data->data4.e] == '=' &&
		arg[data->data4.f][data->data4.e + 1])
		data->data4.e = ft_strlen(arg[data->data4.f]);
	else
		value = NULL;
	p_env_name = ft_search_env(data, name);
	if (!p_env_name)
		ft_env_lstadd_back(&data->env_table, ft_env_lstnew(name, value));
	else
	{
		free(p_env_name->value);
		free(name);
		p_env_name->value = ft_strdup(value);
		free(value);
	}
}

void	ft_wrong_env_name(char **arg, t_data *data)
{
	char	*name;

	while (arg[data->data4.f][data->data4.e] &&
		arg[data->data4.f][data->data4.e] != ' ')
		data->data4.e++;
	name = ft_substr(arg[data->data4.f], 0, data->data4.e);
	printf("minishell: export: `%s': not a valid identifier\n", name);
	data->data5.last_error = 1;
	free(name);
}
