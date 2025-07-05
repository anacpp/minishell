/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/05/16 20:16:33 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// OBS : NORMINETTE - OK

#include "../../includes/minishell.h"

void add_token(t_token **head, char *value, t_token_type type, int quote_type)
{
	t_token	*new;
	t_token	*temp;

	if (!value)
		return ;
	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return ;
	}
	new->type = type;
	new->quote_type = quote_type;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}


void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
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

void	update_quote_flags(char c, int *in_squote, int *in_dquote)
{
	if (c == '\'' && !(*in_dquote))
		*in_squote = !(*in_squote);
	else if (c == '\"' && !(*in_squote))
		*in_dquote = !(*in_dquote);
}
