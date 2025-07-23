/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/23 20:14:12 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	BUILTIN_UTILS.C

	Auxiliary functions to support built-in commands.

	Functions:
	- is_n_flag: checks if the echo `-n` flag is correctly present.
	- is_valid_key: validates variable names for export/unset.
	- print_env_sorted: prints environment variables in export order.

	These functions help ensure that built-in commands
	work correctly and in a standardized way.
*/

#include "../../includes/minishell.h"

/**
 * @brief Checks if the string represents the `-n` flag of the `echo` command.
 * @param str The string to be checked.
 * @return 1 if it's the `-n` flag, 0 otherwise.
 * */
int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Checks if an environment variable key is valid.
 */
int	is_valid_key(char *key)
{
	int	i;

	if (!key || !(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	i = 1;
	while (key[i] && key[i] != '=')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
/**
 * @brief Sorts an array of strings in alphabetical order (Bubble Sort).
 * @param env The array of string pointers to be sorted.
 * @param count The number of elements in the array.
 */

static void	sort_env_array(char **env, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strncmp(env[j], env[j + 1], ft_strlen(env[j])) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief Prints environment variables in the format 
 * 'declare -x KEY=VALUE',
 * in alphabetical order.
 *
 * This function creates a copy of the environment 
 * pointer array to
 * not modify the original shell environment order.
 *
 * @param envp The shell environment to be printed.
 */
void	print_env_sorted(char **envp)
{
	char	**env_copy;
	int		count;
	int		i;

	if (!envp)
		return ;
	count = 0;
	while (envp[count])
		count++;
	env_copy = malloc(sizeof(char *) * (count + 1));
	if (!env_copy)
		return ;
	i = -1;
	while (++i < count)
		env_copy[i] = envp[i];
	env_copy[count] = NULL;
	sort_env_array(env_copy, count);
	i = 0;
	while (i < count)
	{
		//ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_copy[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	free(env_copy);
}
