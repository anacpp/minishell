#include "../../includes/minishell.h"

int is_builtin(t_cmd *cmd)
{
    const char *builtins[] = {"cd", "echo", "exit", "export", "unset", "pwd", "env", NULL};
    int i;

    i = 0;
    while (builtins[i])
    {
        if (ft_strcmp(cmd->argv[0], builtins[i]) == 0)
            return 1;
        i++;
    }
    return 0;
}

static int is_executable_path(char *path)
{
    if (!path)
        return (0);
    if (access(path, X_OK) == 0)
        return (1);
    return (0);
}

int is_external_command(t_cmd *cmd)
{
    char *cmd_name;
    char *path_env;

    if (!cmd || !cmd->argv || !cmd->argv[0])
        return 0;
    cmd_name = cmd->argv[0];
    if (cmd_name[0] == '/' || (cmd_name[0] == '.' && (cmd_name[1] == '/' || (cmd_name[1] == '.' && cmd_name[2] == '/'))))
        return (is_executable_path(cmd_name));
    path_env = getenv("PATH");
    if (!path_env)
        return 0;
    return ; // aqui eu preciso retornar o path da função externa... preciso fazer essa função ainda
}

void	setup_redir(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == T_REDIR_IN)
			fd = open(redir->filename, O_RDONLY);
		else if (redir->type == T_REDIR_OUT)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == T_APPEND) 
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == T_HEREDOC) 
			fd = create_heredoc(redir->filename);
		else
		{
			redir = redir->next;
			continue ;
		}
		if (fd < 0)
		{
			perror(redir->filename);
			exit (EXIT_FAILURE);
		}
		if (redir->type == T_REDIR_IN || redir->type == T_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
}

/**
 * Salva os FDs padrão (stdin, stdout) em `fds[0]` e `fds[1]`
 */
void	save_stdio(int fds[2])
{
	fds[0] = dup(STDIN_FILENO);
	fds[1] = dup(STDOUT_FILENO);
	if (fds[0] < 0 || fds[1] < 0)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}
}

/**
 * Restaura os FDs padrão após redirecionamento de builtins
 */
void	restore_stdio(int fds[2])
{
	if (dup2(fds[0], STDIN_FILENO) < 0)
	{
		perror("restore stdin");
		exit(EXIT_FAILURE);
	}
	if (dup2(fds[1], STDOUT_FILENO) < 0)
	{
		perror("restore stdout");
		exit(EXIT_FAILURE);
	}
	close(fds[0]);
	close(fds[1]);
}


