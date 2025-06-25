/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacques <rjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by rjacques          #+#    #+#             */
/*   Updated: 2025/06/21 02:47:02 by rjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_token_after_redir(t_token *redir_token)
{
	t_token	*next_t;

	if (!redir_token)
		return (0);
	next_t = get_next_token(redir_token);
	if (!next_t)
		return (report_syntax_error(NULL, NULL));
	if (token_is_operator(next_t))
		return (error_unexpected_token(next_t));
	if (next_t->type != T_WORD)
	{
		return (error_unexpected_token(next_t));
	}
	return (0);
}

int	validate_empty_filename_after_redir(t_token *filename_token)
{
	if (filename_token && filename_token->type == T_WORD
		&& filename_token->value && filename_token->value[0] == '\0')
	{
		return (report_syntax_error("ambiguous redirect", NULL));
	}
	return (0);
}

int	validate_command_segment_start(t_token *first_token_in_segment)
{
	if (!first_token_in_segment)
		return (0);
	if (first_token_in_segment->type == T_PIPE)
		return (error_unexpected_token(first_token_in_segment));
	if (token_is_redirection(first_token_in_segment))
	{
		return (report_syntax_error("missing command", NULL));
	}
	return (0);
}

int	validate_pipe_placement(t_token *pipe_token, int is_first_overall)
{
	t_token	*next_t;
	t_token	*error_token;

	if (!pipe_token || pipe_token->type != T_PIPE)
		return (0);
	if (is_first_overall)
		return (error_unexpected_token(pipe_token));
	next_t = get_next_token(pipe_token);
	if (!next_t || next_t->type == T_PIPE)
	{
		if (next_t)
			error_token = next_t;
		else
			error_token = pipe_token;
		return (error_unexpected_token(error_token));
	}
	return (0);
}