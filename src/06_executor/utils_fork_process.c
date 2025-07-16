/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fork_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:36:30 by rjacques          #+#    #+#             */
/*   Updated: 2025/07/16 19:50:56 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_pid(pid_t pid)
{
	if (g_num_pids < MAX_PIDS)
	{
		g_child_pids[g_num_pids] = pid;
		g_num_pids++;
	}
	else
		ft_printf("minishell: too many child processes\n");
}

int	wait_pid(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (1);
	if (WIFEXITED(status))
		g_signal_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_signal_status = 128 + WTERMSIG(status);
	return (0);
}

void	wait_all_children(void)
{
	int	i;

	i = 0;
	while (i < g_num_pids)
	{
		wait_pid(g_child_pids[i]);
		i++;
	}
	g_num_pids = 0;
}
