#include "../../includes/minishell.h"

static int open_pipes(t_cmd *cmd_list, int *pipefds)
{
    t_cmd *cmd;
    int i;

    i = 0;
    cmd = cmd_list;
    while (cmd && cmd->next)
    {
        if (pipe(pipefds + i * 2) == -1)
            return (-1);
        i++;
        cmd = cmd->next;
    }
    return (i);
}

static void close_all_pipes(int *pipefds, int count)
{
    int i;

    i = 0;
    while (i < count * 2)
    {
        close(pipefds[i]);
        i++;
    }
}

static void setup_pipes(t_cmd *cmd, int i, int pipe_count, int *pipefds)
{
    if (i > 0)
    {
        dup2(pipefds[(i - 1) * 2], STDIN_FILENO);
    }
    if (i < pipe_count)
    {
        dup2(pipefds[i * 2 + 1], STDOUT_FILENO);
    }
    close_all_pipes(pipefds, pipe_count);
}
