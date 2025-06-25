/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdos-san <rdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by rjacques          #+#    #+#             */
/*   Updated: 2025/06/21 05:36:33 by rdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	parse_command_segment(t_cmd *cmd, t_token **start_token);
static int	handle_pipe_token(t_cmd **cmd, t_token **token);
static int	parser_loop(t_cmd **current_cmd, t_token **current_token);

static int	parser_loop(t_cmd **current_cmd, t_token **current_token)
{
	while (*current_token != NULL)
	{
		if (!parse_command_segment(*current_cmd, current_token))
			return (0);
		if (*current_token && (*current_token)->type == T_PIPE)
		{
			if ((*current_cmd)->argv[0] == NULL && (*current_cmd)->redirs)
			{
				error_unexpected_token(*current_token);
				return (0);
			}
			if (!handle_pipe_token(current_cmd, current_token))
				return (0);
		}
	}
	return (1);
}

t_cmd	*parse(t_token *tokens)
{
	t_cmd	*cmd_head;
	t_cmd	*current_cmd;

	if (!tokens)
		return (NULL);
	if (tokens->type == T_PIPE)
		return (error_unexpected_token(tokens), NULL);
	cmd_head = create_new_cmd();
	current_cmd = cmd_head;
	if (!parser_loop(&current_cmd, &tokens))
		return (free_command_table(cmd_head), NULL);
	if (current_cmd->argv[0] == NULL && current_cmd->redirs)
	{
		report_syntax_error("missing command", NULL);
		return (free_command_table(cmd_head), NULL);
	}
	return (cmd_head);
}

static int	handle_pipe_token(t_cmd **cmd, t_token **token)
{
	t_token	*next_t;
	t_token	*error_t;

	next_t = (*token)->next;
	if (!next_t || next_t->type == T_PIPE)
	{
		if (next_t)
			error_t = next_t;
		else
			error_t = *token;
		return (error_unexpected_token(error_t), 0);
	}
	(*cmd)->next = create_new_cmd();
	*cmd = (*cmd)->next;
	*token = (*token)->next;
	return (1);
}

static int	parse_command_segment(t_cmd *cmd, t_token **start_token)
{
	t_token	*segment_end;
	int		arg_count;

	segment_end = *start_token;
	while (segment_end && segment_end->type != T_PIPE)
		segment_end = segment_end->next;
	arg_count = count_segment_args(*start_token);
	cmd->argv = ft_calloc(arg_count + 1, sizeof(char *));
	if (!cmd->argv)
		handle_error(NULL, "malloc failed", 1, 1);
	if (!fill_segment_data(cmd, start_token, segment_end))
		return (0);
	*start_token = segment_end;
	return (1);
}