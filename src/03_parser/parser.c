/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by rjacques          #+#    #+#             */
/*   Updated: 2025/06/11 17:19:37 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	parse_command_segment(t_cmd *cmd, t_token **start_token);
static int	count_segment_args(t_token *token);
static int	handle_pipe_token(t_cmd **cmd, t_token **token);
static int	fill_segment_data(t_cmd *cmd, t_token **start, t_token *end);

// REFATORAR: 27 LINHAS
t_cmd	*parse(t_token *tokens)
{
	t_cmd	*cmd_head;
	t_cmd	*current_cmd;
	t_token	*current_token;

	if (!tokens)
		return (NULL);
	if (tokens->type == T_PIPE)
		return (error_unexpected_token(tokens), NULL);
	cmd_head = create_new_cmd();
	current_cmd = cmd_head;
	current_token = tokens;
	while (current_token != NULL)
	{
		if (current_token->type == T_PIPE)
		{
			if (!handle_pipe_token(&current_cmd, &current_token))
				return (free_command_table(cmd_head), NULL);
		}
		if (current_token == NULL)
			break ;
		if (!parse_command_segment(current_cmd, &current_token))
			return (free_command_table(cmd_head), NULL);
	}
	if (cmd_head && !cmd_head->argv[0] && cmd_head->redirs)
		return (report_syntax_error("missing command", NULL),
			free_command_table(cmd_head), NULL);
	return (cmd_head);
}

static int	count_segment_args(t_token *token)
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

static int	handle_pipe_token(t_cmd **cmd, t_token **token)
{
	if (!(*token)->next || (*token)->next->type == T_PIPE)
	{
		error_unexpected_token((*token)->next ? (*token)->next : *token); // PROIBIDO USO DE TERNÁRIO 
		return (0);
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
	cmd->argv[0] = NULL;
	if (!fill_segment_data(cmd, start_token, segment_end))
		return (0);
	*start_token = segment_end;
	return (1);
}

static int	fill_segment_data(t_cmd *cmd, t_token **start, t_token *end)
{
	t_token	*iter;
	int		i;
	int		last_was_redir;

	last_was_redir = 0;
	iter = *start;
	i = 0;
	while (iter != end)
	{
		if (token_is_redirection(iter))
		{
			if (!add_redirection(cmd, &iter))
				return (0);
			last_was_redir = 1;
			continue ;
		}
		last_was_redir = 0;
		if (iter->type == T_WORD)
			cmd->argv[i++] = remove_quotes(iter->value);
		iter = iter->next;
	}
	cmd->argv[i] = NULL;
	if (i == 0 && cmd->redirs != NULL)
		return (report_syntax_error("missing command", NULL));
	return (1);
}

