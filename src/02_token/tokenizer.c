/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/05/21 17:08:14 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* OBS :
	-> NORMINETTE - ok
	-> CHECK LEAKS - ok (LEAKS APENAS DA BIBLIOTECA READLINE, QUE SÃO ESPERADAS)
*/

#include "../../includes/minishell.h"

static char *handle_variable(const char *str, int *i)
{
    int start = *i;
    (*i)++;

    if (str[*i] == '?') {
        (*i)++;
        return ft_strndup(str + start, 2);
    }
    if (str[*i] == '$') {
        (*i)++;
        return ft_strndup(str + start, 2);
    }
    while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
        (*i)++;
    return ft_strndup(str + start, *i - start);
}

static char	*get_token_value(const char *str, int *i, t_token *last)
{
	char	*value;
	char	*tmp;
	int		in_squote;
	int		in_dquote;

	in_squote = 0;
	in_dquote = 0;
	value = ft_strdup("");
	while (str[*i])
	{
		update_quote_flags(str[*i], &in_squote, &in_dquote);
		if (is_token_end(str[*i], in_squote, in_dquote))
			break ;
		else if (str[*i] == '$' && !in_squote && !is_heredoc_context(last))
			tmp = handle_variable(str, i);
		else
			tmp = handle_char(str, i);
		value = ft_strjoin(value, tmp);
	}
	return (value);
}

static char	*get_operator(const char *str, int *i)
{
	char	*operator;

	operator = NULL;
	if ((str[*i] == '<' || str[*i] == '>') && str[*i + 1] == str[*i])
	{
		operator = ft_strndup(str + *i, 2);
		(*i) += 2;
	}
	else if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>')
	{
		operator = ft_strndup(str + *i, 1);
		(*i)++;
	}
	return (operator);
}

t_token	*tokenize_input(const char *str)
{
	t_token	*head;
	char	*value;
	int		i;

	head = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!str[i])
			break ;
		if (is_operator_char(str[i]))
			value = get_operator(str, &i);
		else
			value = get_token_value(str, &i, get_last_token(head));
		if (value && *value != '\0')
			add_token(&head, value, get_token_type(value));
		free(value);
	}
	return (head);
}
