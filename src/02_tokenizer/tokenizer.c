#include "minishell.h"


static char *expand_variable(const char *str, int *i)
{
    int     start;
    char    *var_name;
    char    *var_value;
    char    *value;

	start = *i;
    (*i)++;
    while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
        (*i)++;
    var_name = ft_strndup(str + start + 1, *i - start - 1);
    var_value = getenv(var_name);
    free(var_name);
    if (var_value)
        value = ft_strdup(var_value);
    else
        value = ft_strdup("");
    return (value);
}

static int is_operator_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

static char *get_token_value(const char *str, int *i)
{
    int     in_squote;
    int     in_dquote;
    char    *value;
    char    *expanded_value;

    in_squote = 0;
    in_dquote = 0;
    value = ft_strdup("");
    while (str[*i])
    {
        update_quote_flags(str[*i], &in_squote, &in_dquote);
        if (str[*i] == '$' && !in_squote)
        {
            expanded_value = expand_variable(str, i);
            update_token_value(&value, expanded_value);
            free(expanded_value);
        }
        else if (is_token_end(str[*i], in_squote, in_dquote))
            break ;
        else
            (*i)++;
    }
    return (value);
}

static char *get_operator(const char *str, int *i)
{
    char    *operator;

    operator = NULL;
    if ((str[*i] == '<' || str[*i] == '>') && str[*i + 1] == str[*i])
    {
        operator = ft_strndup(str + *i, 2);
        (*i) += 2;
    }
    else if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>')
    {
        operator = ft_strndup(str + *i, 1);
        (*i)++;
    }
    return (operator);
}

t_token *tokenize_input(const char *str)
{
    t_token *head;
    char    *value;
    int     i;

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
        if (value && *value)
        {
            add_token(&head, value, get_token_type(value));
            free(value);
        }
    }
    return (head);
}

// Main function for testing

int main(void)
{
    const char *input = "$USER ls -l | grep test > output.txt";
    t_token *tokens = tokenize_input(input);

    print_tokens(tokens);

    return 0;
}