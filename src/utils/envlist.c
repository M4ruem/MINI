#include "../minishell.h"

t_env	*init_envlst(char *key, char *val);
void	add_to_envlst(t_env **envlst, t_env *new);
void	del_from_envlst(t_env **envlst);
void	free_envlst(t_env *envlst);

t_env	*init_envlst(char *key, char *val)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		err_alloc();
	new->key = key;
	new->val = val;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	add_to_envlst(t_env **envlst, t_env *new)
{
	t_env	*tmp;

	if (*envlst == NULL)
		(*envlst) = new;
	else
	{
		tmp = *envlst;
		while ((*envlst)->next)
			*envlst = (*envlst)->next;
		(*envlst)->next = new;
		new->prev = (*envlst);
		*envlst = tmp;
	}
}

void	del_from_envlst(t_env **envlst)
{
	t_env	*del;

	del = (*envlst);
	if ((*envlst)->prev == NULL)
	{
		(*envlst) = (*envlst)->next;
		(*envlst)->prev = NULL;
	}	
	else if ((*envlst)->next == NULL)
	{
		(*envlst) = (*envlst)->prev;
		(*envlst)->next = NULL;
	}
	else
	{
		del->prev->next = del->next;
		del->next->prev = del->prev;
		(*envlst) = del->next;
	}
	free(del->key);
	free(del->val);
	del->next = NULL;
	del->prev = NULL;
	free(del);
}

void	free_envlst(t_env *envlst)
{
	t_env	*tmp;

	while (envlst)
	{
		tmp = envlst;
		envlst = envlst->next;
		free(tmp->key);
		if (tmp->val)
			free(tmp->val);
		tmp->key = NULL;
		tmp->val = NULL;
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp);
		tmp = NULL;
	}
}