#include "minishell.h"

void	add_token(t_token **head, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*temp;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = ft_strdup(value);
	new->type = type;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
}
char	*ft_strndup(const char *s, size_t n)
{
    size_t	i;
    char	*dup;

    i = 0;
    while (s[i] && i < n)
        i++;
    dup = malloc(i + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (s[i] && i < n)
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}
