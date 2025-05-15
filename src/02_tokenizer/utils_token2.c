#include "minishell.h"

int	is_token_end(char c, int in_squote, int in_dquote)
{
	return (!in_squote && !in_dquote &&
		(is_operator_char(c) || c == ' ' || c == '\t'));
}

void update_token_value(char **value, const char *expanded_value)
{
    char *temp;

    temp = ft_strjoin(*value, expanded_value);
    free(*value);
    *value = temp;
}

void print_tokens(t_token *head)
{
    t_token *temp = head;
    while (temp)
    {
        printf("Token: %s, Type: %d\n", temp->value, temp->type);
        temp = temp->next;
    }
}
