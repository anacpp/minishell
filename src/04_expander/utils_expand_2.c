/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/08/05 17:24:41 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	free_remaining_expansions(t_token *start, t_token *end)
{
	t_token	*tmp;

	tmp = start;
	while (tmp && tmp != end)
	{
		free(tmp->value);
		tmp = tmp->next;
	}
}

void	expand_tokens(t_token *tokens, int last_status)
{
	t_token	*tmp;
	char	*expanded;
	t_token	*error_token;

	error_token = NULL;
	tmp = tokens;
	while (tmp)
	{
		expanded = expand_variables(tmp->value, last_status, tmp->quote_type);
		if (!expanded)
		{
			error_token = tmp;
			break ;
		}
		free(tmp->value);
		tmp->value = expanded;
		tmp = tmp->next;
	}
	if (error_token)
		free_remaining_expansions(error_token, NULL);
}
