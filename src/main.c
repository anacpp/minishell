#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *input;

    printf("Digite algo (Ctrl+D para sair):\n");

    while (1)
    {
        input = readline("minishell$ ");
        if (!input) {
            printf("\n[Encerrado com Ctrl+D]\n");
            break;
        }

        if (*input)
            add_history(input);
        printf("Você digitou: %s\n", input);

        free(input);
    }
    clear_history(); 
    return 0;
}
