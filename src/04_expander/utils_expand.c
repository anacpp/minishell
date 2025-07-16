/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/16 19:34:40 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* UTILS_EXPAND.C

	Funções auxiliares usadas no processo de expansão de 
	variáveis, mantendo o código modular e reutilizável.

	- append_expanded: trata e junta a expansão de 
	uma variável ao resultado.
	- update_quotes: atualiza os estados de aspas simples/
	duplas durante a leitura da string.
	- process_dollar_sequence: lida com um token 
	de variável começando com '$'.
	- process_regular_char: adiciona caractere normal
	ao resultado e avança o índice.

	Essas funções são usadas por `expand_variables` para gerenciar
	o fluxo de expansão corretamente.
*/

// TODO: NORMINETTE

#include "../../includes/minishell.h"

char	*append_expanded(char *result, char *input, int *i, int status)
{
	char	*expanded;
	char	*tmp;

	expanded = handle_dollar(&input[*i], i, status);
	if (!expanded)
	{
		free(result);
		return (NULL);
	}
	tmp = ft_strjoin(result, expanded);
	return (tmp);
}

void	update_quotes(char c, int *in_squote, int *in_dquote)
{
	if (c == '\'' && !*in_dquote)
		*in_squote = !*in_squote;
	else if (c == '\"' && !*in_squote)
		*in_dquote = !*in_dquote;
}

char	*process_dollar_sequence(char *result, char *input, int *i, int status)
{
	char	*tmp;

	tmp = append_expanded(result, input, i, status);
	if (!tmp)
	{
		free(result);
		return (NULL);
	}
	return (tmp);
}

char	*process_regular_char(char *result, char current, int *i)
{
	char	*tmp;

	tmp = append_char_and_advance(result, current);
	if (!tmp)
	{
		free(result);
		return (NULL);
	}
	(*i)++;
	return (tmp);
}
