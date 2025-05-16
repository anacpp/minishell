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

/*
// Função de teste para verificar o funcionamento do tokenizer com texto simples + expansão de variáveis + operadores VAI SER APAGADA DEPOIS DO TESTE

int main(void)
{
    const char *tests[] = {
        "echo \'ana",                         // FAZER O TRATAMENTO NO PRÉ-TRATAMENTO PARA EVITAR O ERRO DE ASPAS MAL FORMADAS
        "echo '$USER'",                       // aspas simples: sem expansão OK
        "echo \"$USER\"",                     // aspas duplas: com expansão OK
        "echo $USERabc",                      // var + sufixo **VERIFICAR NO TERMINAL DE OUTRA PESSOA**
        "echo abc$USER",                      // prefixo + var OK 
        "echo abc$USERxyz",                   // prefixo + var + sufixo **VERIFICAR NO TERMINAL DE OUTRA PESSOA**
        "ls -l | grep \"$USER\" > out.txt",   // operador + expansão OK
        "cat<<file",                           // heredoc OK
        "echo > file.txt",                    // redirecionamento OK
        "cat < infile | sort > outfile",      // redir in + pipe + redir out OK
        "echo $UNDEFINED",                    // var indefinida VERIFICAR NO TERMINAL
        "mkdir test && cd test",              // operadores inválidos (extra) OK
        "echo \"Hello, $USER!\"",             // string formatada com var OK
        "echo \"abc $USER def\" | wc -l",     // expansão + pipe OK 
        "echo $USER$HOME",                    // múltiplas vars seguidas OK
        NULL
    };
    
    int i = 0;
    t_token *tokens;
    while (tests[i])
    {
        printf("Test input: %s\n", tests[i]);
        tokens = tokenize_input(tests[i]);
        if (!tokens)
        {
            printf("No tokens generated.\n");
        }
        else
        {
            print_tokens(tokens);
            free_tokens(tokens);
        }
        printf("\n");
        i++;
    }
    return 0;
}*/