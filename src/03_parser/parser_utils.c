/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by rjacques          #+#    #+#             */
/*   Updated: 2025/07/16 16:42:35 by acesar-p         ###   ########.fr       */
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

int	ft_count_args(char **argv)
{
	int	count;

	count = 0;
	while (argv && argv[count])
		count++;
	return (count);
}
