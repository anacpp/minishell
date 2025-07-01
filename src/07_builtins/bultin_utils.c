/*
	BUILTIN_UTILS.C

	Funções auxiliares para suporte aos comandos built-in.

	Funções:
	- is_n_flag: checa se a flag `-n` do echo está presente corretamente.
	- is_valid_key: valida nomes de variáveis para export/unset.
	- print_env_sorted: imprime variáveis de ambiente em ordem de export.

	Essas funções ajudam a garantir que os comandos built-in funcionem corretamente e de forma padronizada.
*/


#include "../../includes/minishell.h"

int is_n_flag(char *str)
{
    int i;

    if (!str || str[0] != '-' || str[1] != 'n')
        return (0);
    i = 2;
    while (str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}
extern char	**environ; // isso aqui é uma variavel de ambiente, tenho que ver se ao apontar para ela dessa forma é errado.

int	is_valid_key(char *key)
{
	int	i;

	if (!key || !(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	i = 1;
	while (key[i] && key[i] != '=')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
void	print_env_sorted(void)
{
	char	*key;

	for (int j = 0; environ[j]; j++)
	{
		if (ft_strchr(environ[j], '='))
		{
			key = ft_substr(environ[j], 0, ft_strchr(environ[j], '=') - environ[j]);
			ft_printf("declare -x %s=\"%s\"\n", key, getenv(key));
			free(key);
		}
	}
}
