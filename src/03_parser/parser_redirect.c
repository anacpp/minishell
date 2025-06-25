/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacques <rjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by rjacques          #+#    #+#             */
/*   Updated: 2025/06/21 03:24:47 by rjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_redir	*create_redir_node(t_token_type type, char *filename);
static void		append_redir_to_cmd(t_cmd *cmd, t_redir *new_redir);

int	add_redirection(t_cmd *cmd, t_token **token_ptr)
{
	t_token	*redir_token;
	t_token	*filename_token;
	t_redir	*new_redir;
	char	*final_filename;

	redir_token = *token_ptr;
	filename_token = get_next_token(redir_token);
	if (!filename_token)
		return (error_unexpected_token(NULL));
	if (token_is_operator(filename_token))
		return (error_unexpected_token(filename_token));
	if (filename_token->value && filename_token->value[0] == '\0')
		return (report_syntax_error("ambiguous redirect", NULL));
	final_filename = remove_quotes(filename_token->value);
	if (!final_filename || final_filename[0] == '\0')
	{
		if (final_filename)
			free(final_filename);
		return (report_syntax_error("ambiguous redirect", NULL));
	}
	new_redir = create_redir_node(redir_token->type, final_filename);
	append_redir_to_cmd(cmd, new_redir);
	*token_ptr = filename_token;
	return (1);
}

static t_redir	*create_redir_node(t_token_type type, char *filename)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		handle_error(NULL, "malloc failed", 1, 1);
	new_redir->type = type;
	new_redir->filename = filename;
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