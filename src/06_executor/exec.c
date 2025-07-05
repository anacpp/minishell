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
	TODO: NORMINETTE, função set_redir/exec_external/save pid / wait all children
	    
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

int is_command_valid(t_cmd *cmd)
{
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (0);
    if (is_builtin(cmd))
        return (1);
    if (is_external_command(cmd))
        return (1);
    return (0);
}
int executor(t_cmd *cmd)
{
    int total_cmd;
    pid_t pid;
    t_cmd *current_cmd;
    pid_t g_child_pids[MAX_PIDS];
    int   g_num_pids;

    g_num_pids = 0;
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (1);
    total_cmd = count_cmds(cmd);
    if (total_cmd > 1)
        create_pipes(total_cmd);
    current_cmd = cmd;
    while (current_cmd)
    {
        if (!is_valid_cmd(current_cmd))
        {
            ft_printf("minishell: %s: command not found\n", current_cmd->argv[0]);
            return (127);
        }
        if (is_builtin(cmd->argv[0]) && total_cmd == 1)
        {
	        int stdio_backup[2];
        	save_stdio(stdio_backup);
        	if (cmd->redirs)
		        setup_redir(cmd->redirs);
        	run_builtin(cmd);
        	restore_stdio(stdio_backup);
        }
        else
        {
            pid = fork();
            if (pid < 0)
            {
                perror("fork");
                return (1);
            }
            else if (pid == 0) //filho
            {
                if (current_cmd->redirs != NULL)
                    setup_redir(current_cmd->redirs);
                if (is_builtin(current_cmd->argv[0]))
                    run_builtin(current_cmd);
                else
                    exec_external(current_cmd);
                exit(EXIT_FAILURE); //caso exec falhe
            }
            else
            {
                save_pid(pid); //ela vai salvar o pid do processo
            }
        }
        current_cmd = current_cmd->next;
    }
    wait_all_children(); //espera todos os filhos terminarem e atualiza $? global
    return (0);
}

