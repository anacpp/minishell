#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


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
			if ((*input == '&' && *(input + 1) == '&')
				|| (*input == '|' && *(input + 1) == '|'))
				return (1);
		}
		input++;
	}
	return (0);
}
void	is_valid_input_syntax(const char *input)
{
    if (!*input)
        handle_error(NULL, NULL, 1);
    if (contain_pipe_error((char *)input) || *input == '|')
        handle_error(NULL, "Syntax error: unexpected pipe", 2);	
    else if (contains_unsupported_logical_operators((char *)input))
        handle_error(NULL, "Syntax error: unsupported logical operator", 2);	
    else
        
}


// Função da Raquel 03
// Função da Raquel 04


//main para teste

#include <stdio.h>


int	main(void)
{
	const char	*tests[] = {
		"| ls -l",
		/*"ls -l |a",
		"ls -l || grep txt",
		"ls -l | | grep txt",
		"echo \"ok\" && ls",
		"echo \" | ola camarada && |\" | grep txt",
		"ls | grep txt",
		"cat file.txt",*/
		NULL
	};
	int	i;

	i = 0;
	while (tests[i])
	{
		printf("Testando: %s\n", tests[i]);
		is_valid_input_syntax(tests[i]);
		i++;
	}
	return (0);
}

