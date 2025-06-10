/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacques <rjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/06/10 00:17:04 by rjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* OBS:
	-> NORMINETTE - ok
	-> CHECK LEAKS - ok (LEAKS APENAS DA BIBLIOTECA READLINE, QUE SÃO ESPERADAS)
 */

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

int	is_valid_input_syntax(const char *input)
{
	if (!input || *input == '\0')
		return (1);
	if (has_unclosed_quotes(input))
		return (report_syntax_error("syntax error: unclosed quotes", NULL));
	if (contains_unsupported_logical_operators(input))
		return (report_syntax_error("syntax error: unsupported operator",
				NULL));
	return (1);
}
