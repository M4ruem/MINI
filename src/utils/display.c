#include "../minishell.h"

void	display_toklst(t_toklst *toklst);
void	display_strlst(t_token *strlst);
void	display_envlst(t_env *envlst);

void	display_toklst(t_toklst *toklst)
{
	int	idx;

	idx = 1;
	while (toklst)
	{
		if (!toklst)
			break ;
		printf("__________ %dth node __________\n", idx);
		printf("  cmd : ");
		display_strlst(toklst->cmd);
		printf(" </<< : ");
		display_strlst(toklst->rdr_in);
		printf(" >/>> : ");
		display_strlst(toklst->rdr_out);
		printf("_______________________________\n");
		toklst = toklst->next;
		idx++;
	}
}

void	display_strlst(t_token *strlst)
{
	if (!strlst)
		printf("(null)\n");
	while (strlst)
	{
		printf("%s(%d)", strlst->str, strlst->type);
		if (strlst->next)
			printf(" | ");
		else
			printf(" \033[0;33m.\033[0;37m\n");
		strlst = strlst->next;
	}
}

void	display_envlst(t_env *envlst)
{
	if (!envlst)
		printf("(null)\n");
	while (envlst)
	{
		if (envlst->val)
			printf("%s=%s\n", envlst->key, envlst->val);
		envlst = envlst->next;
	}
}
