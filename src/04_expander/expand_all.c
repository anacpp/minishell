/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expande_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/06/11 17:14:43 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	TODO: NORMINETTE

    DONE : 
*/

#include "../includes/minishell.h"

void	expand_argv(char **argv, int last_status)
{
	int		i;
	char	*expanded;

	i = 0;
	while (argv && argv[i])
	{
		expanded = expand_variables(argv[i], last_status);
		free(argv[i]);
		argv[i] = expanded;
		i++;
	}
}

void	expand_redirs(t_redir *redir, int last_status)
{
	char	*expanded;

	while (redir)
	{
		if (redir->filename)
		{
			expanded = expand_variables(redir->filename, last_status);
			free(redir->filename);
			redir->filename = expanded;
		}
		redir = redir->next;
	}
}

void	expand_all_variables(t_cmd *cmds, int last_status)
{
	while (cmds)
	{
		expand_argv(cmds->argv, last_status);
		expand_redirs(cmds->redirs, last_status);
		cmds = cmds->next;
	}
}
