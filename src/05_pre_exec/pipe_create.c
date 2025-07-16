/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/16 19:36:36 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Cria os pipes necessários para conectar múltiplos comandos encadeados
	(por exemplo: ls | grep a | wc -l).

	Funções:
	- create_pipes: aloca e cria todos os
	 pipes (1 a menos que o número de comandos).
	- free_pipes: libera todos os pipes criados.
	- handle_pipe_error: exibe erro, libera recursos e evita vazamentos.

	Retorna um array de pares de file descriptors
	usados no redirecionamento entre processos.
*/

/*
	TODO: NORMINETTE

	DONE :
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
// Teste

/*TESTEs /
int			**create_pipes(int total_cmds);
void		print_pipes(int **pipes, int total_pipes);
void		free_pipes(int **pipes, int count);

#include <stdio.h>

void	print_pipes(int **pipes, int n_pipes)
{
	int	i;

	i = 0;
	while (i < n_pipes)
	{
		printf("Pipe[%d][READ]: %d\n", i, pipes[i][0]);
		printf("Pipe[%d][WRITE]: %d\n", i, pipes[i][1]);
		i++;
	}
}

int	main(void)
{
	int		total_pipes;
	int		**pipes;
	char	msg[] = "Hello pipe!";
	char	buf[100];
	int		rd;

	int	total_cmds = 3; // Teste com 3 comandos → 2 pipes
	total_pipes = total_cmds - 1;
	pipes = create_pipes(total_cmds);
	if (!pipes)
	{
		printf("Erro ao criar pipes.\n");
		return (1);
	}
	print_pipes(pipes, total_pipes);
	write(pipes[0][1], msg, sizeof(msg));
	rd = read(pipes[0][0], buf, sizeof(msg));
	buf[rd] = '\0';
	printf("Lido do pipe: %s\n", buf);
	for (int i = 0; i < total_pipes; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	free_pipes(pipes, total_pipes);
	return (0);
}

*/