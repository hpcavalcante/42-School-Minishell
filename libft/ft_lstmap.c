/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:56:14 by gissao-m          #+#    #+#             */
/*   Updated: 2022/10/17 14:57:14 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_new;
	t_list	*aux;

	lst_new = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		aux = ft_lstnew(f(lst->content));
		if (!aux)
			ft_lstclear(&aux, del);
		lst = lst->next;
		ft_lstadd_back(&lst_new, aux);
	}
	return (lst_new);
}
