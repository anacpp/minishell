/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extern_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:36:30 by rjacques          #+#    #+#             */
/*   Updated: 2025/07/17 18:52:12 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*TODO: 
	USAR STR_no_free em vez de ft_strjoin na funçõa join_triple */

#include "../../includes/minishell.h"

char	*ft_strjoin_triple(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	if (!s1 || !s2 || !s3)
		return (NULL);
	tmp = ft_strjoin_no_free(s1, s2);
	if (!tmp)
		return (NULL);
	res = ft_strjoin_no_free(tmp, s3);
	free(tmp);
	return (res);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
