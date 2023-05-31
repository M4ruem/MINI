/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:53:34 by cormiere          #+#    #+#             */
/*   Updated: 2023/05/29 14:55:11 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**allocate_tabl(t_data **data)
{
	char	**tabl;

	tabl = malloc(sizeof(char *) * ((*data)->data2.nbr + 2));
	if (!tabl)
		exit(EXIT_FAILURE);
	tabl[(*data)->data2.nbr + 1] = NULL;
	return (tabl);
}

char	**fill_tabl(t_data **data, char *str, char **tabl)
{
	int	i;

	i = ft_strlen(str) - 1;
	tabl = put_cmd_in_arg(i, *data, str, tabl);
	return (tabl);
}
