/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/06/11 17:12:14 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	TODO:
	->adicionar tratamento para quando o input escrito não
	corresponder a nenhum tipo de comando externo ou interno; retuornar erro : comando não encontrado;
	->NORMA /NORMINETTE/VALGRIND

*/
#include "../../includes/minishell.h"

static void	setup_heredoc_input(t_cmd *cmd)
{
	if (cmd->heredoc_fd >= 0)
	{
		dup2(cmd->heredoc_fd, STDIN_FILENO);
		close(cmd->heredoc_fd);
	}
}

static void	setup_redirections(t_cmd *cmd)
{
	if (cmd->redir_in_fd >= 0)
	{
		dup2(cmd->redir_in_fd, STDIN_FILENO);
		close(cmd->redir_in_fd);
	}
	if (cmd->redir_out_fd >= 0)
	{
		dup2(cmd->redir_out_fd, STDOUT_FILENO);
		close(cmd->redir_out_fd);
	}
	setup_heredoc_input(cmd);
}

static void	execute_child(t_cmd *cmd)
{
	setup_redirections(cmd);
	if (is_builtin(cmd->argv[0]) == 1)
	{
		exec_builtin(cmd);
		exit(g_exit_status);
	}
	else
	{
		execve(cmd->argv[0], cmd->argv, environ);
		perror("minishell");
		exit(1);
	}
}
// tenho que diminuir aqui
int	execute_pipeline(t_cmd *cmd_list)
{
	t_cmd	*cmd;
	pid_t	pids[256];
	int		pipefds[512];
	int		i;
	int		cmd_count;
	int		pipe_count;

	i = 0;
	cmd = cmd_list;
	cmd_count = 0;
	while (cmd)
	{
		cmd_count++;
		cmd = cmd->next;
	}
	pipe_count = cmd_count - 1;
	if (pipe_count > 0)
	{
		if (open_pipes(cmd_list, pipefds) == -1)
		{
			perror("pipe");
			return (1);
		}
	}
	cmd = cmd_list;
	i = 0;
	while (cmd)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			setup_pipes(cmd, i, pipe_count, pipefds);
			execute_child(cmd);
		}
		i++;
		cmd = cmd->next;
	}
	close_all_pipes(pipefds, pipe_count);
	g_exit_status = wait_for_children(pids, cmd_count);
	return (g_exit_status);
}
