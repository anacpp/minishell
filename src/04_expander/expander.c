/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/23 20:27:14 by acesar-p         ###   ########.fr       */
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

// TODO: NORMINETTE

#include "../../includes/minishell.h"

char	*handle_dollar(char *str, int *i, int status);
char	*append_char_and_advance(char *str, char c);

char *expand_variables(char *input, int status, int quote_type)
{
    int i;
    char *result;
    char *tmp;

	i = 0;
	result = ft_strdup("");
    if (!result)
        return NULL;
    while (input[i])
    {
        if (quote_type == 1)
        {
            tmp = process_regular_char(result, input[i], &i);
            if (!tmp)
            {
                free(result);
                return NULL;
            }
            result = tmp;
        }
        else
        {
            if (input[i] == '$')
            {
                tmp = process_dollar_sequence(result, input, &i, status);
                if (!tmp)
                {
                    free(result);
                    return NULL;
                }
                result = tmp;
            }
            else
            {
                tmp = process_regular_char(result, input[i], &i);
                if (!tmp)
                {
                    free(result);
                    return NULL;
                }
                result = tmp;
            }
        }
    }
    return result;
}



char	*handle_dollar(char *str, int *i, int status)
{
	int		j;
	char	*name;
	char	*value;

	j = 0;
	(*i)++;
	if (str[1] == '?')
	{
		(*i)++;
		return (ft_itoa(status));
	}
	while (str[1 + j] && (ft_isalnum(str[1 + j]) || str[1 + j] == '_'))
		j++;
	if (j == 0)
		return (ft_strdup("$"));
	name = ft_substr(str, 1, j);
	value = getenv(name);
	free(name);
	(*i) += j;
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*append_char_and_advance(char *str, char c)
{
	int		len;
	char	*new;

	len = ft_strlen(str);
	new = malloc(len + 2);
	if (!new)
		return (NULL);
	ft_memcpy(new, str, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(str);
	return (new);
}

void	expand_tokens(t_token *tokens, int last_status)
{
	t_token	*tmp;
	char	*expanded;

	tmp = tokens;
	while (tmp)
	{
		expanded = expand_variables(tmp->value, last_status, tmp->quote_type);
		if (!expanded)
			break ;
		free(tmp->value);
		tmp->value = expanded;
		tmp = tmp->next;
	}
}

