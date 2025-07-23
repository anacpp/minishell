/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by rjacques          #+#    #+#             */
/*   Updated: 2025/07/23 20:14:14 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*TODO : reduzir -> add_env_var 
		 alocar -> funções auxiliares para outro arquivo
		 (max 5 fun por arquivo)
*/

// Declaration of static functions (local helpers)
static int	get_env_count(char **env);
static char	**duplicate_initial_environment(void);
static char	*extract_key_from_string(const char *var_string);

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

/**
 * @brief Finds a variable in the shell environment.
 * @param key The key of the variable to be searched.
 * @param envp The shell environment.
 * @return A pointer to the variable string in the environment, or NULL.
 */
char	**find_env_var(const char *key, char **envp)
{
	int	i;
	int	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && (envp[i][key_len] == '='
			|| envp[i][key_len] == '\0'))
		{
			return (&envp[i]);
		}
		i++;
	}
	return (NULL);
}

static char	*extract_key_from_string(const char *var_string)
{
	const char	*equal_sign;

	equal_sign = ft_strchr(var_string, '=');
	if (equal_sign)
		return (ft_substr(var_string, 0, equal_sign - var_string));
	return (ft_strdup(var_string));
}

/**
 * @brief Adds or updates an environment variable in the shell context.
 * @param var_string The variable string ("KEY=value" or "KEY").
 * @param shell_context The shell context whose environment will be modified.
 */
void	add_env_var(const char *var_string, t_shell *shell_context)
{
	char	*key;
	char	**var_ptr;
	int		count;
	char	**new_env;

	key = extract_key_from_string(var_string);
	var_ptr = find_env_var(key, shell_context->envp);
	if (var_ptr && ft_strchr(var_string, '='))
	{
		free(*var_ptr);
		*var_ptr = ft_strdup(var_string);
	}
	else if (!var_ptr)
	{
		count = 0;
		while (shell_context->envp && shell_context->envp[count])
			count++;
		new_env = malloc(sizeof(char *) * (count + 2));
		if (!new_env)
			handle_error(NULL, "malloc failed", 1, 1);
		ft_memcpy(new_env, shell_context->envp, count * sizeof(char *));
		new_env[count] = ft_strdup(var_string);
		new_env[count + 1] = NULL;
		free(shell_context->envp);
		shell_context->envp = new_env;
	}
	free(key);
}

/**
 * @brief Removes an environment variable from the shell context.
 * @param key The key of the variable to be removed.
 * @param shell_context The shell context.
 */
void	remove_env_var(const char *key, t_shell *shell_context)
{
	char	**var_ptr;

	var_ptr = find_env_var(key, shell_context->envp);
	if (var_ptr)
	{
		free(*var_ptr);
		while (*var_ptr)
		{
			*var_ptr = *(var_ptr + 1);
			var_ptr++;
		}
	}
}

/**
 * @brief Searches for an environment variable in envp and returns its value.
 * @param key The key to be searched (e.g., "PATH").
 * @param envp The environment array.

	* @return The variable value (the string after '=')
	or NULL if not found.
 * The returned string points to memory inside envp,
   it's not a copy.
 */
char	*get_env_value(const char *key, char **envp)
{
	int	i;
	int	key_len;

	if (!key || !envp)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			return (envp[i] + key_len + 1);
		}
		i++;
	}
	return (NULL);
}
