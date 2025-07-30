
#include "../includes/minishell.h"

void	handle_exit(int is_interactive)
{
	if (is_interactive)
		write(STDOUT_FILENO, "exit\n", 5);
}

char	*get_input(int is_interactive)
{
	if (is_interactive)
		return readline("minishell$ ");
	return readline(NULL);
}
