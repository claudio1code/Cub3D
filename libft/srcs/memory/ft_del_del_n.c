/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_del_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacesar- <cacesar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 09:42:21 by cacesar-          #+#    #+#             */
/*   Updated: 2026/04/12 08:49:56 by cacesar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_del_del_n(void**tofree, int n)
{
	int	count;

	count = 0;
	if (!tofree)
		return ;
	while (count < n)
		ft_del(tofree[count++]);
	ft_del(tofree);
}
