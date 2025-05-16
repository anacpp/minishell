#include "../../includes/minishell.h"

t_token	*get_last_token(t_token *head)
{
	t_token	*current;

	current = head;
	if (!current)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}
