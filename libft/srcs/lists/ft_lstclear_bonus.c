/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:05:55 by clados-s          #+#    #+#             */
/*   Updated: 2026/03/30 13:21:25 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstclear(t_list **lst, void (*del)(void*), int r)
{
	t_list	*temp;
	t_list	*actualy;

	if (!del || !*lst)
		return (r);
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
	return (r);
}
