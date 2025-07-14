#include "../../includes/minishell.h"

int is_builtin(t_cmd *cmd)
{
    const char *builtins[] = {"cd", "echo", "exit", "export", "unset", "pwd", "env", NULL};
    int i;

    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (0);

    i = 0;
    while (builtins[i])
    {
        if (ft_strcmp(cmd->argv[0], builtins[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}

/**
 * @brief Configura os redirecionamentos de entrada e saída para os comandos.
 * Cada redirecionamento é processado e o descritor de arquivo correspondente é aberto.
 * @param redir A lista de redirecionamentos a serem configurados.
 * @return void
 * */
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
 * @brief Salva os descritores de arquivo padrão (stdin e stdout) para posterior restauração.
 * @param fds Array onde os descritores serão salvos.
 */
void	save_stdio(int fds[2])
{
	//dup: duplica o descritor de arquivo, retornando um novo descritor que aponta para o mesmo arquivo.
	fds[0] = dup(STDIN_FILENO);
	fds[1] = dup(STDOUT_FILENO);
	if (fds[0] < 0 || fds[1] < 0)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Restaura os descritores de arquivo padrão (stdin e stdout) a partir dos valores salvos.
 * @param fds Array contendo os descritores de arquivo a serem restaurados.
 */
void	restore_stdio(int fds[2])
{
	//dup2: para de apontar o descritor de arquivo especificado para o descritor de arquivo padrão.
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


