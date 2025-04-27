/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:52:02 by aiimdih           #+#    #+#             */
/*   Updated: 2024/11/06 15:18:55 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		new->next = *lst;
		*lst = new;
	}
}
/*int main()
{
	t_list *node1 = ft_lstnew("node1");
	t_list *node2 = ft_lstnew("node2");
	t_list *node3 = ft_lstnew("node3");
	node1->next	= node2;
	node2->next 	= node3;
	node3->next 	= NULL;
	t_list *newnode = ft_lstnew("newnode");
	newnode->next = NULL;
	printf("%s \n, %s\n", (char*)node1->content, (char*)newnode->next);
	ft_lstadd_front(&node1, newnode);
	printf("%s \n, %p\n", (char*)node1->content, newnode->next);
}*/
