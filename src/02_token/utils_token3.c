/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/05/16 20:16:57 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// OBS : NORMINETTE - OK

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

char	*handle_escape_in_dquote(const char *str, int *i)
{
	char	next;
	char	*tmp;

	next = str[*i + 1];
	if (next == '\\' || next == '"' || next == '$' || next == '`')
	{
		(*i)++;
		tmp = ft_strndup(str + *i, 1);
		(*i)++;
	}
	else
	{
		tmp = ft_strndup(str + *i, 1);
		(*i)++;
	}
	return (tmp);
}

char	*handle_escape(const char *str, int *i, int in_squote, int in_dquote)
{
	char	*tmp;

	if (in_squote)
		return (handle_escape_in_squote(str, i));
	if (in_dquote)
		return (handle_escape_in_dquote(str, i));
	(*i)++;
	tmp = ft_strndup(str + *i, 1);
	(*i)++;
	return (tmp);
}
