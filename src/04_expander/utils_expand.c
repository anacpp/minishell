/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/24 15:24:13 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* UTILS_EXPAND.C

	Helper functions used in the process of variable expansion,
	keeping the code modular and reusable.

	- append_expanded: handles and joins the expansion of
	a variable to the result.
	- update_quotes: updates the state of single/double quotes
	while reading the string.
	- process_dollar_sequence: handles a variable token
	starting with '$'.
	- process_regular_char: adds a regular character
	to the result and advances the index.

	These functions are used by `expand_variables` to manage
	the expansion flow correctly.
*/


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
		return (NULL);
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
