/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 04:50:40 by rdos-san          #+#    #+#             */
/*   Updated: 2025/06/21 05:19:31 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
	{
		ft_printf("    argv[%d]: \"%s\"\n", i, argv[i]);
		i++;
	}
}

static void	print_redirs(t_redir *redirs)
{
	if (!redirs)
		ft_printf("    (none)\n");
	while (redirs)
	{
		ft_printf("    Type: %s, File: \"%s\"\n",
			token_type_str(redirs->type), redirs->filename);
		redirs = redirs->next;
	}
}

void	print_command_table(t_cmd *cmds)
{
	int	cmd_num;

	cmd_num = 1;
	while (cmds)
	{
		ft_printf("\n--- Command %d ---\n", cmd_num++);
		ft_printf("  Args (argv):\n");
		print_argv(cmds->argv);
		ft_printf("  Redirections:\n");
		print_redirs(cmds->redirs);
		cmds = cmds->next;
	}
}