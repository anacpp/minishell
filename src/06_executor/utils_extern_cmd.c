#include "../../includes/minishell.h"

char *ft_strjoin_triple_free(char *s1, char *sep, char *s2,
								int free_s1, int free_sep, int free_s2)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin_free(s1, sep, free_s1, free_sep);
	if (!tmp)
	{
		if (!free_s1) free(s1);
		if (!free_sep) free(sep);
		if (free_s2) free(s2);
		return (NULL);
	}
	res = ft_strjoin_free(tmp, s2, 1, free_s2);
	return (res);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char *ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;
    
    len2 = ft_strlen(s2);
    len1 = ft_strlen(s1);
    joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	ft_memcpy(joined, s1, len1);
	ft_memcpy(joined + len1, s2, len2);
	joined[len1 + len2] = '\0';
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
	return (joined);
}
