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
    int i = 1;
    int newline = 1;

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