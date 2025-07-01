/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_segment_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 05:14:01 by rdos-san          #+#    #+#             */
/*   Updated: 2025/06/21 05:36:29 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fill_segment_data(t_cmd *cmd, t_token **start, t_token *end)
{
	t_token	*iter;
	int		i;

	iter = *start;
	i = 0;
	while (iter != end)
	{
		if (token_is_redirection(iter))
		{
			if (!add_redirection(cmd, &iter))
				return (0);
		}
		else if (iter->type == T_WORD)
		{
			cmd->argv[i] = remove_quotes(iter->value);
			i++;
		}
		iter = iter->next;
	}
	cmd->argv[i] = NULL;
	if (i == 0 && cmd->redirs != NULL && end != NULL && end->type == T_PIPE)
		return (1);
	if (i == 0 && cmd->redirs != NULL)
		return (report_syntax_error("missing command", NULL));
	return (1);
}

int	count_segment_args(t_token *token)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = token;
	while (temp && temp->type != T_PIPE)
	{
		if (token_is_redirection(temp))
		{
			temp = get_next_token(temp);
			if (temp)
				temp = get_next_token(temp);
		}
		else
		{
			count++;
			temp = get_next_token(temp);
		}
	}
	return (count);
}
