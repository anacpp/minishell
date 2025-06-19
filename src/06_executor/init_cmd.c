/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/06/11 17:12:18 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	TODO: NORMA, NORMINETTE, VALGRIND

*/

#include "../../includes/minishell.h"

static int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
			count++;
		token = token->next;
	}
	return (count);
}

static int	count_redirs(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type >= REDIR_IN && token->type <= REDIR_APPEND)
		{
			if (token->next && token->next->type == WORD)
			{
				count++;
				token = token->next;
			}
		}
		token = token->next;
	}
	return (count);
}

static char	**init_args(t_token *token)
{
	int		argc;
	char	**args;
	int		i;

	argc = count_args(token);
	args = malloc(sizeof(char *) * (argc + 1));
	i = 0;
	if (!args)
		return (NULL);
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
		{
			args[i++] = ft_strdup(token->str);
			if (!args[i - 1])
			{
				free_split(args);
				return (NULL);
			}
		}
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}

static t_redirect	*init_redirections(t_token *token)
{
	int			count;
	t_redirect	*redir;
	int			i;

	count = count_redirs(token);
	redir = malloc(sizeof(t_redirect) * (count + 1));
	i = 0;
	if (!redir)
		return (NULL);
	while (token && token->type != PIPE)
	{
		if (token->type >= REDIR_IN && token->type <= REDIR_APPEND)
		{
			if (token->next && token->next->type == WORD)
			{
				redir[i].type = token->type;
				redir[i].file = ft_strdup(token->next->str);
				if (!redir[i].file)
				{
					while (i-- > 0)
						free(redir[i].file);
					free(redir);
					return (NULL);
				}
				i++;
				token = token->next;
			}
		}
		token = token->next;
	}
	redir[i].file = NULL;
	return (redir);
}

static t_cmd	*create_cmd(t_token *token)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = init_args(token);
	cmd->redir = init_redirections(token);
	cmd->pipe_in = -1;
	cmd->pipe_out = -1;
	cmd->pid = -1;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*init_cmd(t_token *token)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*new_cmd;

	head = NULL;
	tail = NULL;
	while (token)
	{
		new_cmd = create_cmd(token);
		if (!new_cmd)
		{
			free_cmd(head);
			return (NULL);
		}
		if (!head)
			head = new_cmd;
		else
			tail->next = new_cmd;
		tail = new_cmd;
		while (token && token->type != PIPE)
			token = token->next;
		if (token && token->type == PIPE)
			token = token->next;
	}
	return (head);
}
