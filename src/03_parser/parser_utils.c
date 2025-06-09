#include "../../includes/minishell.h"

// Verifica se o tipo do token é um operador de redirecionamento
int	is_redirection_token_type(t_token_type type)
{
    return (type == T_REDIR_IN || type == T_REDIR_OUT || type == T_HEREDOC
        || type == T_APPEND);
}

// Verifica se o token (nao nulo) é um operador de redirecionamento
int	token_is_redirection(t_token *token)
{
    if (!token)
        return (0);
    return (is_redirection_token_type(token->type));
}

// Verifica se o token (nao nulo) é um operador (pipe ou redirecionamento)
int	token_is_operator(t_token *token)
{
    if (!token)
        return (0);
    return (token_is_redirection(token) || token->type == T_PIPE);
}

// Retorna o proximo token, ou NULL se nao houver
t_token	*get_next_token(t_token *current)
{
    if (current)
        return (current->next);
    return (NULL);
}
