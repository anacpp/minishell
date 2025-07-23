/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:36:30 by rjacques          #+#    #+#             */
/*   Updated: 2025/07/23 20:14:18 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*TODO: 
	Function reduction : find_cmd_path */

#include "../../includes/minishell.h"

static char	*check_direct_exec(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

/**
 * @brief Finds the complete path of an executable command.
 * @param cmd The command to be found.
 * @param envp The current environment to search for the PATH variable.
 * @return The dynamically allocated complete path or NULL.
 */
static char	*find_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_var;
	char	*full_path;
	int		i;

	if (!cmd || ft_strchr(cmd, '/'))
		return (check_direct_exec(cmd));
	path_var = get_env_value("PATH", envp);
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_triple(paths[i], "/", cmd);
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}
extern char	**environ;

void	exec_external(t_cmd *cmd, t_shell *shell_context)
{
	char	*cmd_path;
	char	**current_env;

	current_env = shell_context->envp;
	cmd_path = find_cmd_path(cmd->argv[0], current_env);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	execve(cmd_path, cmd->argv, current_env);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(cmd_path);
	exit(126);
}
