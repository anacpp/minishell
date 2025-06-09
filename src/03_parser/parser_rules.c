#include "../../includes/minishell.h"

// Valida o que vem depois de um token de redirecionamento.
// Erro: Redirecionamentos seguidos (ex: "> >")
// Erro: Faltando argumento/arquivo apos redirecionamento (ex: ">" no final)
int	validate_token_after_redir(t_token *redir_token)
{
	t_token	*next_t;

	if (!redir_token)
		return (0);
	next_t = get_next_token(redir_token);
	if (!next_t)
		// Nada apos o redirecionamento
		return (report_syntax_error(NULL, NULL)); // Erro: `newline` inesperado
	if (token_is_operator(next_t))
		// Operador logo apos redirecionamento
		return (error_unexpected_token(next_t));
	if (next_t->type != T_WORD) // Nao é um nome de arquivo esperado
	{
		return (error_unexpected_token(next_t));
	}
	return (0);
}

// Valida se o nome de arquivo (que é um T_WORD) é uma string vazia.
// Cobre Erro: $VAR expande para "" como nome de arquivo.
int	validate_empty_filename_after_redir(t_token *filename_token)
{
	if (filename_token && filename_token->type == T_WORD
		&& filename_token->value && filename_token->value[0] == '\0')
	{
		return (report_syntax_error("ambiguous redirect", NULL));
	}
	return (0);
}

// Valida o inicio de um comando ou segmento de comando.
// Cobre: Faltando comando antes de redirecionamento (ex: "> out.txt")
// Cobre: Redirecionamento no lugar de comando (ex: "> out.txt | cmd")
// Tambem verifica por pipes no inicio.
int	validate_command_segment_start(t_token *first_token_in_segment)
{
	if (!first_token_in_segment) // Segmento vazio (ex: input vazio apos trim)
		return (0);
	if (first_token_in_segment->type == T_PIPE)
		return (error_unexpected_token(first_token_in_segment));
	if (token_is_redirection(first_token_in_segment))
	{
		return (report_syntax_error("missing command", NULL));
	}
	return (0); //(comeca com T_WORD ou outro token valido)
}

// Valida um token de pipe.
// Verifica se o pipe esta no inicio, ou se ha pipes consecutivos,
// ou se o pipe é o ultimo token.
int	validate_pipe_placement(t_token *pipe_token, int is_first_overall)
{
	t_token *next_t;

	if (!pipe_token || pipe_token->type != T_PIPE)
		return (0);

	// Erro: Pipe como primeiro token significativo da linha
	if (is_first_overall)
		return (error_unexpected_token(pipe_token));

	// Erro: Nada apos o pipe, ou outro pipe logo em seguida
	next_t = get_next_token(pipe_token);
	if (!next_t || next_t->type == T_PIPE)
		return (error_unexpected_token(next_t ? next_t : pipe_token));

	return (0);
}
