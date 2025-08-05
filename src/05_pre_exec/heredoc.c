/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/08/05 17:23:10 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Implements the behavior of heredoc (<<), which reads user input
	until a delimiter is found.

	Functions:
	- create_heredoc: creates and returns a temporary file
	with the heredoc content.
	- heredoc_loop: reads line by line until the delimiter
	and writes to the file.
	- check_delimiter: compares the entered line with the delimiter.
	- print_prompt: displays the prompt "> ".

	This content will be used as standard input (stdin) for the command.
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
	const char	*prompt = "heredoc> ";

	write(1, prompt, strlen(prompt));
}

static void	heredoc_loop(int fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		print_prompt();
		line = readline("");
		if (!line)
		{
			write(1, "warning: heredoc ended by EOF\n", 31);
			break ;
		}
		if (check_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		write(fd, line, (int)ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	create_heredoc(char *delimiter, char **tmp_path)
{
	int		fd;
	char	*tmpfile;

	tmpfile = malloc(256);
	if (!tmpfile)
		handle_error("heredoc", "malloc failed", 1, 1);
	fd = create_temp_file(tmpfile, 256);
	if (fd < 0)
		handle_error("heredoc", strerror(errno), 1, 1);
	heredoc_loop(fd, delimiter);
	close(fd);
	*tmp_path = tmpfile;
	return (0);
}
