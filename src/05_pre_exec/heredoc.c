/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/06/11 17:14:43 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	TODO: NORMA, VALGRIND

    DONE : NORMINETTE - OK
*/
#include "../../includes/minishell.h"

static int	check_delimiter(const char *line, const char *delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i])
	{
		if (line[i] != delimiter[i])
			return (0);
		i++;
	}
	if (line[i] != '\0')
		return (0);
	return (1);
}

static void	print_prompt(void)
{
	write(1, "> ", 2);
}

static void	heredoc_loop(int fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		print_prompt();
		line = readline("");
		if (!line)
			break ;
		if (check_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		write(fd, line, (int)strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	create_heredoc(char *delimiter)
{
	int		fd;
	char	*tmpfile;

	tmpfile = "/tmp/minishell_heredoc";
	fd = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		handle_error("heredoc", strerror(errno), 1, 1);
	heredoc_loop(fd, delimiter);
	close(fd);
	fd = open(tmpfile, O_RDONLY);
	if (fd < 0)
		handle_error("heredoc", strerror(errno), 1, 1);
	return (fd);
}
