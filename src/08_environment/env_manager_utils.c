
#include "../../includes/minishell.h"

/**
 * @brief Counts the number of environment variables in the array.
 * @param env The environment string array.
 * @return The number of environment variables.
 */
static int	get_env_count(char **env)
{
	int	count;

	count = 0;
	while (env && env[count])
	{
		count++;
	}
	return (count);
}

/**
 * @brief Duplica o ambiente do sistema.
 * @return Um novo array de strings alocado dinamicamente.
 */
static char	**duplicate_initial_environment(void)
{
	extern char	**environ;
	char		**new_env;
	int			count;
	int			i;

	count = get_env_count(environ);
	new_env = ft_calloc(count + 1, sizeof(char *));
	if (!new_env)
		handle_error(NULL, "malloc failed", 1, 1);
	i = -1;
	while (++i < count)
	{
		new_env[i] = ft_strdup(environ[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			handle_error(NULL, "malloc failed", 1, 1);
		}
	}
	return (new_env);
}

/**
 * @brief Inicializa o contexto do shell, incluindo o ambiente e o status.
 * @param shell_context Ponteiro para a struct t_shell.
 */
void	init_shell_context(t_shell *shell_context)
{
	shell_context->envp = duplicate_initial_environment();
	shell_context->last_status = 0;
}

/**
 * @brief Frees the memory allocated for the shell environment.
 * @param shell_context The shell context.
 */
void	free_environment(t_shell *shell_context)
{
	int	i;

	if (shell_context->envp)
	{
		i = 0;
		while (shell_context->envp[i])
		{
			free(shell_context->envp[i]);
			i++;
		}
		free(shell_context->envp);
		shell_context->envp = NULL;
	}
}
