#include "../../includes/minishell.h"

void	builtin_pwd(void)
{
	char	cwd[1024];
	char	*ret;

	ret = getcwd(cwd, sizeof(cwd));
	if (ret)
		ft_printf("%s\n", cwd);
	else
		ft_printf("minishell: pwd: error retrieving current directory\n");
}

extern char	**environ;

void	builtin_env(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (ft_strchr(environ[i], '='))
			ft_printf("%s\n", environ[i]);
		i++;
	}
}
void	builtin_export(char **argv)
{
	int		i;
	char	*key;

	if (!argv[1])
	{
		for (int j = 0; environ[j]; j++)
		{
			if (ft_strchr(environ[j], '='))
			{
				key = ft_substr(environ[j], 0, ft_strchr(environ[j], '=') - environ[j]);
				ft_printf("declare -x %s=\"%s\"\n", key, getenv(key));
				free(key);
			}
		}
		return ;
	}
	i = 1;
	while (argv[i])
	{
		if (!is_valid_key(argv[i]))
			ft_printf("minishell: export: `%s`: not a valid identifier\n", argv[i]);
		else
			putenv(ft_strdup(argv[i]));
		i++;
	}
}

void	builtin_unset(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_key(argv[i]))
			ft_printf("minishell: unset: `%s`: not a valid identifier\n", argv[i]);
		else
			unsetenv(argv[i]);
		i++;
	}
}

