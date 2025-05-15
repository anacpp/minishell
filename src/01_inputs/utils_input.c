//TODO : Add header, CHECK NORMINETTE

#include "../../includes/minishell.h"

void	update_quote_state(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
	else if (c == '"' && !(*in_single))
		*in_double = !(*in_double);
}


int	is_redirect(char c)
{
    // TODO : tem que verificar se podemos dar um return com condicional.
	return (c == '<' || c == '>');
}


int	skip_redirect_and_check_error(const char *input, int *i)
{
	int	redirect_len;

	redirect_len = 1;
	if (input[*i + 1] == input[*i])
		redirect_len++;
	*i += redirect_len;
	while (input[*i] == ' ' || input[*i] == '\t')
		(*i)++;
	return (input[*i] == '\0' || is_redirect(input[*i]) || input[*i] == '|');
}