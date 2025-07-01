/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/06/11 17:14:43 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	TODO: NORMINETTE
	    
*/

#include "../../includes/minishell.h"

void	prepare_heredocs(t_cmd *cmds)
{
	t_cmd		*cmd;
	t_redir		*redir;
	int			fd;
	char		*tmp_filename;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
			{
				fd = create_heredoc(redir->filename);
				if (fd < 0)
				{
					perror("heredoc");
				}
				free(redir->filename);
				redir->type = T_REDIR_IN;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

int executor(t_cmd *cmd)
{
	int total_cmd;

	total_cmd = count_cmds(cmd);
	if (total_cmd > 1)
		create_pipes(total_cmd);
	if (!cmd || cmd->argv[0] == NULL)
		return (1);		
	is_valid_cmd(cmd);
}


// continuação 


