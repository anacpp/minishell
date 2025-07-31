/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/24 15:33:40 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	has_unclosed_quotes(const char *input)
{
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	while (*input)
	{
		update_quote_state(*input, &in_single, &in_double);
		input++;
	}
	return (in_single || in_double);
}

static int	contains_unsupported_logical_operators(const char *input)
{
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	while (*input)
	{
		update_quote_state(*input, &in_single, &in_double);
		if (!in_single && !in_double)
		{
			if ((*input == '&' && *(input + 1) == '&') || (*input == '|'
					&& *(input + 1) == '|'))
				return (1);
		}
		input++;
	}
	return (0);
}

static int	contains_stray_ampersand(const char *input)
{
	int	in_single;
	int	in_double;
	int	i;

	in_single = 0;
	in_double = 0;
	i = 0;
	while (input[i])
	{
		update_quote_state(input[i], &in_single, &in_double);
		if (input[i] == '&' && !in_single && !in_double)
		{
			if (input[i + 1] == '&')
				i++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	is_valid_input_syntax(const char *input)
{
	t_token	ampersand_token;

	if (!input || *input == '\0')
		return (0);
	if (has_unclosed_quotes(input))
		return (report_syntax_error("syntax error: unclosed quotes", NULL));
	if (contains_unsupported_logical_operators(input))
		return (report_syntax_error("syntax error: unsupported operator",
				NULL));
	if (contains_stray_ampersand(input))
	{
		ampersand_token.value = "&";
		ampersand_token.type = T_WORD;
		ampersand_token.next = NULL;
		return (report_syntax_error("syntax error near unexpected token",
				&ampersand_token));
	}
	return (1);
}
