#include "../../includes/minishell.h"

void handle_error(char *data, char *msg, int code)
{
    if (msg)
    {
        write(STDERR_FILENO, msg, ft_strlen(msg));
        write(STDERR_FILENO, "\n", 1);
    }
    if (data)
        free(data);
    exit(code);
}