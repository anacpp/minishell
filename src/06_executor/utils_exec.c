/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/06/11 17:13:15 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	TODO: NORMA, NORMINETTE, VALGRIND

*/

#include "../../includes/minishell.h"

int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != T_PIPE)
	{
		if (token->type == T_WORD || token->type == T_ARGUMENT)
			count++;
		token = token->next;
	}
	return (count);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
}

void	free_redirects(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd->argv && cmd->argv[i])
	{
		free(cmd->argv[i]);
		i++;
	}
	free(cmd->argv);
	free_redirects(cmd->redir);
	free(cmd);
}

void	free_cmd_list(t_cmd *head)
{
	t_cmd	*tmp;

	while (head)
	{
		tmp = head->next;
		free_cmd(head);
		head = tmp;
	}
}
