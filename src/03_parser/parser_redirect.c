/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacques <rjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by rjacques          #+#    #+#             */
/*   Updated: 2025/06/10 00:19:48 by rjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_redir	*create_redir_node(t_token *redir_t, t_token *file_t);
static void		append_redir_to_cmd(t_cmd *cmd, t_redir *new_redir);

int	add_redirection(t_cmd *cmd, t_token **token_ptr)
{
	t_token	*redir_token;
	t_token	*filename_token;
	t_redir	*new_redir;

	redir_token = *token_ptr;
	filename_token = get_next_token(redir_token);
	if (!filename_token)
		return (error_unexpected_token(NULL));
	if (token_is_operator(filename_token))
		return (error_unexpected_token(filename_token));
	if (filename_token->value && filename_token->value[0] == '\0')
		return (report_syntax_error("ambiguous redirect", NULL));
	new_redir = create_redir_node(redir_token, filename_token);
	append_redir_to_cmd(cmd, new_redir);
	*token_ptr = filename_token;
	return (1);
}

static t_redir	*create_redir_node(t_token *redir_t, t_token *file_t)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		handle_error(NULL, "malloc failed", 1, 1);
	new_redir->type = redir_t->type;
	new_redir->filename = remove_quotes(file_t->value);
	new_redir->next = NULL;
	return (new_redir);
}

static void	append_redir_to_cmd(t_cmd *cmd, t_redir *new_redir)
{
	t_redir	*last;

	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}
