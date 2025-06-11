/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/06/11 17:04:45 by acesar-p         ###   ########.fr       */
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
