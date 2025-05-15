#include "../includes/minishell.h"

int main(void)
{
    char *input;
    char *pre_treat_input;
    t_token *tokens;

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
        pre_treat_input = ft_strtrim(input, " \t\n");
        free(input);
        if (!*pre_treat_input)
        {
            free(pre_treat_input);
            break;
        }
        is_valid_input_syntax(pre_treat_input);
        tokens = tokenize_input(pre_treat_input);
        free(pre_treat_input);
        if (!tokens)
        {
            ft_printf("Erro ao tokenizar a entrada.\n");
            continue ;
        }
        print_tokens(tokens);
        free_tokens(tokens);
    }
    clear_history(); 
    return 0;
}
