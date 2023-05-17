//#include "../minishell.h"

/*void	msh_cd(t_token *argv, t_env *envlst);
int		_cd_old(t_env *envlst);
int		_cd_home(char *str, t_env *envlst);
int		_cd_str(char *err_msg, int type);
void	_cd_error(char *str, int type);

void	msh_cd(t_token *argv, t_env *envlst)
{
	int		flag;

	flag = SUCCESS;
	if (argv->next == NULL)
		flag = _cd_home(NULL, envlst);
	else
	{
		argv = argv->next;
		if (ft_strcmp(argv->str, "-") == 0)
			flag = _cd_old(envlst);
		else if (argv->str[0] == '~' || ft_strcmp(argv->str, "--") == 0)
			flag = _cd_home(argv->str, envlst);
		else if (argv->type == T_ENV && argv->str[0] == '\0')
			flag = _cd_home(NULL, envlst);
		else if ((argv->type == T_ENV && argv->str[0] != '\0') || \
					argv->type == T_OFF)
			flag = _cd_str(argv->str, argv->type);
	}
	if (flag == FAILURE)
		return ;
	change_env_val(envlst, "OLDPWD", get_env_val(envlst, "PWD"));
	change_env_val(envlst, "PWD", getcwd(0, MAX_PATH_LEN));
}

int	_cd_old(t_env *envlst)
{
	char	*path;

	path = get_env_val(envlst, "OLDPWD");
	if (path && chdir(path) != -1)
	{
		ft_putendl_fd(path, STDOUT_FILENO);
		free(path);
	}
	else
		_cd_error("OLDPWD", CD_NOT_SET);
	if (g_status != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	_cd_home(char *str, t_env *envlst)
{
	char	*path;

	path = get_env_val(envlst, "HOME");
	if (!path)
	{
		_cd_error("HOME", CD_NOT_SET);
		return (FAILURE);
	}
	if (str && str[0] == '~' && str[1] != '\0')
		path = msh_strjoin(path, msh_strdup(str + 1));
	if (chdir(path) == -1)
		_cd_error(path, CD_NOT_FOUND);
	free(path);
	if (g_status != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	_cd_str(char *str, int type)
{
	char		*path;
	struct stat	stat_result;

	path = NULL;
	if (type == T_OFF)
		path = msh_strdup(str);
	else if (type == T_ENV)
		path = msh_strdup(str);
	if (chdir(path) == -1)
	{
		if (stat(path, &stat_result) != -1 && stat_result.st_mode != 0040000)
			_cd_error(path, CD_NOT_DIR);
		else
			_cd_error(path, CD_NOT_FOUND);
	}
	free(path);
	if (g_status != 0)
		return (FAILURE);
	return (SUCCESS);
}

void	_cd_error(char *err_msg, int type)
{
	ft_putstr_fd("gumshell: cd: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	if (type == CD_NOT_SET)
		ft_putendl_fd(" not set", STDERR_FILENO);
	else if (type == CD_NOT_FOUND)
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	else if (type == CD_NOT_DIR)
		ft_putendl_fd(": Not a directory", STDERR_FILENO);
	g_status = 1;
}*/

#include "../minishell.h"

void msh_cd(t_token *argv, t_env *envlst);
int cd_old(t_env *envlst);
int cd_home(char *str, t_env *envlst);
int cd_directory(char *path);
void print_cd_error(const char *command, const char *error);

void msh_cd(t_token *argv, t_env *envlst)
{
    int flag = SUCCESS;
    
    if (argv->next == NULL)
    {
        flag = cd_home(NULL, envlst);
    }
    else
    {
        argv = argv->next;
        if (ft_strcmp(argv->str, "-") == 0)
        {
            flag = cd_old(envlst);
        }
        else if (argv->str[0] == '~' || strcmp(argv->str, "--") == 0)
        {
            flag = cd_home(argv->str, envlst);
        }
        else if (argv->type == T_ENV && argv->str[0] == '\0')
        {
            flag = cd_home(NULL, envlst);
        }
        else if (argv->type == T_ENV || argv->type == T_OFF)
        {
            flag = cd_directory(argv->str);
        }
    }
    
    if (flag == FAILURE)
        return;
    
    change_env_val(envlst, "OLDPWD", get_env_val(envlst, "PWD"));
    change_env_val(envlst, "PWD", getcwd(NULL, 0));
}

int cd_old(t_env *envlst)
{
    char *path = get_env_val(envlst, "OLDPWD");
    
    if (!path || chdir(path) == -1)
    {
        print_cd_error("cd", "OLDPWD not set");
        return FAILURE;
    }
    
    printf("%s\n", path);
    free(path);
    
    return SUCCESS;
}

int cd_home(char *str, t_env *envlst)
{
    char *path = get_env_val(envlst, "HOME");
    
    if (!path)
    {
        print_cd_error("cd", "HOME not set");
        return FAILURE;
    }
    
    if (str && str[0] == '~' && str[1] != '\0')
    {
        char *temp = msh_strjoin(path, str + 1);
        free(path);
        path = temp;
    }
    
    int result = cd_directory(path);
    
    free(path);
    
    return result;
}

int cd_directory(char *path)
{
    if (chdir(path) == -1)
    {
        struct stat stat_result;
        
        if (stat(path, &stat_result) != -1 && !S_ISDIR(stat_result.st_mode))
            print_cd_error("cd", "Not a directory");
        else
            print_cd_error("cd", "No such file or directory");
        
        return FAILURE;
    }
    
    return SUCCESS;
}

void print_cd_error(const char *command, const char *error)
{
    fprintf(stderr, "%s: %s\n", command, error);
    g_status = 1;
}
