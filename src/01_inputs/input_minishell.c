/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacques <rjacques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/06/09 15:11:15 by rjacques         ###   ########.fr       */
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
	int		in_single;
	int		in_double;
	int		expect_next;
	char	*trimmed;
	char	*ptr;

	in_single = 0;
	in_double = 0;
	expect_next = 1;
	trimmed = ft_strtrim(input, " \t");
	if (!trimmed)
		return (0);
	ptr = trimmed;
	while (*ptr)
	{
		update_quote_state(*ptr, &in_single, &in_double);
		if (*ptr == '|' && !in_single && !in_double)
		{
			if (expect_next)
			{
				free(trimmed);
				return (1);
			}
			expect_next = 1;
		}
		else if (*ptr != ' ' && *ptr != '\t')
			expect_next = 0;
		ptr++;
	}
	free(trimmed);
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

/**
 * @brief Função principal de validação que orquestra todas as verificações.
 *
 * @details Invoca uma série de funções de verificação em uma ordem específica
 * para garantir que o erro mais relevante seja reportado primeiro. Se qualquer
 * verificação falhar, ela chama `report_syntax_error` e retorna `0`.
 *
 * @param input A string de entrada bruta a ser validada.
 * @return Retorna `1` se a sintaxe for considerada válida para prosseguir
 * para a tokenização, ou `0` se um erro for encontrado.
 */
int	is_valid_input_syntax(const char *input)
{
	if (!input || *input == '\0')
		return (1);
	if (has_unclosed_quotes(input))
		return (report_syntax_error("syntax error: unclosed quotes", NULL));
	// A verificação de operadores não suportados deve vir ANTES
	// da verificação de pipes, para dar uma mensagem mais específica.
	// ex: ls || pwd
	if (contains_unsupported_logical_operators(input))
		return (report_syntax_error("syntax error: unsupported operator",
				NULL));
	if (contain_pipe_error(input))
		return (report_syntax_error("syntax error near unexpected token `|'",
				NULL));
	if (has_malformed_redirects(input))
		return (report_syntax_error("syntax error: malformed redirection",
				NULL));
	return (1);
}

