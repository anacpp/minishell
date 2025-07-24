#include "../../includes/minishell.h"

static void dup_and_close(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		dup2(oldfd, newfd);
		close(oldfd);
	}
}

static void setup_child_pipes(t_cmd *cmd, int *pipe_fds, int in_fd)
{
	dup_and_close(in_fd, STDIN_FILENO);
	if (cmd->next)
	{
		close(pipe_fds[0]);
		dup_and_close(pipe_fds[1], STDOUT_FILENO);
	}
}

void execute_child_process(t_cmd *cmd, int *pipe_fds, int in_fd, t_shell *shell_context)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_child_pipes(cmd, pipe_fds, in_fd);
	if (cmd->redirs)
		setup_redir(cmd->redirs);
	if (cmd->redirs)
		unlink_heredocs(cmd->redirs);
	if (is_builtin(cmd))
		exit(run_builtin(cmd, shell_context));
	exec_external(cmd, shell_context);
	exit(EXIT_FAILURE);
}
