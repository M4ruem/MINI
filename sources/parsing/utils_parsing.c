#include "../include/minishell.h"

int	check_stupid_quotes(char *str)
{
	int	i;
	int	j;
	int	len;
	int	x;

	x = 0;
	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == 39)
			j++;
		if (str[i] == '"')
			x++;
		i++;
	}
	if ((j % 2 != 0 || x % 2 != 0) && (j == len || x == len
			|| (j + x) == len))
		printf("Error quote not closed\n");
	if (j == len || x == len || (j + x) == len)
		return (1);
	return (0);
}

int	finsh_stupid(t_data *data, char *str, int x, int j)
{
	int	i;
	int	len;

	len = ft_strlen(str);
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
	int	i;
	int	j;
	int	x;
	int	len;

	i = 0;
	x = 0;
	j = 0;
	len = ft_strlen(str);
	if (str == NULL)
		return (2);
	if (check_stupid_quotes(str) == 1)
		return (3);
	if (ft_strncmp(str, ".") == 0)
	{
		printf("Minisheru: .: filename argument required]\n");
		printf(".: usage: . filename [arguments]\n");
		data->data5.last_error = 2;
		return (1);
	}
	while (str[i] == '.')
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
