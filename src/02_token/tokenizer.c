/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/05/16 20:16:26 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* OBS :
	-> NORMINETTE - ok
	-> CHECK LEAKS - ok (LEAKS APENAS DA BIBLIOTECA READLINE, QUE SÃO ESPERADAS)
*/

#include "../../includes/minishell.h"

static char	*expand_variable(const char *str, int *i)
{
	int		start;
	char	*var_name;
	char	*var_value;
	char	*value;

	start = *i;
	(*i)++;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_strndup(str + start + 1, *i - start - 1);
	var_value = getenv(var_name);
	free(var_name);
	if (var_value)
		value = ft_strdup(var_value);
	else
		value = ft_strdup("");
	return (value);
}

static char	*handle_variable(const char *str, int *i)
{
	return (expand_variable(str, i));
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
		if (str[*i] == '\\' && str[*i + 1])
			tmp = handle_escape(str, i, in_squote, in_dquote);
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
