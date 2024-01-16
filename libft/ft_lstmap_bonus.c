/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:33:55 by sangylee          #+#    #+#             */
/*   Updated: 2023/03/19 21:38:48 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	lst_init(t_list **lst, void *(*f)(void *), t_list **start, t_list **cur)
{
	void	*ptr;

	if (!(*lst) || !f)
		return (0);
	ptr = f((*lst)->content);
	if (!ptr)
		return (0);
	(*cur) = ft_lstnew(ptr);
	if (!(*cur))
	{
		free(ptr);
		return (0);
	}
	(*start) = (*cur);
	(*lst) = (*lst)->next;
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*cur;
	void	*ptr;

	if (!lst_init(&lst, f, &start, &cur))
		return (NULL);
	while (lst)
	{
		ptr = f(lst->content);
		if (!ptr)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		cur->next = ft_lstnew(ptr);
		if (!(cur->next))
		{
			free(ptr);
			ft_lstclear(&start, del);
			return (NULL);
		}
		cur = cur->next;
		lst = lst->next;
	}
	return (start);
}
