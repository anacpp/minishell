#include "../../includes/minishell.h"

void	update_quote_flags(char c, int *in_squote, int *in_dquote)
{
	if (c == '\'' && !(*in_dquote))
		*in_squote = !(*in_squote);
	else if (c == '\"' && !(*in_squote))
		*in_dquote = !(*in_dquote);
}

static t_token	*create_token(char *value, t_token_type type, int quote_type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	new->quote_type = quote_type;
	new->next = NULL;
	return (new);
}

void	add_token(t_token **head, char *value, t_token_type type, int quote_type)
{
	t_token	*new;
	t_token	*temp;

	if (!value)
		return ;
	new = create_token(value, type, quote_type);
	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
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
