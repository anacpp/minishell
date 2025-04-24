/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-p <acesar-p@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:57:59 by acesar-p          #+#    #+#             */
/*   Updated: 2024/10/03 16:58:58 by acesar-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_stack **lst, void (*del)(void *))
{
	t_stack	*current_lst;
	t_stack	*tmp;

	if (!lst || !del)
		return ;
	current_lst = *lst;
	while (current_lst != NULL)
	{
		tmp = current_lst;
		current_lst = current_lst->next;
		del(tmp->content);
		free(tmp);
	}
	*lst = NULL;
}
