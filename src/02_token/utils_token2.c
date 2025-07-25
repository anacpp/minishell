/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/05/21 17:08:55 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* OBS :
	->NORMINETTE - OK

	TODO :
	->APAGAR AS FUNÇÕES DE PRINT E TOKEN_TYPE_STR QUANDO FOR ENTREGAR
*/

#include "../../includes/minishell.h"

int	is_token_end(char c, int in_squote, int in_dquote)
{
	if (in_squote || in_dquote)
		return (0);
	return (is_operator_char(c) || c == ' ' || c == '\t');
}

void	update_token_value(char **value, char *expanded_value)
{
	char	*temp;

	temp = ft_strjoin(*value, expanded_value);
	*value = temp;
}

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_heredoc_context(t_token *last)
{
	return (last && last->type == T_HEREDOC);
}


// FUNÇÕES DE DEPURAÇÃO ABAIXO :
void	print_tokens(t_token *head)
{
	while (head)
	{
		if (head->value)
			printf("Token: %s, Type: %s\n", head->value,
				token_type_str(head->type));
		else
			printf("Token: (null), Type: %s\n", token_type_str(head->type));
		head = head->next;
	}
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
