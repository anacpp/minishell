#include "../../includes/minishell.h"

static int	handle_pipe_token(t_cmd **cmd, t_token **token, t_cmd *head);
static int	parse_command_segment(t_cmd *cmd, t_token **start_token);
static int	count_segment_args(t_token *start, t_token *end);
static int	fill_segment_data(t_cmd *cmd, t_token **start, t_token *end);

/**
 * @brief Converte uma lista de tokens em uma lista estruturada de comandos.
 *
 * @details Esta é a função de entrada do parser. Ela itera sobre a lista de
 * tokens, usando o pipe `|` como delimitador para criar múltiplos nós `t_cmd`.
 * Cada nó é preenchido com seus respectivos argumentos e redirecionamentos.
 *

 * @param tokens Ponteiro para o início da lista de tokens gerada pelo tokenizer.
 * @return Retorna um ponteiro para o primeiro comando da lista (`t_cmd`).
 * Em caso de erro de sintaxe, libera a memória alocada e retorna `NULL`.
 */
t_cmd	*parse(t_token *tokens)
{
	t_cmd	*cmd_head;
	t_cmd	*current_cmd;
	t_token	*current_token;

	if (!tokens)
		return (NULL);
	cmd_head = create_new_cmd();
	current_cmd = cmd_head;
	current_token = tokens;
	while (current_token != NULL)
	{
		if (current_token->type == T_PIPE)
		{
			if (!handle_pipe_token(&current_cmd, &current_token, cmd_head))
				return (NULL);
		}
		if (!parse_command_segment(current_cmd, &current_token))
		{
			free_command_table(cmd_head);
			return (NULL);
		}
	}
	return (cmd_head);
}

/**
 * @brief Lida com a lógica de um token de pipe.
 *
 * @details Chamada quando um `T_PIPE` é encontrado. Cria um novo comando,
 * anexa-o à lista e verifica erros de sintaxe, como pipes consecutivos
 * (`| |`) ou um pipe no final da linha.
 *
 * @param cmd Ponteiro para o ponteiro do comando atual, para poder modificá-lo.
 * @param token Ponteiro para o ponteiro do token atual, para avançá-lo.
 * @param head Ponteiro para o início da lista de comandos,
	para limpeza em caso de erro.
 * @return Retorna `1` em caso de sucesso,
	ou `0` se um erro de sintaxe for encontrado.
 */
static int	handle_pipe_token(t_cmd **cmd, t_token **token, t_cmd *head)
{
	(*cmd)->next = create_new_cmd();
	*cmd = (*cmd)->next;
	*token = (*token)->next;
	if (!*token || (*token)->type == T_PIPE)
	{
		error_unexpected_token(*token);
		free_command_table(head);
		return (0);
	}
	return (1);
}

/**
 * @brief Orquestra a análise de um único segmento de comando.
 *
 * @details Um segmento é uma sequência de tokens entre dois pipes (ou do início
 * até o primeiro pipe/fim). Esta função organiza a contagem de argumentos e
 * o preenchimento da estrutura `t_cmd` com esses dados.
 *
 * @param cmd O nó de comando atual a ser preenchido.
 * @param start_token Ponteiro para o ponteiro do token inicial do segmento.
 * Será atualizado para apontar para o final do segmento após a execução.
 * @return Retorna `1` em caso de sucesso, `0` em caso de falha.
 */
static int	parse_command_segment(t_cmd *cmd, t_token **start_token)
{
	t_token	*segment_end;
	int		arg_count;

	segment_end = *start_token;
	while (segment_end && segment_end->type != T_PIPE)
		segment_end = segment_end->next;
	arg_count = count_segment_args(*start_token, segment_end);
	cmd->argv = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->argv)
		handle_error(NULL, "malloc failed", 1, 1);
	if (!fill_segment_data(cmd, start_token, segment_end))
		return (0);
	*start_token = segment_end;
	return (1);
}

/**
 * @brief Conta o número de argumentos em um segmento de comando.
 *
 * @details Realiza uma "primeira passagem" pelo segmento para saber
 * exatamente quantos tokens `T_WORD` existem, a fim de alocar o
 * tamanho exato para o `argv`.
 *
 * @param start O token inicial do segmento.
 * @param end O token final do segmento (um `T_PIPE` ou `NULL`).
 * @return Retorna o número de argumentos (`int`) encontrados.
 */
static int	count_segment_args(t_token *start, t_token *end)
{
	int		arg_count;
	t_token	*iter;

	arg_count = 0;
	iter = start;
	while (iter != end)
	{
		if (token_is_redirection(iter))
		{
			if (iter->next)
				iter = iter->next;
		}
		else if (iter->type == T_WORD)
			arg_count++;
		iter = iter->next;
	}
	return (arg_count);
}

/**
 * @brief Preenche o `argv` e a lista de redirecionamentos de um comando.
 *
 * @details Realiza uma "segunda passagem" pelo segmento. Popula o `argv`
 * com os `T_WORD`s e chama `add_redirection` para lidar com os tokens de
 * redirecionamento.
 *
 * @param cmd O nó de comando a ser preenchido.
 * @param start O ponteiro para o ponteiro do token inicial do segmento.
 * @param end O token final do segmento.
 * @return Retorna `1` em caso de sucesso, `0` em caso de falha.
 */
static int	fill_segment_data(t_cmd *cmd, t_token **start, t_token *end)
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
			continue ;
		}
		if (iter->type == T_WORD)
			cmd->argv[i++] = remove_quotes(iter->value);
		iter = iter->next;
	}
	cmd->argv[i] = NULL;
	if (i == 0 && cmd->redirs != NULL)
		return (report_syntax_error("missing command", NULL));
	return (1);
}
