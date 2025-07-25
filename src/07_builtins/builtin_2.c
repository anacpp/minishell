/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/23 20:27:16 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Implements additional built-in commands for minishell.

	Functions:
	- builtin_pwd: displays the current directory.
	- builtin_env: prints environment variables.
	- builtin_export: adds/updates environment variables.
	- builtin_unset: removes environment variables.
	
	Uses the global variable `environ` to access/modify the environment.
*/

#include "../../includes/minishell.h"

/**
 * @brief Prints a standardized error message for a builtin.
 *
 * @param cmd The builtin command name.
 * @param arg The argument that caused the error (can be NULL).
 * @param msg The specific error message.
 */
static void	print_builtin_error(const char *cmd, const char *arg,
		const char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd((char *)arg, STDERR_FILENO);
		ft_putstr_fd("': ", STDERR_FILENO);
	}
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

/**
 * @brief Displays the current working directory.
 *
 * Does not accept arguments. In case of error getting the directory,
 * prints a custom error message.
 *
 * @return Returns 0 on success, 1 on error.
 */
int	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	else
	{
		print_builtin_error("pwd", NULL, "error retrieving current directory");
		return (1);
	}
}

/**
 * @brief Prints the environment variables of the current context.
 *
 * @param argv The command argument vector.
 * @param shell_context The shell context.
 * @return Returns 0 on success, 127 if invalid arguments are passed.
 */
int	builtin_env(char **argv, t_shell *shell_context)
{
	char	**env;
	int		i;

	if (argv[1])
	{
		print_builtin_error("env", argv[1], "No such file or directory");
		return (127);
	}
	env = shell_context->envp;
	i = 0;
	while (env && env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			ft_putstr_fd(env[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Adds or updates variables in the shell environment.
 *
 * If called without arguments, prints the environment in sorted order.
 * For each argument, validates the key and adds/updates it in the environment.
 * Continues processing even if it finds an invalid key.
 *
 * @param argv Command arguments.
 * @param shell_context The shell context.
 * @return Returns 0 if everything is successful, 1 if any key is invalid.
 */
int	builtin_export(char **argv, t_shell *shell_context)
{
	int	i;
	int	status;

	status = 0;
	if (!argv[1])
	{
		print_env_sorted(shell_context->envp);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		if (!is_valid_key(argv[i]))
		{
			print_builtin_error("export", argv[i], "not a valid identifier");
			status = 1;
		}
		else
			add_env_var(argv[i], shell_context);
		i++;
	}
	return (status);
}

/**
 * @brief Removes variables from the shell environment.
 *
 * Validates each key before trying to remove it. Keys for unset
 * cannot contain the '=' character.
 *
 * @param argv Command arguments.
 * @param shell_context The shell context.
 * @return Returns 0 if everything is successful, 1 if any key is invalid.
 */
int	builtin_unset(char **argv, t_shell *shell_context)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (argv[i])
	{
		if (!is_valid_key(argv[i]) || ft_strchr(argv[i], '='))
		{
			print_builtin_error("unset", argv[i], "not a valid identifier");
			status = 1;
		}
		else
			remove_env_var(argv[i], shell_context);
		i++;
	}
	return (status);
}
