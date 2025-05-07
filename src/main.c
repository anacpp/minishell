#include "../includes/minishell.h"

int main(void)
{
    char *input;
    char *pre_treat_input;

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
        //printf("Você digitou: %s\n", input);
        pre_treat_input = ft_strtrim((char *)input, " \t\n");
        free(input);
        if (!*pre_treat_input)
        {
            free(pre_treat_input);
            continue;
        }
        is_valid_input_syntax((char *)pre_treat_input);
    }
    clear_history(); 
    return 0;
}
