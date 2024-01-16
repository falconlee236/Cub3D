/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:19:14 by sangylee          #+#    #+#             */
/*   Updated: 2023/03/22 16:28:26 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*cur;

	if (!del || !lst)
		return ;
	cur = *lst;
	while (cur)
	{
		node = cur;
		del(cur->content);
		cur = cur->next;
		free(node);
	}
	*lst = NULL;
}
