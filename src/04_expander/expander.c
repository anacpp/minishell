/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by acesar-p          #+#    #+#             */
/*   Updated: 2025/06/11 17:14:43 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
	EXPANDER.C

	Contém a função principal de expansão de variáveis dentro de uma string. 
	Respeita o comportamento do Bash para:
	- Expansão de $VAR e ${VAR}
	- Expansão de $? (último status de saída)
	- Não expandir dentro de aspas simples
	- Permitir expansão dentro de aspas duplas

	Fluxo:
	- expand_variables: percorre a string original e substitui os tokens com '$'.
	- handle_dollar: extrai o nome da variável e retorna seu valor (ou "" se indefinida).
	- append_char_and_advance: adiciona caractere literal à string resultante.
	- expand_tokens: aplica a expansão a todos os tokens do parser que não estão entre aspas simples.

	Depende de funções auxiliares em utils_expand.c.
*/

//TODO: NORMINETTE

#include "../../includes/minishell.h"

char	*handle_dollar(char *str, int *i, int status);
char	*append_char_and_advance(char *str, char c);


char *expand_variables(char *input, int status)
{
	int		i;
	int		in_squote;
	int		in_dquote;
	char	*result;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	result = ft_strdup("");
	while (input[i])
	{
		update_quotes(input[i], &in_squote, &in_dquote);
		if (input[i] == '$' && !in_squote)
			result = process_dollar_sequence(result, input, &i, status);
		else
			result = process_regular_char(result, input[i], &i);
		if (!result)
			return (NULL);
	}
	return (result);
}

char *handle_dollar(char *str, int *i, int status)
{
    int j;
    char *name;
    char *value;

    j = 0;
    (*i)++;
    if (str[1] == '?')  
    {
        (*i)++;
        return (ft_itoa(status));
    }
    while (str[1 + j] && (ft_isalnum(str[1 + j]) || str[1 + j] == '_'))
        j++;
    if (j == 0)
        return ft_strdup("$"); 
    name = ft_substr(str, 1, j); 
    value = getenv(name);   
    free(name);
    (*i) += j;
    if (!value)
        return ft_strdup("");  
    printf("[EXPAND_DEBUG] $%.*s -> %s\n", j, str + 1, value ? value : "(null)");
    return (ft_strdup(value));
}


char	*append_char_and_advance(char *str, char c)
{
	int		len;
	char	*new;

	len = ft_strlen(str);
	new = malloc(len + 2);
	if (!new)
		return (NULL);
	ft_memcpy(new, str, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(str);
	return (new);
}
void expand_tokens(t_token *tokens, int last_status)
{
	t_token *tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->quote_type != 1)
		{
			char *expanded = expand_variables(tmp->value, last_status);
			if (!expanded)
				break; 
			free(tmp->value);
			tmp->value = expanded;
		}
		tmp = tmp->next;
	}
}

