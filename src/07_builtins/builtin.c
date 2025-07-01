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

void run_builtin(t_cmd *cmd)
{
    if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
        builtin_cd(cmd->argv);
    else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
        builtin_exit(cmd->argv);
    else if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
        builtin_echo(cmd->argv);
    else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
        builtin_pwd();
    else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
        builtin_env();
    else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
        builtin_export(cmd->argv);
    else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
        builtin_unset(cmd->argv);
}


void	builtin_cd(char **argv)
{
	char	*home;
	int		ret;

	if (!argv[1])
	{
		home = getenv("HOME");
		ret = chdir(home);
	}
	else
	{
		ret = chdir(argv[1]);
		if (ret != 0)
			ft_printf("minishell: cd: %s: No such file or directory\n", argv[1]);
	}
}

void builtin_exit(char **argv)
{
    int status;

    status = 0;
    if (argv[1])
        status = ft_atoi(argv[1]);
    exit(status);
}

void builtin_echo(char **argv)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    while (argv[i] && is_n_flag(argv[i]))
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
}


static void	print_args(char **argv, int i)
{
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1])
			ft_printf(" ");
		i++;
	}
}

/*
Main teste 

#include "minishell.h"

int	main(void)
{
	char	*line;
	char	**args;
	t_cmd	cmd;

	while (1)
	{
		line = readline("builtin-test$ ");
		if (!line)
			break;

		if (*line)
			add_history(line);

		args = ft_split(line, ' '); // Simples split por espaço
		if (!args || !args[0])
		{
			free(line);
			continue;
		}

		// Prepara o comando manualmente
		cmd.argv = args;
		cmd.redirs = NULL;
		cmd.next = NULL;

		// Verifica se é builtin
		if (is_builtin(cmd.argv[0]))
			run_builtin(&cmd);
		else
			ft_printf("Comando '%s' não é builtin.\n", cmd.argv[0]);

		free(line);
		free_split(args); // função que libera array de strings
	}
	return (0);
}
*/