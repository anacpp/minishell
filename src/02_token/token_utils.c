/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/08/05 17:32:21 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_word_token(const char *str, int *i, int *quote_type)
{
	int	in_squote;
	int	in_dquote;
	int	temp_i;

	in_dquote = 0;
	in_squote = 0;
	temp_i = *i;
	while (str[temp_i] && !is_operator_char(str[temp_i]) && str[temp_i] != ' '
		&& str[temp_i] != '\t')
	{
		update_quote_flags(str[temp_i], &in_squote, &in_dquote);
		temp_i++;
	}
	if (in_squote)
		*quote_type = 1;
	else if (in_dquote)
		*quote_type = 2;
	return (get_token_value(str, i, quote_type));
}

void	get_token_next(const char *str, int *i, t_token **head)
{
	char	*value;
	int		quote_type;

	quote_type = 0;
	if (is_operator_char(str[*i]))
		value = get_operator(str, i);
	else
		value = handle_word_token(str, i, &quote_type);
	if (value && *value != '\0')
		add_token(head, value, get_token_type(value), quote_type);
	free(value);
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
}

t_token_type	get_token_type(const char *str)
{
	if (ft_strlen(str) == 1 && str[0] == '|')
		return (T_PIPE);
	else if (ft_strlen(str) == 1 && str[0] == '<')
		return (T_REDIR_IN);
	else if (ft_strlen(str) == 1 && str[0] == '>')
		return (T_REDIR_OUT);
	else if (ft_strlen(str) == 2 && !ft_strncmp(str, "<<", 2))
		return (T_HEREDOC);
	else if (ft_strlen(str) == 2 && !ft_strncmp(str, ">>", 2))
		return (T_APPEND);
	else if (!ft_strncmp(str, "$", 2))
		return (T_ARGUMENT);
	return (T_WORD);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*dup;

	i = 0;
	while (s[i] && i < n)
		i++;
	dup = malloc(i + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
