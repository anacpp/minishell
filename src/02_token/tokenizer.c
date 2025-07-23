/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/23 20:27:15 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* OBS :
	-> NORMINETTE - ok
	-> CHECK LEAKS - ok (LEAKS ONLY FROM READLINE LIBRARY, WHICH ARE EXPECTED)


*/

#include "../../includes/minishell.h"

static char	*extract_token_without_quotes(const char *str, int len,
		int quote_type)
{
	if ((quote_type == 1 && str[0] == '\'' && str[len - 1] == '\'')
		|| (quote_type == 2 && str[0] == '"' && str[len - 1] == '"'))
		return (ft_strndup(str + 1, len - 2));
	return (ft_strndup(str, len));
}

char	*get_token_value(const char *str, int *i, int *quote_type)
{
	int		in_squote;
	int		in_dquote;
	int		start;
	char	*value;

	in_squote = 0;
	in_dquote = 0;
	start = *i;
	*quote_type = 0;
	if (str[start] == '\'')
		*quote_type = 1;
	else if (str[start] == '"')
		*quote_type = 2;
	while (str[*i])
	{
		update_quote_flags(str[*i], &in_squote, &in_dquote);
		if (is_token_end(str[*i], in_squote, in_dquote))
			break ;
		(*i)++;
	}
	value = extract_token_without_quotes(str + start, *i - start, *quote_type);
	return (value);
}

char	*get_operator(const char *str, int *i)
{
	if ((str[*i] == '<' || str[*i] == '>') && str[*i + 1] != '\0' && str[*i
			+ 1] == str[*i])
	{
		*i += 2;
		return (ft_strndup(str + *i - 2, 2));
	}
	else if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
	{
		*i += 1;
		return (ft_strndup(str + *i - 1, 1));
	}
	return (NULL);
}

t_token	*tokenize_input(const char *str)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (str[i])
		get_token_next(str, &i, &head);
	return (head);
}
