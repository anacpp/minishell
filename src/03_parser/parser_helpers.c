#include "../../includes/minishell.h"

static void	perform_quote_removal(char *str, char *new_str);

/**
 * @brief Cria uma nova string removendo as aspas de controle.
 *
 * @details Recebe uma string e remove as aspas (simples ou duplas) que
 * servem para agrupar o conteúdo, mas não as aspas literais dentro de outras.
 * Ex: `"olá 'mundo'"` -> `olá 'mundo'`.
 *
 * @param str A string original que pode conter aspas.
 * @return Retorna uma nova string alocada dinamicamente com o resultado.
 */
char	*remove_quotes(char *str)
{
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		handle_error(NULL, "malloc failed", 1, 1);
	perform_quote_removal(str, new_str);
	return (new_str);
}

/**
 * @brief Executa a lógica de remoção de aspas.
 *
 * @details Itera pela string de origem, controlando o estado "dentro de
 * aspas" para copiar para a string de destino apenas os caracteres que
 * não são aspas de controle.
 *
 * @param str A string de origem.
 * @param new_str A string de destino onde o resultado será armazenado.
 */
static void	perform_quote_removal(char *str, char *new_str)
{
	int	i;
	int	j;
	int	in_squote;
	int	in_dquote;

	i = 0;
	j = 0;
	in_squote = 0;
	in_dquote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
}

/**
 * @brief Aloca e inicializa um novo nó de comando (`t_cmd`).
 *
 * @details Função utilitária para criar um comando "vazio", com seus
 * ponteiros internos (`argv`, `redirs`, `next`) inicializados como `NULL`.
 *
 * @return Retorna um ponteiro para o nó `t_cmd` recém-criado.
 */
t_cmd	*create_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		handle_error(NULL, "malloc failed", 1, 1);
	new_cmd->argv = NULL;
	new_cmd->redirs = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}
