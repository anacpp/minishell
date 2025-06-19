/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/06/11 17:12:11 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	TODO: NORMA, NORMINETTE, VALGRIND

*/

#include "../../includes/minishell.h"

static char	**extract_args(t_token **tokens)
{
	int		argc;
	char	**argv;
	int		i;

	argc = count_args(*tokens);
	argv = malloc(sizeof(char *) * (argc + 1));
	i = 0;
	while (*tokens && (*tokens)->type != T_PIPE)
	{
		if ((*tokens)->type == T_WORD || (*tokens)->type == T_ARGUMENT)
			argv[i++] = ft_strdup((*tokens)->value);
		else if ((*tokens)->type == T_REDIR_IN || (*tokens)->type == T_REDIR_OUT
			|| (*tokens)->type == T_APPEND || (*tokens)->type == T_HEREDOC)
			*tokens = (*tokens)->next;
		*tokens = (*tokens)->next;
	}
	argv[i] = NULL;
	return (argv);
}

static t_redir	*extract_redirects(t_token **tokens)
{
	t_redir	*head;
	t_token	*curr;
	t_redir	*new;

	head = NULL, *tail;
	head = NULL, tail = NULL;
	curr = *tokens;
	while (curr && curr->type != T_PIPE)
	{
		if (curr->type == T_REDIR_IN || curr->type == T_REDIR_OUT
			|| curr->type == T_APPEND || curr->type == T_HEREDOC)
		{
			new = malloc(sizeof(t_redir));
			if (!new)
				return (NULL);
			new->type = curr->type;
			curr = curr->next;
			if (!curr || (curr->type != T_WORD && curr->type != T_ARGUMENT))
				return (NULL);
			new->filename = ft_strdup(curr->value);
			new->next = NULL;
			if (!head)
				head = new;
			else
				tail->next = new;
			tail = new;
		}
		curr = curr->next;
	}
	return (head);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd *head = NULL, *tail = NULL;

	while (tokens)
	{
		t_cmd *cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			return (NULL);
		cmd->argv = extract_args(&tokens);
		cmd->redir = extract_redirects(&tokens);
		cmd->pipe_in = 0;
		cmd->pipe_out = 1;
		cmd->next = NULL;

		if (!head)
			head = cmd;
		else
			tail->next = cmd;
		tail = cmd;

		if (tokens && tokens->type == T_PIPE)
			tokens = tokens->next;
	}
	return (head);
}