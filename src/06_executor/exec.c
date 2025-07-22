/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/22 18:31:41 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	TODO: Redução de função -> execute_pipeline.c heredoc

*/
#include "../../includes/minishell.h"

static int	execute_single_builtin(t_cmd *cmd, t_shell *shell_context);
static int	execute_pipeline(t_cmd *cmds, t_shell *shell_context);
static void	execute_child_process(t_cmd *cmd, int *pipe_fds, int in_fd,
				t_shell *shell_context);
static void	prepare_heredocs(t_cmd *cmds);

/**
 * @brief Prepara os heredocs para os comandos,
 * criando arquivos temporários.

	* Cada heredoc é substituído por um arquivo
	temporário que contém o texto do heredoc.
 * @param cmds A lista de comandos que contêm os heredocs.
 */
static void	prepare_heredocs(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*redir;
	
	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
			{
				char *tmp_path;

				if (create_heredoc(redir->filename, &tmp_path) < 0)
				{
					perror("heredoc");
				}
				free(redir->filename);
				redir->filename = tmp_path;
				redir->type = T_REDIR_IN;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

/**
 * @brief Executa os comandos no contexto do shell.
 * Se for um único comando built-in, executa diretamente.
 * Se for uma pipeline, cria processos filhos para cada comando.
 * @param cmds A lista de comandos a serem executados.

	* @param shell_context O contexto do shell que contém
	o ambiente e o último status.
 * @return O status de saída do comando executado (0 para sucesso,
	>0 para erro).
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
 * @brief Executa um único built-in no processo pai.
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

/**
 * @brief Executa uma pipeline de comandos em processos filhos.
 */
static int	execute_pipeline(t_cmd *cmds, t_shell *shell_context)
{
	int		pipe_fds[2];
	int		in_fd;
	pid_t	pid;
	t_cmd	*current;

	in_fd = STDIN_FILENO;
	current = cmds;
	g_num_pids = 0;
	while (current)
	{
		if (current->next)
			pipe(pipe_fds);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
			execute_child_process(current, pipe_fds, in_fd, shell_context);
		save_pid(pid);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (current->next)
		{
			close(pipe_fds[1]);
			in_fd = pipe_fds[0];
		}
		current = current->next;
	}
	wait_all_children();
	return (g_signal_status);
}

/**
 * @brief Código executado dentro de um processo filho.
 */
static void	execute_child_process(t_cmd *cmd, int *pipe_fds, int in_fd,
		t_shell *shell_context)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd->next)
	{
		close(pipe_fds[0]);
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);
	}
	if (cmd->redirs)
		setup_redir(cmd->redirs);
	if (cmd->redirs)
	{
		setup_redir(cmd->redirs);

		t_redir *redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == T_REDIR_IN &&
				redir->filename &&
				ft_strncmp(redir->filename, "./.heredoc_", 11) == 0)
			{
				unlink(redir->filename);
			}
			redir = redir->next;
		}
	}

	if (is_builtin(cmd))
		exit(run_builtin(cmd, shell_context));
	else
		exec_external(cmd, shell_context);
	exit(EXIT_FAILURE);
}
