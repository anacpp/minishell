#include "../../includes/minishell.h"

// Define as variáveis globais que foram declaradas com 'extern' no header.
pid_t					g_child_pids[MAX_PIDS];
int						g_num_pids;
volatile sig_atomic_t	g_signal_status = 0;
