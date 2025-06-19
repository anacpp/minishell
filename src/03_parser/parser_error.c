/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacques <rjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by rjacques          #+#    #+#             */
/*   Updated: 2025/06/10 00:24:01 by rjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	report_syntax_error(const char *message, t_token *error_token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (ft_strnstr(message, "token", ft_strlen(message)))
	{
		ft_putstr_fd(message, STDERR_FILENO);
		if (error_token && error_token->value)
		{
			ft_putstr_fd(" `", STDERR_FILENO);
			ft_putstr_fd(error_token->value, STDERR_FILENO);
			ft_putstr_fd("'", STDERR_FILENO);
		}
		else
			ft_putstr_fd(" `newline'", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(message, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	return (0);
}

int	error_unexpected_token(t_token *token)
{
	return (report_syntax_error("syntax error near unexpected token", token));
}
