#include "minishell.h"

static int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
static t_token_type	get_token_type(const char *str)
{
	if (!ft_strcmp(str, "|", 2))
		return (T_PIPE);
	else if (!ft_strcmp(str, "<", 2))
		return (T_REDIR_IN);
	else if (!ft_strcmp(str, ">", 2))
		return (T_REDIR_OUT);
	else if (!ft_strcmp(str, "<<", 3))
		return (T_HEREDOC);
	else if (!ft_strcmp(str, ">>", 3))
		return (T_APPEND);
	return (T_WORD);
}

static char	*get_token_value(const char *str, int *i)
{
	int		start;
	int		in_single_quote;
	int		in_double_quote;

	start = *i;
	in_single_quote = 0;
	in_double_quote = 0;
	while (str[*i])
	{
		if (str[*i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[*i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && !in_double_quote
			&& (is_operator_char(str[*i]) || str[*i] == ' ' || str[*i] == '\t'))
			break;
		(*i)++;
	}
	return ft_strndup(str + start, *i - start);
}

static char *get_operator(const char *str, int *i)
{
	char	*operator;

	operator = NULL;
	if ((str[*i] == '<' || str[*i] == '>') && str[*i + 1] == str[*i])
	{
		operator = ft_strndup(str + *i, 2); 
		(*i) += 2;
	}
	else if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>' ) 
	{
		operator = ft_strndup(str + *i, 1); 
		(*i)++; 
	}
	return (operator);
}

t_token	*tokenize_input(const char *str)
{
	t_token	*head;
	char	*value;
	int		i;

	head = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!str[i])
			break ;
		if (is_operator_char(str[i]))
			value = get_operator(str, &i);
		else
			value = get_token_value(str, &i);
		if (!value)
			continue ;
		add_token(&head, value, get_token_type(value));
		free(value);
	}
	return (head);
}