/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:26:26 by cormiere          #+#    #+#             */
/*   Updated: 2023/05/29 14:28:16 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_chr(char c, t_data *data)
{
	if ((c == 33 || c == 35 || c == 42 || c == 40 || c == 41
			|| c == 59 || c == 47 || c == 63 || c == 124)
		&& data->data1.squote == 0 && data->data1.dquote == 0)
		return (1);
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (nmemb == 0 || size <= 0)
		return (malloc(0));
	if (!(nmemb * size / size == nmemb))
		return (NULL);
	dest = malloc(size * nmemb);
	if (dest == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}

int	check_rl(void)
{
	if (g_sigint == 1)
		rl_done = 1;
	return (0);
}
