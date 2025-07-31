#include "../../includes/minishell.h"

int	is_token_end(char c, int in_squote, int in_dquote)
{
	if (in_squote || in_dquote)
		return (0);
	return (is_operator_char(c) || c == ' ' || c == '\t');
}
int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
