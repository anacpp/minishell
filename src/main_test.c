#include "../includes/minishell.h"

int	main(void)
{
	char *input;
	char *trimmed;

	const char *tests[] = {"", "rm -rf ", "comando > output.txt 2>&1", "ls -l",
		"| ls", "ls || grep", "echo \"ola", "echo 'ola", "cat <<", "ls >",
		"echo oi >>> file.txt", "echo > > file.txt", "ls -l | grep txt", NULL};
	int i = 0;

	printf("\n==== 🧪 Testando inputs automaticamente ====\n");
	while (tests[i])
	{
		printf("🔹 Teste %02d: \"%s\"\n", i + 1, tests[i]);
		trimmed = ft_strtrim(tests[i], " \t\n");
		is_valid_input_syntax(trimmed);
		free(trimmed);
		printf("--------------------------------------------------\n");
		i++;
	}

	printf("\n==== 💬 Agora digite comandos manualmente ====\n");

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("\n[Encerrado com Ctrl+D]\n");
			break ;
		}
		if (*input)
			add_history(input);

		trimmed = ft_strtrim(input, " \t\n");
		free(input);

		if (!*trimmed)
		{
			free(trimmed);
			continue ;
		}
		is_valid_input_syntax(trimmed);
		free(trimmed);
	}
	clear_history();
	return (0);
}