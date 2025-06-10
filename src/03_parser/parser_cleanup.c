/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacques <rjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by rjacques          #+#    #+#             */
/*   Updated: 2025/06/10 00:24:22 by rjacques         ###   ########.fr       */
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

void	print_command_table(t_cmd *cmds)
{
	int		i;
	int		cmd_num;
	t_redir	*redirs;

	cmd_num = 1;
	while (cmds)
	{
		printf("\n--- Command %d ---\n", cmd_num++);
		printf("  Args (argv):\n");
		if (cmds->argv)
		{
			i = 0;
			while (cmds->argv[i])
			{
				printf("    argv[%d]: \"%s\"\n", i, cmds->argv[i]);
				i++;
			}
		}
		printf("  Redirections:\n");
		if (!cmds->redirs)
			printf("    (none)\n");
		redirs = cmds->redirs;
		while (redirs)
		{
			printf("    Type: %s, File: \"%s\"\n", token_type_str(redirs->type),
				redirs->filename);
			redirs = redirs->next;
		}
		cmds = cmds->next;
	}
}
