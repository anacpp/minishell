
#include "../../includes/minishell.h"

void save_pid(pid_t pid)
{
	if (g_num_pids < MAX_PIDS)
	{
		g_child_pids[g_num_pids] = pid;
		g_num_pids++;
	}
	else
		ft_printf("minishell: too many child processes\n");
}
int wait_pid(pid_t pid)
{
	int status;

	if (waitpid(pid, &status, 0) == -1)
		return (1); // erro no waitpid
	if (WIFEXITED(status)) // se saiu corretamente
		g_signal_status = WEXITSTATUS(status);// retorna status de saída
	else if (WIFSIGNALED(status)) // se houve uma interrupção do proce. por sinal ex: ctrl + c
		g_signal_status = 128 + WTERMSIG(status); // retorna o status de processi interrompido por sinal
	return (0);
}
void wait_all_children(void)
{
	int i;

    i = 0;
	while (i < g_num_pids)
    {
		wait_pid(g_child_pids[i]);
        i++;
    }
	g_num_pids = 0;
}
