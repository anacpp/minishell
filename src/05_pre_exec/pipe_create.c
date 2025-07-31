/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/24 15:53:19 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Creates the necessary pipes to connect multiple chained commands
	(for example: ls | grep a | wc -l).

	Functions:
	- create_pipes: allocates and creates all
	 pipes (1 less than the number of commands).
	- free_pipes: frees all created pipes.
	- handle_pipe_error: displays error, frees resources and prevents leaks.

	Returns an array of file descriptor pairs
	used in redirection between processes.
*/

#include "../../includes/minishell.h"

static void	free_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pipes[i])
			free(pipes[i]);
		i++;
	}
	free(pipes);
}

static void	handle_pipe_error(int **pipes, int created, const char *msg)
{
	perror(msg);
	free_pipes(pipes, created);
}

int	**create_pipes(int total_cmds)
{
	int	**pipes;
	int	total_pipes;
	int	i;

	total_pipes = total_cmds - 1;
	pipes = malloc(sizeof(int *) * total_pipes);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < total_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			handle_pipe_error(pipes, i, "malloc");
			return (NULL);
		}
		if (pipe(pipes[i]) == -1)
		{
			handle_pipe_error(pipes, i + 1, "pipe");
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
