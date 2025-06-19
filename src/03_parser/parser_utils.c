/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacques <rjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by rjacques          #+#    #+#             */
/*   Updated: 2025/06/10 00:18:36 by rjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection_token_type(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT || type == T_HEREDOC
		|| type == T_APPEND);
}

int	token_is_redirection(t_token *token)
{
	if (!token)
		return (0);
	return (is_redirection_token_type(token->type));
}

int	token_is_operator(t_token *token)
{
	if (!token)
		return (0);
	return (token_is_redirection(token) || token->type == T_PIPE);
}

t_token	*get_next_token(t_token *current)
{
	if (current)
		return (current->next);
	return (NULL);
}
