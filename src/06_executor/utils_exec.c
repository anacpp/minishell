/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:36:30 by rjacques          #+#    #+#             */
/*   Updated: 2025/07/24 17:27:25 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_cmd *cmd)
{
	const char	*builtins[] = {"cd", "echo", "exit", "export", "unset", "pwd",
		"env", NULL};
	int			i;

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
 * @brief Configures input and output redirections for commands.

	* Each redirection is processed and the corresponding 
	file descriptor is opened.
 * @param redir The list of redirections to be configured.
 * @return void
 * */

static int	open_redir_file(t_redir *redir)
{
	if (redir->type == T_REDIR_IN)
		return (open(redir->filename, O_RDONLY));
	else if (redir->type == T_REDIR_OUT)
		return (open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (redir->type == T_APPEND)
		return (open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

static void	apply_redir(t_redir *redir, int fd)
{
	if (redir->type == T_REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	setup_redir(t_redir *redir)
{
	int fd;

	while (redir)
	{
		if (redir->type == T_REDIR_IN || redir->type == T_REDIR_OUT || redir->type == T_APPEND)
		{
			fd = open_redir_file(redir);
			if (fd < 0)
			{
				perror(redir->filename);
				exit(EXIT_FAILURE);
			}
			apply_redir(redir, fd);
		}
		redir = redir->next;
	}
}


/**
 * @brief Saves the standard file descriptors (stdin and stdout)
 * for later restoration.
 * @param fds Array where the descriptors will be saved.
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


