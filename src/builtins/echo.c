//#include "../minishell.h"

/*void	msh_echo(t_token *argv);
int		_echo_opt(char *str);

void	msh_echo(t_token *argv)
{
	int	n_opt;

	n_opt = 0;
	argv = argv->next;
	while (argv)
	{
		if (_echo_opt(argv->str))
			n_opt = 1;
		else
			break ;
		argv = argv->next;
	}
	while (argv)
	{
		ft_putstr_fd(argv->str, STDOUT_FILENO);
		argv = argv->next;
		if (argv)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (n_opt == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

int	_echo_opt(char *str)
{
	if (ft_strncmp(str, "-n", 2))
		return (0);
	else
	{
		str += 2;
		while (*str)
		{
			if (*str != 'n')
				return (0);
			str++;
		}
		return (1);
	}
}*/

#include "../minishell.h"

void msh_echo(t_token *argv);
int is_echo_option(const char *str);

void msh_echo(t_token *argv)
{
    int n_opt = 0;
    argv = argv->next;

    // Check for -n option
    while (argv)
    {
        if (is_echo_option(argv->str))
        {
            n_opt = 1;
        }
        else
        {
            break;
        }
        argv = argv->next;
    }

    // Print the arguments
    while (argv)
    {
        ft_putstr_fd(argv->str, STDOUT_FILENO);
        argv = argv->next;
        if (argv)
        {
            ft_putstr_fd(" ", STDOUT_FILENO);
        }
    }

    // Print a newline unless -n option is specified
    if (n_opt == 0)
    {
        ft_putstr_fd("\n", STDOUT_FILENO);
    }
}

int is_echo_option(const char *str)
{
    if (ft_strcmp(str, "-n") == 0)
    {
        return 1;
    }
    return 0;
}
