/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by rjacques          #+#    #+#             */
/*   Updated: 2025/06/21 04:52:07 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_argv(char **argv);
static void	free_redirections(t_redir *redirs);

void	free_command_table(t_cmd *cmd_table)
{
	t_cmd	*tmp_cmd;

	while (cmd_table)
	{
		tmp_cmd = cmd_table->next;
		free_redirections(cmd_table->redirs);
		free_argv(cmd_table->argv);
		free(cmd_table);
		cmd_table = tmp_cmd;
	}
}

static void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

static void	free_redirections(t_redir *redirs)
{
	t_redir	*tmp_redir;

	while (redirs)
	{
		tmp_redir = redirs->next;
		free(redirs->filename);
		free(redirs);
		redirs = tmp_redir;
	}
}
