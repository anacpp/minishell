/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:00 by rjacques          #+#    #+#             */
/*   Updated: 2025/06/11 17:17:57 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	perform_quote_removal(char *str, char *new_str);

char	*remove_quotes(char *str)
{
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		handle_error(NULL, "malloc failed", 1, 1);
	perform_quote_removal(str, new_str);
	return (new_str);
}

static void	perform_quote_removal(char *str, char *new_str)
{
	int	i;
	int	j;
	int	in_squote;
	int	in_dquote;

	i = 0;
	j = 0;
	in_squote = 0;
	in_dquote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
}

t_cmd	*create_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		handle_error(NULL, "malloc failed", 1, 1);
	new_cmd->argv = NULL; 
	new_cmd->redirs = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}
//REFATORAR : 26 LINHAS
char	**ft_realloc_argv(char **argv, const char *new_arg)
{
	int		size;
	char	**new_argv;

	size = 0;
	if (argv)
	{
		while (argv[size])
			size++;
	}
	new_argv = malloc(sizeof(char *) * (size + 2));
	if (!new_argv)
		return (NULL);
	size = 0;
	if (argv)
	{
		while (argv[size])
		{
			new_argv[size] = argv[size];
			size++;
		}
	}
	new_argv[size] = ft_strdup(new_arg);
	new_argv[size + 1] = NULL;
	if (argv)
		free(argv);
	return (new_argv);
}
