#include "../../includes/minishell.h"

static char *check_direct_exec(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

//relative path -> path relative to the currenty directory you are (ex: shit.sh). / absolute path is full path from the root (ex: /home/acesar/script/shit.sh)
static char	*find_cmd_path(char *cmd)
{
	char	**paths;
	char	*path_var;
	char	*full_path;
	int		i;

	if (!cmd || ft_strchr(cmd, '/')) // já tem caminho
		return check_direct_exec(cmd);
	path_var = getenv("PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_triple(paths[i], "/", cmd); // helper
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}
extern char **environ;

void	exec_external(t_cmd *cmd)
{
	char	*cmd_path;

	cmd_path = find_cmd_path(cmd->argv[0]);
	if (!cmd_path)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", cmd->argv[0]);
		exit(127); // padrão bash para "command not found"
	}
	execve(cmd_path, cmd->argv, environ);
	ft_printf("minishell: %s: %s\n", cmd->argv[0], strerror(errno));
	free(cmd_path);
	exit(126); // "permission denied"
}
