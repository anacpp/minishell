/*
	Implementa comandos built-in adicionais da minishell.

	Funções:
	- builtin_pwd: exibe o diretório atual.
	- builtin_env: imprime variáveis de ambiente.
	- builtin_export: adiciona/atualiza variáveis de ambiente.
	- builtin_unset: remove variáveis de ambiente.
	
	Utiliza a variável global `environ` para acessar/modificar o ambiente.
*/

#include "../../includes/minishell.h"

/**
 * @brief Imprime uma mensagem de erro padronizada para um builtin.
 *
 * @param cmd O nome do comando builtin.
 * @param arg O argumento que causou o erro (pode ser NULL).
 * @param msg A mensagem de erro específica.
 */
static void	print_builtin_error(const char *cmd, const char *arg,
		const char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd((char *)arg, STDERR_FILENO);
		ft_putstr_fd("': ", STDERR_FILENO);
	}
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

/**
 * @brief Exibe o diretório de trabalho atual.
 *
 * Não aceita argumentos. Em caso de erro ao obter o diretório,
 * imprime uma mensagem de erro customizada.
 *
 * @return Retorna 0 em sucesso, 1 em caso de erro.
 */
int	builtin_pwd(void)
{
	char cwd[1024]; // tamanho maximo do caminho
	// getcwd: obter o diretório de trabalho atual
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	else
	{
		print_builtin_error("pwd", NULL, "error retrieving current directory");
		return (1);
	}
}

/**
 * @brief Imprime as variáveis de ambiente do contexto atual.
 *
 * @param argv O vetor de argumentos do comando.
 * @param shell_context O contexto do shell.
 * @return Retorna 0 em sucesso, 127 se argumentos inválidos forem passados.
 */
int	builtin_env(char **argv, t_shell *shell_context)
{
	char	**env;
	int		i;

	// env não funciona se tiver argumentos, então argv[1] deve ser NULL
	if (argv[1])
	{
		print_builtin_error("env", argv[1], "No such file or directory");
		return (127);
	}
	env = shell_context->envp;
	i = 0;
	while (env && env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			ft_putstr_fd(env[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Adiciona ou atualiza variáveis no ambiente do shell.
 *
 * Se chamado sem argumentos, imprime o ambiente de forma ordenada.
 * Para cada argumento, valida a chave e a adiciona/atualiza no ambiente.
 * Continua o processamento mesmo que encontre uma chave inválida.
 *
 * @param argv Argumentos do comando.
 * @param shell_context O contexto do shell.
 * @return Retorna 0 se tudo for bem-sucedido, 1 se alguma chave for inválida.
 */
int	builtin_export(char **argv, t_shell *shell_context)
{
	int	i;
	int	status;

	status = 0;
	if (!argv[1])
	{
		print_env_sorted(shell_context->envp);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		if (!is_valid_key(argv[i]))
		{
			print_builtin_error("export", argv[i], "not a valid identifier");
			status = 1;
		}
		else
			add_env_var(argv[i], shell_context);
		i++;
	}
	return (status);
}

/**
 * @brief Remove variáveis do ambiente do shell.
 *
 * Valida cada chave antes de tentar removê-la. Chaves para unset
 * não podem conter o caractere '='.
 *
 * @param argv Argumentos do comando.
 * @param shell_context O contexto do shell.
 * @return Retorna 0 se tudo for bem-sucedido, 1 se alguma chave for inválida.
 */
int	builtin_unset(char **argv, t_shell *shell_context)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (argv[i])
	{
		if (!is_valid_key(argv[i]) || ft_strchr(argv[i], '='))
		{
			print_builtin_error("unset", argv[i], "not a valid identifier");
			status = 1;
		}
		else
			remove_env_var(argv[i], shell_context);
		i++;
	}
	return (status);
}
