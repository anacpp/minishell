/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/07/24 15:22:57 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"

t_token	*get_last_token(t_token *head)
{
	t_token	*current;

	current = head;
	if (!current)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}

char	*handle_char(const char *str, int *i)
{
	char	*tmp;

	tmp = ft_strndup(str + *i, 1);
	(*i)++;
	return (tmp);
}

const char	*token_type_str(t_token_type type)
{
	if (type == T_WORD)
		return ("Word");
	else if (type == T_PIPE)
		return ("Pipe");
	else if (type == T_REDIR_IN)
		return ("Redir In");
	else if (type == T_REDIR_OUT)
		return ("Redir Out");
	else if (type == T_HEREDOC)
		return ("Heredoc");
	else if (type == T_APPEND)
		return ("Append");
	else if (type == T_ARGUMENT)
		return ("Argument");
	else
		return ("Unknown");
}

char	*handle_word_token(const char *str, int *i, int *quote_type)
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
