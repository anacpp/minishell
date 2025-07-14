/*
	BUILTIN.C

	Executa os comandos built-in reconhecidos pela minishell: cd, exit, echo, pwd, env, export, unset.

	Funções:
	- run_builtin: roteia a execução com base no nome do comando.
	- builtin_cd: muda o diretório atual (ou vai para $HOME se nenhum argumento).
	- builtin_exit: encerra o shell com o status opcional.
	- builtin_echo: imprime argumentos com suporte à flag -n.
*/

#include "../../includes/minishell.h"
/**
 * @brief Roteia para a função built-in correta e retorna seu status.
 * @param cmd O comando a ser executado.
 * @return O status de saída do built-in (0 para sucesso, >0 para erro).
 */
int	run_builtin(t_cmd *cmd, t_shell *shell_context)
{
	char	*cmd_name;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (127);
	cmd_name = cmd->argv[0];
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (builtin_cd(cmd->argv, shell_context));
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd_name, "export") == 0)
		return (builtin_export(cmd->argv, shell_context));
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (builtin_unset(cmd->argv, shell_context));
	if (ft_strcmp(cmd_name, "env") == 0)
		return (builtin_env(cmd->argv, shell_context));
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (builtin_exit(cmd->argv, shell_context));
	return (127); // Indica que não é um built-in
}

/**
 * @brief Imprime os argumentos na saída padrão.
 * @param argv Argumentos do comando.
 * @return Sempre retorna 0 (sucesso).
 */
int	builtin_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (argv[i] && is_n_flag(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}

/**
 * @brief Imprime uma mensagem de erro padronizada para o comando cd.
 *
 * @param path O caminho que causou o erro.
 * @param msg A mensagem de erro específica.
 */
static void	print_cd_error(const char *path, const char *msg)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd((char *)path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

/**
 * @brief Muda o diretório de trabalho atual.
 *
 * Realiza verificações usando stat() para fornecer mensagens
 * de erro precisas
 *
 * @param argv Argumentos do comando.
 * @param shell_context O contexto do shell para acessar o ambiente.
 * @return 0 em sucesso, 1 em erro.
 */
int	builtin_cd(char **argv, t_shell *shell_context)
{
	char		*path;
	struct stat	stat_buf;

	if (argv[1] && argv[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n",
				STDERR_FILENO), 1);
	path = argv[1];
	if (!path)
	{
		path = get_env_value("HOME", shell_context->envp);
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n",
					STDERR_FILENO), 1);
	}
	if (stat(path, &stat_buf) != 0)
	{
		print_cd_error(path, "No such file or directory");
		return (1);
	}
	if (!S_ISDIR(stat_buf.st_mode))
		return (print_cd_error(path, "Not a directory"), 1);
	if (chdir(path) != 0)
		return (print_cd_error(path, "Permission denied"), 1);
	return (0);
}

/**
 * @brief Verifica se uma string representa um número válido (inteiro).
 *
 * Esta função auxiliar verifica se a string contém apenas dígitos,
 * com um sinal opcional ('+' ou '-') no início.
 *
 * @param str A string a ser verificada.
 * @return 1 se for uma string numérica válida, 0 caso contrário.
 */
static int	is_numeric_string(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Termina o shell com um status de saída, com validação de argumentos.
 *
 * Comportamentos implementados:
 * 1.  `exit` (sem args): Sai com o status do último comando.
 * 2.  `exit [arg]`:
 * - Se [arg] não for numérico, imprime erro e sai com status 2.
 * - Se houver mais de um argumento, imprime erro, retorna status 1 e NÃO sai.
 * - Se [arg] for numérico, sai com o status `[arg] % 256`.
 *
 * @param argv Argumentos do comando.
 * @param shell_context Contexto do shell para obter o último status.
 * @return Não retorna se bem-sucedido. Retorna 1 em caso de "too many arguments".
 */
int	builtin_exit(char **argv, t_shell *shell_context)
{
	long long	status;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!argv[1])
	{
		exit(shell_context->last_status);
	}
	//TODO: Verificar se o exit aceita coisas diferentes de números
	if (!is_numeric_string(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(2);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	//Precisa ser um lon long pq aceita qualquer número enviado pelo usuário
	status = ft_atoll(argv[1]);
	exit((unsigned char)status);
}



