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

/**
 * @brief Verifica se a string representa a flag `-n` do comando `echo`.
 * @param str A string a ser verificada.
 * @return 1 se for a flag `-n`, 0 caso contrário.
 * */
int	is_n_flag(char *str)
{
	int	i;

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

/**
 * @brief Verifica se a chave de uma variável de ambiente é válida.
 */
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
/**
 * @brief Ordena um array de strings em ordem alfabética (Bubble Sort).
 * @param env O array de ponteiros de string a ser ordenado.
 * @param count O número de elementos no array.
 */
static void	sort_env_array(char **env, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strncmp(env[j], env[j + 1], ft_strlen(env[j])) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief Imprime as variáveis de ambiente no formato 'declare -x KEY=VALUE',
 * em ordem alfabética.
 *
 * Esta função cria uma cópia do array de ponteiros do ambiente para
 * não modificar a ordem do ambiente original do shell.
 *
 * @param envp O ambiente do shell a ser impresso.
 */
void	print_env_sorted(char **envp)
{
	char	**env_copy;
	int		count;
	int		i;

	if (!envp)
		return ;
	count = 0;
	while (envp[count])
		count++;
	env_copy = malloc(sizeof(char *) * (count + 1));
	if (!env_copy)
		return ;
	i = -1;
	while (++i < count)
		env_copy[i] = envp[i];
	env_copy[count] = NULL;
	sort_env_array(env_copy, count);
	i = 0;
	while (i < count)
	{
		//ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_copy[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	free(env_copy);
}
