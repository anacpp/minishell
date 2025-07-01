/*
	BUILTIN_2.C

	Implementa comandos built-in adicionais da minishell.

	Funções:
	- builtin_pwd: exibe o diretório atual.
	- builtin_env: imprime variáveis de ambiente.
	- builtin_export: adiciona/atualiza variáveis de ambiente.
	- builtin_unset: remove variáveis de ambiente.

	Utiliza a variável global `environ` para acessar/modificar o ambiente.
*/


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

	if (!argv[1])
	{
		print_env_sorted();
		return ;
	}
	i = 1;
	while (argv[i])
	{
		if (!is_valid_key(argv[i]))
			ft_printf("minishell: export: `%s`: not a valid identifier\n", argv[i]);
		else
			putenv(ft_strdup(argv[i])); // INfelizmente não podemos usar essa função é necesário trocar
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
			unsetenv(argv[i]);// ESSE comando tb não pode ser usado :C
		i++;
	}
}

