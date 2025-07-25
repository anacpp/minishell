/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/05/21 17:06:23 by acesar-p         ###   ########.fr       */
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

static int	has_malformed_redirects(const char *input)
{
	int	i;
	int	in_single;
	int	in_double;
	
	i = 0;
	in_single = 0;
	in_double = 0;
	while (input[i])
	{
		update_quote_state(input[i], &in_single, &in_double);
		if (!in_single && !in_double && is_redirect(input[i]))
		{
			if (skip_redirect_and_check_error(input, &i))
				return (1);
		}
		else
			i++;
	}
	return (0);
}

static int	contain_pipe_error(const char *input)
{
	int	in_single;
	int	in_double;
	int	expect_next;

	in_single = 0;
	in_double = 0;
	expect_next = 0;
	while (*input)
	{
		update_quote_state(*input, &in_single, &in_double);
		if (*input == '|' && !in_single && !in_double)
		{
			if (expect_next)
				return (1);
			expect_next = 1;
		}
		else if (*input != ' ' && *input != '\t')
			expect_next = 0;
		input++;
	}
	return (expect_next);
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

void	is_valid_input_syntax(char *input)
{
	if (!input || !*input)
	{
		handle_error(input, NULL, 1);
		return ;
	}
	if (has_unclosed_quotes((char *)input))
		handle_error(input, "Syntax error: unclosed quotes", 2);
	else if (contain_pipe_error((char *)input) || *input == '|')
		handle_error(input, "Syntax error: unexpected pipe", 2);
	else if (contains_unsupported_logical_operators((char *)input))
		handle_error(input, "Syntax error: unsupported logical operator", 2);
	else if (has_malformed_redirects((char *)input))
		handle_error(input, "Syntax error: malformed redirection", 2);
}
