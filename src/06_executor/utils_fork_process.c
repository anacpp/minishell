/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fork_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:36:30 by rjacques          #+#    #+#             */
/*   Updated: 2025/07/24 17:25:52 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_pid(pid_t pid, int *num_pids, pid_t *child_pids)
{
	if (*num_pids < MAX_PIDS)
	{
		child_pids[*num_pids] = pid;
		(*num_pids)++;
	}
	else
		ft_printf("minishell: too many child processes\n");
}

int	wait_pid(pid_t pid)
{
	int	status;
	int sig;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("minishell: waitpid");
		return (1);
	}
	if (WIFEXITED(status))
		g_signal_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		g_signal_status = 128 + sig;
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	}
	return (0);
}


void	wait_all_children(int *num_pids, pid_t *child_pids)
{
	int	i;

	i = 0;
	while (i < *num_pids)
	{
		wait_pid(child_pids[i]);
		i++;
	}
	*num_pids = 0;
}
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