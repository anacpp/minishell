#include "../../includes/minishell.h"

static void close_and_update_fd(int *in_fd, int *pipe_fds, int has_next)
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (has_next)
	{
		close(pipe_fds[1]);
		*in_fd = pipe_fds[0];
	}
}

static int create_and_fork(t_cmd *current, t_fork_ctx *ctx, t_shell *shell_context)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		execute_child_process(current, ctx->pipe_fds, ctx->in_fd, shell_context);
	save_pid(pid, ctx->num_pids, ctx->child_pids);
	return (0);
}

void unlink_heredocs(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == T_REDIR_IN
			&& redir->filename
			&& ft_strncmp(redir->filename, "./.heredoc_", 11) == 0)
			unlink(redir->filename);
		redir = redir->next;
	}
}

static void init_pipeline_ctx(t_pipeline_ctx *ctx)
{
	ctx->in_fd = STDIN_FILENO;
	ctx->num_pids = 0;
	ctx->fork_ctx.pipe_fds = ctx->pipe_fds;
	ctx->fork_ctx.num_pids = &ctx->num_pids;
	ctx->fork_ctx.child_pids = ctx->child_pids;
}

int execute_pipeline(t_cmd *cmds, t_shell *shell_context)
{
	t_pipeline_ctx ctx;
	t_cmd *current;

	init_pipeline_ctx(&ctx);
	current = cmds;
	while (current)
	{
		ctx.fork_ctx.in_fd = ctx.in_fd;
		if (current->next && pipe(ctx.pipe_fds) == -1)
			return (perror("pipe"), 1);
		if (create_and_fork(current, &ctx.fork_ctx, shell_context))
			return (1);
		close_and_update_fd(&ctx.in_fd, ctx.pipe_fds, current->next != NULL);
		current = current->next;
	}
	wait_all_children(&ctx.num_pids, ctx.child_pids);
	return (g_signal_status);
}
