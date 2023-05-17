#include "../minishell.h"

void	msh_env(t_token *argv, t_env *envlst)
{
	if (argv->next)
	{
		errno = NO_EXIST;
		builtin_error(ft_strjoin("env: ", argv->next->str));
		return ;
	}
	while (envlst)
	{
		if (envlst->val)
		{
			ft_putstr_fd(envlst->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(envlst->val, STDOUT_FILENO);
		}
		envlst = envlst->next;
	}
}
