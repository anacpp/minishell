#include "../../includes/minishell.h"

int count_args(t_token *token) {
	int count = 0;
	while (token && token->type != T_PIPE) {
		if (token->type == T_WORD || token->type == T_ARGUMENT)
			count++;
		token = token->next;
	}
	return count;
}

void free_tokens(t_token *head)
{
    t_token *tmp;

    while (head)
    {
        tmp = head->next;
        free(head->value);
        free(head);
        head = tmp;
    }
}

void free_redirects(t_redirect *redir)
{
    t_redirect *tmp;

    while (redir)
    {
        tmp = redir->next;
        free(redir->file);
        free(redir);
        redir = tmp;
    }
}

void free_cmd(t_cmd *cmd)
{
    int i;

    i = 0;
    if (!cmd)
        return;
    while (cmd->argv && cmd->argv[i])
    {
        free(cmd->argv[i]);
        i++;
    }
    free(cmd->argv);
    free_redirects(cmd->redir);
    free(cmd);
}

void free_cmd_list(t_cmd *head)
{
    t_cmd *tmp;

    while (head)
    {
        tmp = head->next;
        free_cmd(head);
        head = tmp;
    }
}
