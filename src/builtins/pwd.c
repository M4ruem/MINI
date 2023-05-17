#include "../minishell.h"

void	msh_pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, MAX_PATH_LEN);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
}
