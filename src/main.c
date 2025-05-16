//TODO : Add header, CHECK NORMINETTE, tirar os prints e print_tokens quando for fazer a entrega / FAZER O TRATAMENTO NO PRÉ-TRATAMENTO PARA EVITAR O ERRO DE ASPAS MAL FORMADAS

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
        pre_treat_input = ft_strtrim((char *)input, " \t\n");
        free(input);
        if (!*pre_treat_input)
        {
            free(pre_treat_input);
            continue;
        }
        is_valid_input_syntax(pre_treat_input);
        tokens = tokenize_input(pre_treat_input);
        free(pre_treat_input);
        if (!tokens)                 
            continue ;
        //print_tokens(tokens);
        free_tokens(tokens);
    }
    clear_history(); 
    return 0;
}

