/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/08/05 17:27:02 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	execute_single_builtin(t_cmd *cmd, t_shell *shell_context);
static void	prepare_heredocs(t_cmd *cmds);

/**
 * @brief Prepares heredocs for commands,
 * creating temporary files.

	* Each heredoc is replaced by a temporary
	file that contains the heredoc text.
 * @param cmds The list of commands that contain the heredocs.
 */
static void	process_heredoc_redir(t_redir *redir)
{
	char	*tmp_path;

	if (create_heredoc(redir->filename, &tmp_path) < 0)
		perror("heredoc");
	free(redir->filename);
	redir->filename = tmp_path;
	redir->type = T_REDIR_IN;
}

static void	process_heredocs_for_cmd(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == T_HEREDOC)
			process_heredoc_redir(redir);
		redir = redir->next;
	}
}

static void	prepare_heredocs(t_cmd *cmds)
{
	t_cmd	*cmd;

	cmd = cmds;
	while (cmd)
	{
		process_heredocs_for_cmd(cmd);
		cmd = cmd->next;
	}
}

/**
 * @brief Executes commands in the shell context.
 * If it's a single built-in command, executes directly.
 * If it's a pipeline, creates child processes for each command.
 * @param cmds The list of commands to be executed.

	* @param shell_context The shell context that contains
	the environment and last status.
 * @return The exit status of the executed command (0 for success,
	>0 for error).
 */
int	executor(t_cmd *cmds, t_shell *shell_context)
{
	if (!cmds)
		return (0);
	prepare_heredocs(cmds);
	if (!cmds->next && is_builtin(cmds))
	{
		return (execute_single_builtin(cmds, shell_context));
	}
	return (execute_pipeline(cmds, shell_context));
}

/**
 * @brief Executes a single built-in in the parent process.
 */
static int	execute_single_builtin(t_cmd *cmd, t_shell *shell_context)
{
	int	stdio_backup[2];
	int	status;

	save_stdio(stdio_backup);
	if (cmd->redirs)
	{
		setup_redir(cmd->redirs);
	}
	status = run_builtin(cmd, shell_context);
	restore_stdio(stdio_backup);
	return (status);
}
