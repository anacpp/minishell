#include "../../includes/minishell.h"

int is_builtin(t_cmd *cmd)
{
    const char *builtins[] = {"cd", "echo", "exit", "export", "unset", "pwd", "env", NULL};
    int i = 0;
    while (builtins[i])
    {
        if (ft_strcmp(cmd->argv[0], builtins[i]) == 0)
            return 1;
        i++;
    }
    return 0;
}

static int is_executable_path(char *path)
{
    if (!path)
        return (0);
    if (access(path, X_OK) == 0)
        return (1);
    return (0);
}

int is_external_command(t_cmd *cmd)
{
    char *cmd_name;
    char *path_env;

    if (!cmd || !cmd->argv || !cmd->argv[0])
        return 0;
    cmd_name = cmd->argv[0];
    if (cmd_name[0] == '/' || (cmd_name[0] == '.' && (cmd_name[1] == '/' || (cmd_name[1] == '.' && cmd_name[2] == '/'))))
        return (is_executable_path(cmd_name));
    path_env = getenv("PATH");
    if (!path_env)
        return 0;
    return ; // aqui eu preciso retornar o path da função externa... preciso fazer essa função ainda
}

