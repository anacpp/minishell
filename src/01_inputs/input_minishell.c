#include "../../includes/minishell.h"

static int	has_unclosed_quotes(const char *input)
{
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	while (*input)
	{
		if (*input == '\'' && !in_double)
			in_single = !in_single;
		else if (*input == '"' && !in_single)
			in_double = !in_double;
		input++;
	}
	return (in_single || in_double);
}

static int	is_redirect(char c)
{
	return (c == '<' || c == '>');
}

static int	has_malformed_redirects(const char *input)
{
	int	i;
	int	in_single;
	int	in_double;
	int	redirect_len;

	i = 0;
	in_single = 0;
	in_double = 0;
	redirect_len = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (input[i] == '"' && !in_single)
			in_double = !in_double;
		if (!in_single && !in_double && is_redirect(input[i]))
		{
			redirect_len = 1;
			if (input[i + 1] == input[i])
				redirect_len++;
			i += redirect_len;
			while (input[i] == ' ' || input[i] == '\t')
				i++;
			if (input[i] == '\0' || is_redirect(input[i]) || input[i] == '|')
				return (1);
		}
		else
			i++;
	}
	return (0);
}

static int	contain_pipe_error(const char *input)
{
	int	in_single;
	int	in_double;
	int	expect_next;

	in_single = 0;
	in_double = 0;
	expect_next = 0;
	while (*input)
	{
		if (*input == '\'' && !in_double)
			in_single = !in_single;
		else if (*input == '"' && !in_single)
			in_double = !in_double;
		if (*input == '|' && !in_single && !in_double)
		{
			if (expect_next)
				return (1);
			expect_next = 1;
		}
		else if (*input != ' ' && *input != '\t')
			expect_next = 0;
		input++;
	}
	return (expect_next);
}

static int	contains_unsupported_logical_operators(const char *input)
{
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	while (*input)
	{
		if (*input == '\'' && !in_double)
			in_single = !in_single;
		else if (*input == '"' && !in_single)
			in_double = !in_double;
		if (!in_single && !in_double)
		{
			if ((*input == '&' && *(input + 1) == '&') || (*input == '|'
					&& *(input + 1) == '|'))
				return (1);
		}
		input++;
	}
	return (0);
}

void	is_valid_input_syntax(char *input)
{
	if (!input || !*input)
	{
		handle_error(input, NULL, 1);
		return ;
	}
	//TODO: any reason to cast to char*?
	if (has_unclosed_quotes((char *)input))
		handle_error(input, "Syntax error: unclosed quotes", 2);
	else if (contain_pipe_error((char *)input) || *input == '|')
		handle_error(input, "Syntax error: unexpected pipe", 2);
	else if (contains_unsupported_logical_operators((char *)input))
		handle_error(input, "Syntax error: unsupported logical operator", 2);
	else if (has_malformed_redirects((char *)input))
		handle_error(input, "Syntax error: malformed redirection", 2);
	else
		printf("✅ O input dado: \"%s\" é válido\n", input);
}

/*main para teste por função

int	main(void)
{
	const char	*tests[] = 	"| ls -l";
	int	i;

	i = 0;
	while (tests[i])
	{
		printf("Testando: %s\n", tests[i]);
		is_valid_input_syntax(tests[i]);
		i++;
	}
	return (0);
}*/
