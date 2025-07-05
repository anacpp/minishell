/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/06/11 17:15:01 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	TODO: NORMA, NORMINETTE, VALGRIND

     DONE : NORMINETTE - OK

*/
#include "../../includes/minishell.h"

static int	open_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		handle_error(file, strerror(errno), 1, 1);
	return (fd);
}

static int	open_outfile(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		handle_error(file, strerror(errno), 1, 1);
	return (fd);
}

static int	append_outfile(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		handle_error(file, strerror(errno), 1, 1);
	return (fd);
}

void	apply_redirects(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		fd = -1;
		if (redir->type == T_REDIR_IN)
			fd = open_infile(redir->filename);
		else if (redir->type == T_REDIR_OUT)
			fd = open_outfile(redir->filename);
		else if (redir->type == T_APPEND)
			fd = append_outfile(redir->filename);
		else if (redir->type == T_HEREDOC)
			fd = create_heredoc(redir->filename);
		if (redir->type == T_REDIR_IN || redir->type == T_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
}
