/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:05:55 by clados-s          #+#    #+#             */
/*   Updated: 2026/04/12 11:58:07 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstclear(t_list **lst, void (*del)(void*), int flag)
{
	t_list	*temp;
	t_list	*actualy;

	if (!del || !*lst)
		return (flag);
	actualy = *lst;
	temp = actualy->next;
	while (actualy && actualy->next)
	{
		ft_lstdelone(actualy, del);
		actualy = temp;
		temp = actualy->next;
	}
	if (actualy)
	{
		ft_lstdelone(actualy, del);
	}
	*lst = NULL;
	return (flag);
}
