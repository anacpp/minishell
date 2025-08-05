/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/08/05 17:24:56 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Contains the main function for expanding variables within a string.
	Respects Bash behavior for:
	- Expansion of $VAR
	- Expansion of $? (last exit status)
	- Do not expand within single quotes
	- Allow expansion within double quotes

	Flow:
	- expand_variables: traverses the original string
	and replaces tokens with '$'.
	- handle_dollar: extracts the variable name
	and returns its value (or "" if undefined).
	- append_char_and_advance: adds literal character to the resulting string.
	- expand_tokens: applies expansion to all tokens
	from the parser that are not within single quotes.

	Depends on auxiliary functions in utils_expand.c.
*/
#include "../../includes/minishell.h"

static char	*process_expansion(char *result, char *input, int *i, int status)
{
	char	*tmp;

	if (input[*i] == '$')
		tmp = process_dollar_sequence(result, input, i, status);
	else
		tmp = process_regular_char(result, input[*i], i);
	if (!tmp)
	{
		free(result);
		return (NULL);
	}
	return (tmp);
}

static char	*expand_in_other_quotes(char *input, char *result, int status)
{
	int		i;
	char	*tmp;

	i = 0;
	while (input[i])
	{
		tmp = process_expansion(result, input, &i, status);
		if (!tmp)
		{
			free(result);
			return (NULL);
		}
		result = tmp;
	}
	return (result);
}

static char	*expand_in_single_quotes(char *input, char *result)
{
	int		i;
	char	*tmp;

	i = 0;
	while (input[i])
	{
		tmp = process_regular_char(result, input[i], &i);
		if (!tmp)
		{
			free(result);
			return (NULL);
		}
		result = tmp;
	}
	return (result);
}

char	*expand_variables(char *input, int status, int quote_type)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	if (quote_type == 1)
		return (expand_in_single_quotes(input, result));
	else
		return (expand_in_other_quotes(input, result, status));
}
