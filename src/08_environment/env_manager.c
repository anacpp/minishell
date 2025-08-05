/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by rdos-san          #+#    #+#             */
/*   Updated: 2025/08/05 17:32:59 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*extract_key_from_string(const char *var_string)
{
	const char	*equal_sign;

	equal_sign = ft_strchr(var_string, '=');
	if (equal_sign)
		return (ft_substr(var_string, 0, equal_sign - var_string));
	return (ft_strdup(var_string));
}

/**
 * @brief Finds a variable in the shell environment.
 * @param key The key of the variable to be searched.
 * @param envp The shell environment.
 * @return A pointer to the variable string in the environment, or NULL.
 */
static char	**find_env_var(const char *key, char **envp)
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
	char	**new_envp;

	key = extract_key_from_string(var_string);
	var_ptr = find_env_var(key, shell_context->envp);
	if (var_ptr && ft_strchr(var_string, '='))
	{
		free(*var_ptr);
		*var_ptr = ft_strdup(var_string);
	}
	else if (!var_ptr)
	{
		count = ft_count_args(shell_context->envp);
		new_envp = ft_calloc(count + 2, sizeof(char *));
		if (!new_envp)
			handle_error(NULL, "malloc failed", 1, 1);
		ft_memcpy(new_envp, shell_context->envp, count * sizeof(char *));
		new_envp[count] = ft_strdup(var_string);
		free(shell_context->envp);
		shell_context->envp = new_envp;
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
