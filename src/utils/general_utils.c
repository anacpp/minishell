#include "../../includes/minishell.h"

void	handle_error(char *data, char *msg, int code)
{
	// TODO: Remove comment to test manually
	//(void)data;
	//(void)code;

	if (msg)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
	}
	// TODO: Comment those lines to test manually
	if (data)
		free(data);
	exit(code);
}