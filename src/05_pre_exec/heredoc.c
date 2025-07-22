/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/22 18:14:54 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Implementa o comportamento do heredoc (<<), que lê entradas do usuário
	até encontrar um delimitador.

	Funções:
	- create_heredoc: cria e retorna um arquivo
	temporário com o conteúdo do heredoc.
	- heredoc_loop: lê linha por linha até 
	o delimitador e escreve no arquivo.
	- check_delimiter: compara a linha digitada com o delimitador.
	- print_prompt: exibe o prompt "> ".

	Esse conteúdo será usado como entrada padrão (stdin) no comando.
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
	const char *prompt = "heredoc> ";
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
