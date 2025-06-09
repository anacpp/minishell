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

