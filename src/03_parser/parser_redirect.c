#include "../../includes/minishell.h"

static t_redir	*create_redir_node(t_token *redir_t, t_token *file_t);
static void		append_redir_to_cmd(t_cmd *cmd, t_redir *new_redir);

/**
 * @brief Processa um token de redirecionamento e seu nome de arquivo.
 *
 * @details Valida a sintaxe do redirecionamento, cria um novo nó `t_redir` e
 * o anexa à lista de redirecionamentos do comando atual.
 *
 * @param cmd O comando ao qual o redirecionamento pertence.
 * @param token_ptr Ponteiro para o ponteiro do token de redirecionamento,
 * que será avançado após a leitura do nome do arquivo.
 * @return Retorna `1` em caso de sucesso, `0` se um erro de sintaxe for encontrado.
 */
int	add_redirection(t_cmd *cmd, t_token **token_ptr)
{
	t_token	*redir_token;
	t_token	*filename_token;
	t_redir	*new_redir;

	redir_token = *token_ptr;
	filename_token = get_next_token(redir_token);
	if (!filename_token || token_is_operator(filename_token))
		return (error_unexpected_token(filename_token));
	if (filename_token->value && filename_token->value[0] == '\0')
		return (report_syntax_error("ambiguous redirect", NULL));
	new_redir = create_redir_node(redir_token, filename_token);
	append_redir_to_cmd(cmd, new_redir);
	*token_ptr = get_next_token(filename_token);
	return (1);
}

/**
 * @brief Aloca e inicializa um novo nó de redirecionamento (`t_redir`).
 *
 * @param redir_t O token que representa o tipo de redirecionamento (ex: `>`).
 * @param file_t O token que contém o nome do arquivo para o redirecionamento.
 * @return Retorna um ponteiro para o nó `t_redir` recém-criado.
 */
static t_redir	*create_redir_node(t_token *redir_t, t_token *file_t)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		handle_error(NULL, "malloc failed", 1, 1);
	new_redir->type = redir_t->type;
	new_redir->filename = remove_quotes(file_t->value);
	new_redir->next = NULL;
	return (new_redir);
}

/**
 * @brief Anexa um novo nó de redirecionamento ao final da lista de um comando.
 *
 * @param cmd O comando que será modificado.
 * @param new_redir O nó de redirecionamento a ser adicionado.
 */
static void	append_redir_to_cmd(t_cmd *cmd, t_redir *new_redir)
{
	t_redir	*last;

	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}
