/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacques <rjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/30 11:19:22 by rjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	BUILTIN.C

	Executes built-in commands recognized by minishell: cd, exit, echo,
		pwd, env, export, unset.

	Functions:
	- run_builtin: routes execution based on command name.
	- builtin_cd: changes current directory (or goes to $HOME if no argument).
	- builtin_exit: terminates shell with optional status.
	- builtin_echo: prints arguments with -n flag support.
*/

#include "../../includes/minishell.h"

/**
 * @brief Prints arguments to standard output.
 * @param argv Command arguments.
 * @return Always returns 0 (success).
 */
static int	builtin_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (argv[i] && is_n_flag(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}

/**
 * @brief Changes the current working directory.
 *
 * Performs checks using stat() to provide accurate
 * error messages
 *
 * @param argv Command arguments.
 * @param shell_context The shell context to access the environment.
 * @return 0 on success, 1 on error.
 */
static int	builtin_cd(char **argv, t_shell *shell_context)
{
	char		*path;
	struct stat	stat_buf;

	if (argv[1] && argv[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n",
				STDERR_FILENO), 1);
	path = argv[1];
	if (!path)
	{
		path = get_env_value("HOME", shell_context->envp);
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n",
					STDERR_FILENO), 1);
	}
	if (stat(path, &stat_buf) != 0)
	{
		print_cd_error(path, "No such file or directory");
		return (1);
	}
	if (!S_ISDIR(stat_buf.st_mode))
		return (print_cd_error(path, "Not a directory"), 1);
	if (chdir(path) != 0)
		return (print_cd_error(path, "Permission denied"), 1);
	return (0);
}

/**
 * @brief Checks if a string represents a valid number (integer).
 *
 * This helper function checks if the string contains only digits,
 * with an optional sign ('+' or '-') at the beginning.
 *
 * @param str The string to be checked.
 * @return 1 if it's a valid numeric string, 0 otherwise.
 */
static int	is_numeric_string(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Terminates the shell with an exit status,
 * with argument validation.
 *
 * Implemented behaviors:
 * 1.  `exit` (no args): Exits with the last command status.
 * 2.  `exit [arg]`:
 * - If [arg] is not numeric, prints error and exits with status 2.
 * - If there's more than one argument, prints error,
 * returns status 1 and does NOT exit.
 * - If [arg] is numeric, exits with status `[arg] % 256`.
 *
 * @param argv Command arguments.
 * @param shell_context Shell context to get the last status.

	* @return Does not return if successful. Returns 1
	in case of "too many arguments".
 */
static int	builtin_exit(char **argv, t_shell *shell_context)
{
	long long	status;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!argv[1])
	{
		exit(shell_context->last_status);
	}
	if (!is_numeric_string(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(2);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	status = ft_atoll(argv[1]);
	exit((unsigned char)status);
}

/**
 * @brief Routes to the correct built-in function and returns its status.
 * @param cmd The command to be executed.
 * @return The exit status of the built-in (0 for success, >0 for error).
 */
int	run_builtin(t_cmd *cmd, t_shell *shell_context)
{
	char	*cmd_name;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (127);
	cmd_name = cmd->argv[0];
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (builtin_cd(cmd->argv, shell_context));
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd_name, "export") == 0)
		return (builtin_export(cmd->argv, shell_context));
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (builtin_unset(cmd->argv, shell_context));
	if (ft_strcmp(cmd_name, "env") == 0)
		return (builtin_env(cmd->argv, shell_context));
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (builtin_exit(cmd->argv, shell_context));
	return (127);
}
