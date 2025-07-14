#include "../../includes/minishell.h"

char	*ft_strjoin_triple(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*res;

	if (!s1 || !s2 || !s3)
		return (NULL);
		//TODO: USAR STR NO FREE
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
		//TODO: USAR STR NO FREE
	res = ft_strjoin(tmp, s3);
	free(tmp);
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
